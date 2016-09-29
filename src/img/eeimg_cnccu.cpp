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

/*! @fn void eeimg_cnccu(const char *fname)
 *   Write CNC CU EEPROM image
 *
 *  @param fname file name to write firmware to
 *  @exception EEEXception
 */
void eeimg_cnccu(const char *fname)
{
	EEBasicBlock iface(fname);

	/* Initialize GPIOFUNC register to select alternative functions of
	 * built-in GPIOs */
	iface.init(CSR(P0_BASE, GPIOFUNC), GPIOFUNC_INIT);

	/* Initialize IOEXPADDR1 register with SMBus GPIO-expander address */
	iface.init(CSR(P0_BASE, IOEXPADDR1), IOEXPADDR1_INIT);

	/* Put control sum to the last frame */
	iface.chksum();
}
