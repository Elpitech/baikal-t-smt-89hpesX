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

#include <stdint.h>
#include "EEExtBlock.h"
#include "img/idt_89hpesXnt8.h"

/*! @var ntx_base
 *   NT-function registers base addresses (NTx_BASE)
 */
static const uint32_t ntx_base[IDT_PORTCNT] = {NT0_BASE,  NT2_BASE,  NT4_BASE,
	NT6_BASE, NT8_BASE, NT12_BASE, NT16_BASE, NT20_BASE};

/*! @var usx_base
 *   Upstream function base addresses (USx_BASE)
 */
static const uint32_t usx_base[IDT_PORTCNT] = {US0_BASE,  US2_BASE,  US4_BASE,
	US6_BASE, US8_BASE, US12_BASE, US16_BASE, US20_BASE};

/*! @var delays
 *   IDT PCIe-switch boot delays
 */
static const uint32_t delays[DELAYS_CNT] = {RDRAINDELAY, POMCDELAY, SEDELAY,
	USSBRDELAY};

/*! @var nodelay
 *   IDT PCIe-switch boot zero-delays
 */
static const uint32_t nodelay[DELAYS_CNT] = {RDRAINDELAY_NODELAY,
	POMCDELAY_NODELAY, SEDELAY_NODELAY, USSBRDELAY_NODELAY};

/*! @var defdelay
 *   IDT PCIe-switch boot default delays
 */
static const uint32_t defdelay[DELAYS_CNT] = {RDRAINDELAY_DEFAULT,
	POMCDELAY_DEFAULT, SEDELAY_DEFAULT, USSBRDELAY_DEFAULT};

/*! @var swpartctl
 *   IDT PCIe-switch partition control registers (SW_BASE)
 */
static const uint32_t swpartctl[IDT_PARTCNT] = {SWPART0CTL, SWPART1CTL,
	SWPART2CTL, SWPART3CTL, SWPART4CTL, SWPART5CTL, SWPART6CTL, SWPART7CTL};

/*! @var swpartsts
 *   IDT PCIe-switch partition status registers (SW_BASE)
 */
static const uint32_t swpartsts[IDT_PARTCNT] = {SWPART0STS, SWPART1STS,
	SWPART2STS, SWPART3STS, SWPART4STS, SWPART5STS, SWPART6STS, SWPART7STS};

/*! @var swportctl
 *   IDT PCIe-switch port control registers (SW_BASE)
 */
static const uint32_t swportctl[IDT_PORTCNT] = {SWPORT0CTL, SWPORT2CTL,
	SWPORT4CTL, SWPORT6CTL, SWPORT8CTL, SWPORT12CTL, SWPORT16CTL, SWPORT20CTL};

/*! @var swportsts
 *   IDT PCIe-switch port status registers (SW_BASE)
 */
static const uint32_t swportsts[IDT_PORTCNT] = {SWPORT0STS, SWPORT2STS,
	SWPORT4STS, SWPORT6STS, SWPORT8STS, SWPORT12STS, SWPORT16STS, SWPORT20STS};

/*! @var swportmode
 *   IDT PCIe-switch port modes
 */
static const uint32_t swportmode[IDT_PORTCNT] = {SWPORTxCTL_MODE_USNT,
	SWPORTxCTL_MODE_DS, SWPORTxCTL_MODE_NT, SWPORTxCTL_MODE_NT,
	SWPORTxCTL_MODE_NT, SWPORTxCTL_MODE_NT, SWPORTxCTL_MODE_NT,
	SWPORTxCTL_MODE_NT};

/*! @var swportpart
 *   IDT PCIe-switch port partitions
 */
static const uint32_t swportpart[IDT_PORTCNT] = {0, 0, 1, 2, 3, 4, 5, 6};

/*! @fn void eeimg_cncbp(const char *fname)
 *   Write CNC BP EEPROM image
 *
 *  @param fname file name to write firmware to
 *  @exception EEEXception
 */
void eeimg_cncbp(const char *fname)
{
	EEExtBlock iface(fname);
	int idx;

	/* Drop all delays to speed the load up */
	for (idx = 0; idx < DELAYS_CNT; idx++) {
		iface.init(CSR(SW_BASE, delays[idx]), nodelay[idx]);
	}

	/* Initialize the ports clocking mode so the Port 0 works in local clock-mode
	 * and others have global clock */
	iface.init(CSR(SW_BASE, PCLKMODE), PCLKMODE_INIT);

	/* Mark all ports as having non-common clock mode */
	for (idx = 0; idx < IDT_PORTCNT; idx++) {
		iface.init(CSR(usx_base[idx], PCIELCTLSTS), PCIELCTLSTS_CLK_NONCOM);
		iface.init(CSR(ntx_base[idx], PCIELCTLSTS), PCIELCTLSTS_CLK_NONCOM);
	}

	/* Initialize the address of the link status/activity and reset GPIO-expanders
	 * IOE17 -> 0x74, IOE18 -> 0x75, IOE19 -> 0x76, IOE20 -> 0x77 */
	iface.init(CSR(SW_BASE, IOEXPADDR4), IOEXPADDR4_INIT);
	iface.init(CSR(SW_BASE, IOEXPADDR5), IOEXPADDR5_INIT);

	/* Initialize the port partitions 0-6 and wait until the change is done, then
	 * clear the status register */
	for (idx = 0; idx < (IDT_PARTCNT - 1); idx++) {
		/* Enable partition with idx */
		iface.init(CSR(SW_BASE, swpartctl[idx]), SWPARTxCTL_STATE_EN);
		/* Wait for partition state is changed */
		iface.wait(CSR(SW_BASE, swpartsts[idx]), SWPARTxSTS_SCC, SWPARTxSTS_SCC_UNMSK);
		/* Clear the status register */
		iface.init(CSR(SW_BASE, swpartsts[idx]), SWPARTxSTS_SCI_SCC_CLEAR);
	}

	/* Initialize the ports mode and wait until the change is done
	 * Port 0(US+NT), 2(DS) belong to partition 0
	 * Ports 4 - 20 (NT) respectively belong to the partitions 1 - 6
	 * Then clear the status register */
	for (idx = 0; idx < IDT_PORTCNT; idx++) {
		/* Initialize port mode (US, DS or NT) and partition it belongs to */
		iface.init(CSR(SW_BASE, swportctl[idx]),
				SWPORTxCTL_INIT(swportmode[idx], swportpart[idx]));
		/* Wait until the chages are made */
		iface.wait(CSR(SW_BASE, swportsts[idx]), SWPORTxSTS_OMCC, SWPORTxSTS_OMCC_UNMSK);
		/* Clear the status register */
		iface.init(CSR(SW_BASE, swportsts[idx]), SWPORTxSTS_OMCI_OMCC_CLEAR);
	}

	/* Enable the necessary BARs for all the NTB functions */
	for (idx = 0; idx < IDT_PORTCNT; idx++) {
		/* Skip port 2 since it has Downstream function enabled only */
		if (idx == 1)
			continue;
		/* BAR0 - Memory mapped Configuration space - x32 Non-prefetchable
		 * memory mapped space. Since it is the registers space then it must be
		 * non-prefetchable, which permits the 32-bits address only according
		 * to the PCI specs. Even though PCIe bridges doesn't do any prefetching
		 * whether prefetch bit is set or not, We'll set the bit as a matter of
		 * legacy */
		iface.init(CSR(ntx_base[idx], BARSETUP0), BARSETUP_CFG_32BIT);
		/* BAR1 - Shared memory window with direct address translation - x32
		 * Non-prefetchable memory mapped space with aperture of
		 * 2^DIRMW_1MB_APRT, which effectively gives 1Mb of memory space per
		 * each memory window */
		iface.init(CSR(ntx_base[idx], BARSETUP1),
				BARSETUP_DIRMW_32BIT | DIRMW_1MB_APRT);
		/* BAR2 + BAR3 - Shared memory windows with address translation
		 * based on lookup table - x64 Non-prefetchable memory mapped space
		 * with aperture of 2^LUMW_1MB_APRT, which effectively gives 1Mb of
		 * memory space per each memory window */
		iface.init(CSR(ntx_base[idx], BARSETUP2),
				BARSETUP_24LUMW_64BIT | LUMW_1MB_APRT);
		/* BAR4 + BAR5 - Shared memory window with direct address translation -
		 * x64 Non-prefetchable memory mapped space with aperture of
		 * 2^DIRMW_1MB_APRT, which effectively gives 1Mb of memory space per
		 * each memory window */
		iface.init(CSR(ntx_base[idx], BARSETUP4),
				BARSETUP_DIRMW_64BIT | DIRMW_1MB_APRT);
	}

	/* Setup NTSDATA register to declare just one Primary port and
	 * multiple Secondary ones:
	 *  Port 0 - Primary port,
	 *  Port 4 - 20 - secondary ports (six ports altogether) */
	for (idx = 0; idx < IDT_PORTCNT; idx++)
		iface.init(CSR(ntx_base[idx], NTSDATA), NTSDATA_PORT0_PRI);

	/* Restore the delays back */
	for (idx = 0; idx < DELAYS_CNT; idx++) {
		iface.init(CSR(SW_BASE, delays[idx]), defdelay[idx]);
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
