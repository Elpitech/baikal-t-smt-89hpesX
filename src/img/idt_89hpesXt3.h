/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file idt_89hpesXnt8.h
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date Sempteber, 2016
 *   @brief
 *
 *   Details about the file
 */
#ifndef IDT_89HPESXT3_H
#define IDT_89HPESXT3_H

#include <stdint.h>

/*! @def CSR(base, reg)
 *   Form CSR address
 */
#define CSR(base, reg) \
	(base | reg)

/*! @def IDT_PORTCNT
 *   Number of ports
 */
#define IDT_PORTCNT		(3)

/*! @def NTx_BASE
 *   NT base registers
 */
#define P0_BASE	((uint32_t)0x0)
#define P2_BASE	((uint32_t)0x2000)
#define P4_BASE	((uint32_t)0x4000)

/*! @def GPIO*
 *   IDT 89HPESxT3 GPIO* related registers (P0_BASE)
 */
#define GPIOFUNC		((uint32_t)0x0418)
#define GPIOCFG			((uint32_t)0x041C)
#define GPIOD			((uint32_t)0x0420)

/*! @def IOEXPADDR*
 *   IDT 89HPESxT3 SMBus GPIO-expanders
 */
#define IOEXPADDR0		((uint32_t)0x0434)
#define IOEXPADDR1		((uint32_t)0x0438)

/*****************************************************************************/

/*! @def GPIOFUNC_*
 *   Fields of the GPIOFUNC PCIe-switch register
 */
#define GPIOFUNC_PE2RSTN_FLD 0
#define GPIOFUNC_PE4RSTN_FLD 1
#define GPIOFUNC_IOEXPINTN0_FLD 2
#define GPIOFUNC_IOEXPINTN2_FLD 4
#define GPIOFUNC_GPEN_FLD 7
#define GPIOFUNC_ALTFUNC_EN(fld)  ((uint32_t)0x1 << fld)
#define GPIOFUNC_INIT \
	(GPIOFUNC_ALTFUNC_EN(GPIOFUNC_PE2RSTN_FLD) | \
	 GPIOFUNC_ALTFUNC_EN(GPIOFUNC_PE4RSTN_FLD))

/*****************************************************************************/

/*! @def IOExADDR
 *   PCIe-switch GPIO-expaners addresses
 *
 *  @IOE4ADDR - P0..P4 link up/activity status
 */
#define IOE4ADDR (uint8_t)0x70

/*! @def IOEXPADDR1_*
 *   Fields of the IOEXPADDR4 PCIe-switch register
 *
 *  Set the expanders to enable the corresponding LEDs when the port link is
 *  active
 */
#define IOEXPADDR1_IOE4ADDR_FLD 1
#define IOEXPADDR1_INIT \
	    ((uint32_t)IOE4ADDR << IOEXPADDR1_IOE4ADDR_FLD)

#endif /* IDT_89HPESXT3_H */

