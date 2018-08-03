/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file eeimg_cnccu.cpp
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */

#include <stdint.h>
#include "EEBasicBlock.h"
#include "img/idt_89hpesXt3.h"

/*! @var portx_base
 *   PCIe-switch port registers base addresses (Px_BASE)
 */
static const uint32_t portx_base[IDT_PORTCNT] = {P0_BASE,  P2_BASE,  P4_BASE};

/*! @fn void eeimg_cnccu(const char *fname)
 *   Write CNC CU EEPROM image
 *
 *  @param fname file name to write firmware to
 *  @exception EEEXception
 */
void eeimg_cnccu(const char *fname)
{
	EEBasicBlock iface(fname);
	int idx;

	/* Initialize GPIOFUNC register to select alternative functions of
	 * built-in GPIOs */
	iface.init(CSR(P0_BASE, GPIOFUNC), GPIOFUNC_INIT);

	/* Initialize IOEXPADDR1 register with SMBus GPIO-expander address */
	iface.init(CSR(P0_BASE, IOEXPADDR1), IOEXPADDR1_INIT);

	for (idx = 0; idx < IDT_PORTCNT; idx++) {
		/* Set L0s exit latency to 0x5 (errata #2) */
		if (idx == 0)
			iface.init(CSR(portx_base[idx], PCIELCAP), PCIELCAP_INIT_US);
		else
			iface.init(CSR(portx_base[idx], PCIELCAP), PCIELCAP_INIT_DS);

		/* Set PCIELCTL to send additional TS2s (errata #13) */
		iface.init(CSR(portx_base[idx], PCIELCTL), PCIELCTL_INIT);
	}

	/* Set SWCTL register to disable Downstream Device Number Checking */
	iface.init(CSR(P0_BASE, SWCTL), SWCTL_INIT);

	/* Set PHYLSTATE0 to initiate Full Link Retrain (errata #7) */
	//iface.init(CSR(P0_BASE, PHYLSTATE0), PHYLSTATE0_INIT);

	/* Put control sum to the last frame */
	iface.chksum();

	/* Add some empty blocks to make it loadable */
	iface.empty(256);
}
