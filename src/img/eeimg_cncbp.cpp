/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file eeimg_cncbp.cpp
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */

#include <string>
#include <iostream>
#include <stdint.h>
#include "EEException.h"
#include "EEExtBlock.h"
#include "img/idt_89hpesXnt8.h"
#include "img/eeimg.h"

/*! @struct Delays configuration
 *   Static configurations of initialization delays
 */
struct delay_cfg {
	const uint32_t reg;
	const uint32_t no;
	const uint32_t def;
};

/*! @struct Partitions configuration
 *   Constant partition configs used by the firmware gen code
 */
struct part_cfg {
	const uint32_t swpartctl;
	const uint32_t swpartsts;
};

/*! @struct Ports configuration
 *   Constant and variable configs of the switch ports
 */
struct port_cfg {
	const uint32_t id;
	const uint32_t usx_base;
	const uint32_t ntx_base;
	const uint32_t swportctl;
	const uint32_t swportsts;
	const uint32_t sXtxlctl;
	uint32_t mode;
	uint32_t part;
	uint32_t devnum;
};

/*! @var delays
 *   IDT PCIe-switch boot delays
 */
static const struct delay_cfg delay[DELAYS_CNT] = {
	{.reg = RDRAINDELAY, .no = RDRAINDELAY_NODELAY, .def = RDRAINDELAY_DEFAULT},
	{.reg = POMCDELAY,   .no = POMCDELAY_NODELAY,   .def = POMCDELAY_DEFAULT},
	{.reg = SEDELAY,     .no = SEDELAY_NODELAY,     .def = SEDELAY_DEFAULT},
	{.reg = USSBRDELAY,  .no = USSBRDELAY_NODELAY,  .def = USSBRDELAY_DEFAULT}
};

/*! @struct Partitions configuration
 *   Static partition configs like non-regular registers address
 */
static const struct part_cfg part[IDT_PARTCNT] = {
	{.swpartctl = SWPART0CTL, .swpartsts = SWPART0STS}, {.swpartctl = SWPART1CTL, .swpartsts = SWPART1STS},
	{.swpartctl = SWPART2CTL, .swpartsts = SWPART2STS}, {.swpartctl = SWPART3CTL, .swpartsts = SWPART3STS},
	{.swpartctl = SWPART4CTL, .swpartsts = SWPART4STS}, {.swpartctl = SWPART5CTL, .swpartsts = SWPART5STS},
	{.swpartctl = SWPART6CTL, .swpartsts = SWPART6STS}, {.swpartctl = SWPART7CTL, .swpartsts = SWPART7STS}
};

/*! @var port
 *   Ports static and variable configurations
 */
static struct port_cfg port[IDT_PORTCNT] = {
	{.id = 0,  .usx_base = US0_BASE,  .ntx_base = NT0_BASE,  .swportctl = SWPORT0CTL,  .swportsts = SWPORT0STS,  .sXtxlctl = S0TXLCTL1,
	 .mode = SWPORTxCTL_MODE_USNT, .part = 0, .devnum = 0},

	{.id = 2,  .usx_base = US2_BASE,  .ntx_base = NT2_BASE,  .swportctl = SWPORT2CTL,  .swportsts = SWPORT2STS,  .sXtxlctl = S1TXLCTL1,
	 .mode = SWPORTxCTL_MODE_DS,   .part = 0, .devnum = 2},

	{.id = 4,  .usx_base = US4_BASE,  .ntx_base = NT4_BASE,  .swportctl = SWPORT4CTL,  .swportsts = SWPORT4STS,  .sXtxlctl = S2TXLCTL1,
	 .mode = SWPORTxCTL_MODE_NT,   .part = 1, .devnum = 0},

	{.id = 6,  .usx_base = US6_BASE,  .ntx_base = NT6_BASE,  .swportctl = SWPORT6CTL,  .swportsts = SWPORT6STS,  .sXtxlctl = S3TXLCTL1,
	 .mode = SWPORTxCTL_MODE_NT,   .part = 2, .devnum = 0},

	{.id = 8,  .usx_base = US8_BASE,  .ntx_base = NT8_BASE,  .swportctl = SWPORT8CTL,  .swportsts = SWPORT8STS,  .sXtxlctl = S4TXLCTL1,
	 .mode = SWPORTxCTL_MODE_NT,   .part = 3, .devnum = 0},

	{.id = 12, .usx_base = US12_BASE, .ntx_base = NT12_BASE, .swportctl = SWPORT12CTL, .swportsts = SWPORT12STS, .sXtxlctl = S5TXLCTL1,
	 .mode = SWPORTxCTL_MODE_NT,   .part = 4, .devnum = 0},

	{.id = 16, .usx_base = US16_BASE, .ntx_base = NT16_BASE, .swportctl = SWPORT16CTL, .swportsts = SWPORT16STS, .sXtxlctl = S6TXLCTL1,
	 .mode = SWPORTxCTL_MODE_NT,   .part = 5, .devnum = 0},

	{.id = 20, .usx_base = US20_BASE, .ntx_base = NT20_BASE, .swportctl = SWPORT20CTL, .swportsts = SWPORT20STS, .sXtxlctl = S7TXLCTL1,
	 .mode = SWPORTxCTL_MODE_NT,   .part = 6, .devnum = 0}
};

/*!@var port_map
 *  Backward ports mapping
 */
static const int portidx_tbl[24] = {
	/*  0   1   2   3   4   5   6   7   8   9  10  11 */
	   -1, -1, -1, -1,  2, -1,  3, -1,  4, -1, -1, -1,
	/* 12  13  14  15  16  17  18  19  20  21  22  23 */
		5, -1, -1, -1,  6, -1, -1, -1,  7, -1, -1, -1
};

/*! @fn void eeimg_setds(const char *dstr)
 *   Parse down-stream ports list and update the ports config table
 *
 *  @param dstr string of comma-separated port IDs
 *  @return number of partitions to initialize
 *  @exception EEEXception
 */
static int eeimg_setds(const char *dstr)
{
	int val, part_limit, port_ds;
	std::string str;
	size_t pos;

	/* If no DS-list argument specified then dstr will be NULL, so use default
	 * setting */
	if (!dstr)
		return (IDT_PARTCNT - 1);

	str = dstr;

	/* Fully parse the specified string */
	while (!str.empty()) {
		/* Parse a number from the start up to comma or the end */
		port_ds = std::stoul(str, &pos, 10);
		if (port_ds >= 24 || portidx_tbl[port_ds] == -1)
			throw EEException(std::string("Invalid port ") + std::to_string(port_ds), true);

		/* If retrieved port is appropriate, then set the DS mode to the port */
		port[portidx_tbl[port_ds]].mode = SWPORTxCTL_MODE_DS;

		/* Discard the parsed number from the string */
		str = str.substr(pos, std::string::npos);
		if (!str.empty()) {
			if (str.at(0) == ',')
				str = str.substr(1, std::string::npos);
			else
				throw EEException("Invalid format of DS ports string", true);
		}
	}

	/* Update partitions table so US and DS ports would belong to the same
	 * partition. Start from port 4, since ports 0 and 2 must preserve
	 * static settings in our configuration */
	for (pos = 2, part_limit = 1; pos < IDT_PORTCNT; pos++) {
		if (port[pos].mode == SWPORTxCTL_MODE_DS) {
			port[pos].part = 0;
			port[pos].devnum = port[pos].id;
		} else {
			port[pos].part = part_limit++;
		}
	}

	return part_limit;
}

/*! @fn void eeimg_cncbp(const char *fname)
 *   Write CNC BP EEPROM image
 *
 *  @param params output image paramters
 *  @exception EEEXception
 */
void eeimg_cncbp(struct eeparams *params)
{
	EEExtBlock iface(params->fname);
	int idx, part_limit;

	/* Parse the passed table of downstream ports */
	part_limit = eeimg_setds(params->dstr);

	/* Drop all delays to speed the load up */
	for (idx = 0; idx < DELAYS_CNT; idx++) {
		iface.init(CSR(SW_BASE, delay[idx].reg), delay[idx].no);
	}

	/* Initialize the ports clocking mode so the Port 0 works in local clock-mode
	 * and others have global clock */
	iface.init(CSR(SW_BASE, PCLKMODE), PCLKMODE_INIT);

	/* Mark all ports as having non-common clock mode */
	for (idx = 0; idx < IDT_PORTCNT; idx++) {
		iface.init(CSR(port[idx].usx_base, PCIELCTLSTS), PCIELCTLSTS_CLK_NONCOM);
		iface.init(CSR(port[idx].ntx_base, PCIELCTLSTS), PCIELCTLSTS_CLK_NONCOM);
	}

	/* Initialize the address of the link status/activity and reset GPIO-expanders
	 * IOE17 -> 0x74, IOE18 -> 0x75, IOE19 -> 0x76, IOE20 -> 0x77 */
	iface.init(CSR(SW_BASE, IOEXPADDR4), IOEXPADDR4_INIT);
	iface.init(CSR(SW_BASE, IOEXPADDR5), IOEXPADDR5_INIT);

	/* Initialize the port partitions needed to fulfill the ports mode settings. After 
	 * initialization we need to wait until the change is done, then clear the status
	 * register */
	for (idx = 0; idx < part_limit; idx++) {
		/* Enable partition with idx */
		iface.init(CSR(SW_BASE, part[idx].swpartctl), SWPARTxCTL_STATE_EN);
		/* Wait for partition state is changed */
		iface.wait(CSR(SW_BASE, part[idx].swpartsts), SWPARTxSTS_SCC, SWPARTxSTS_SCC_UNMSK);
		/* Clear the status register */
		iface.init(CSR(SW_BASE, part[idx].swpartsts), SWPARTxSTS_SCI_SCC_CLEAR);
	}

	/* Initialize the ports mode and wait until the change is done
	 * Port 0(US+NT), 2(DS) belong to partition 0 - it's static config and can't be changed
	 * Ports 4 - 20 can be either DS or NT. In first case it belong to partition 0,
	 * in the second - to partitions from 1 to 7.
	 * Then clear the status register */
	for (idx = 0; idx < IDT_PORTCNT; idx++) {
		/* Initialize port mode (US, DS or NT), device number and partition it
		 * belongs to */
		iface.init(CSR(SW_BASE, port[idx].swportctl),
				SWPORTxCTL_INIT(port[idx].mode, port[idx].devnum, port[idx].part));
		/* Wait until the chages are made */
		iface.wait(CSR(SW_BASE, port[idx].swportsts), SWPORTxSTS_OMCC, SWPORTxSTS_OMCC_UNMSK);
		/* Clear the status register */
		iface.init(CSR(SW_BASE, port[idx].swportsts), SWPORTxSTS_OMCI_OMCC_CLEAR);
	}

	/* Enable the necessary BARs for all the NTB functions */
	for (idx = 0; idx < IDT_PORTCNT; idx++) {
		/* Skip pure down-stream ports */
		if (port[idx].mode == SWPORTxCTL_MODE_DS)
			continue;
		/* BAR0 - Memory mapped Configuration space - x32 Non-prefetchable
		 * memory mapped space. Since it is the registers space then it must be
		 * non-prefetchable, which permits the 32-bits address only according
		 * to the PCI specs. Even though PCIe bridges doesn't do any prefetching
		 * whether prefetch bit is set or not, We'll set the bit as a matter of
		 * legacy */
		iface.init(CSR(port[idx].ntx_base, BARSETUP0), BARSETUP_CFG_32BIT);
		/* BAR1 - Shared memory window with direct address translation - x32
		 * Non-prefetchable memory mapped space with aperture of
		 * 2^DIRMW_1MB_APRT, which effectively gives 1Mb of memory space per
		 * each memory window */
		iface.init(CSR(port[idx].ntx_base, BARSETUP1),
				BARSETUP_DIRMW_32BIT | DIRMW_1MB_APRT);
		/* BAR2 + BAR3 - Shared memory windows with address translation
		 * based on lookup table - x64 Non-prefetchable memory mapped space
		 * with aperture of 2^LUMW_1MB_APRT, which effectively gives 1Mb of
		 * memory space per each memory window */
		iface.init(CSR(port[idx].ntx_base, BARSETUP2),
				BARSETUP_24LUMW_64BIT | LUMW_1MB_APRT);
		/* BAR4 + BAR5 - Shared memory window with direct address translation -
		 * x64 Non-prefetchable memory mapped space with aperture of
		 * 2^DIRMW_1MB_APRT, which effectively gives 1Mb of memory space per
		 * each memory window */
		iface.init(CSR(port[idx].ntx_base, BARSETUP4),
				BARSETUP_DIRMW_64BIT | DIRMW_1MB_APRT);
	}

	/* Setup NTSDATA register to declare just one Primary port and
	 * multiple Secondary ones:
	 *  Port 0 - Primary port,
	 *  Port 4 - 20 - secondary ports (six ports altogether) */
	for (idx = 0; idx < IDT_PORTCNT; idx++)
		iface.init(CSR(port[idx].ntx_base, NTSDATA), NTSDATA_PORT0_PRI);

	/* Set ACS capability for Upstream port (errata #8 - for PCIe standard) */
	//iface.init(US0_BASE, ACSCAP), ACSCAP_INIT);

	/* if used requested initialize SerDes low-swing mode with Tx driver voltage
	 * levels */
	if (params->lse) {
		for (idx = 0; idx < IDT_PORTCNT; idx++) {
			/* Enable low-swing mode */
			iface.init(CSR(port[idx].usx_base, SERDESCFG), SERDESCFG_LSE_EN);
			/* Make sure the level is big-enough */
			iface.init(CSR(SW_BASE, port[idx].sXtxlctl), SxTXCTL1_INIT);
		}
	}

	/* Restore the delays back */
	for (idx = 0; idx < DELAYS_CNT; idx++) {
		iface.init(CSR(SW_BASE, delay[idx].reg), delay[idx].def);
	}

	/* Initialize Temperature sensor values */
	iface.init(CSR(SW_BASE, TMPCTL), TMPCTL_INIT);

	/* Enable all reset pins of Expander #20 to workaround the Errata #19 */
	iface.init(CSR(SW_BASE, IOEXPINTF), IOEXPINTF_INIT);

	/* Put control sum to the last frame */
	iface.chksum();

	/* Add some empty blocks to make it loadable */
	iface.empty(256);
}
