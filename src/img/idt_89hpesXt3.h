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

/*! @def PCIELCTL
 *   IDT 89HPESxT3 Switch link capability
 */
#define PCIELCAP		((uint32_t)0x004C)

/*! @def PCIELCTL
 *   IDT 89HPESxT3 Switch link control register
 */
#define PCIELCTL		((uint32_t)0x0050)

/*! @def SWCTL
 *   IDT 89HPESxT3 Switch control register (P0_BASE)
 */
#define SWCTL			((uint32_t)0x0404)

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

/*! @def PHYLSTATE0
 *   IDT 89HPESxT3 PHY link state register
 */
#define PHYLSTATE0		((uint32_t)0x0534)

/*****************************************************************************/

/*! @def PCIELCAP
 *   Fields of the PCIELCAP PCIe-switch register
 */
#define PCIELCAP_MAXLNKWDTH_FLD	4
#define PCIELCAP_MAXLNKWDTH		((uint32_t)0x4 << PCIELCAP_MAXLNKWDTH_FLD)
#define PCIELCAP_L0SEL_FLD		12
#define PCIELCAP_L0SEL			((uint32_t)0x5 << PCIELCAP_L0SEL_FLD)
#define PCIELCAP_L1EL_FLD		15
#define PCIELCAP_L1EL			((uint32_t)0x2 << PCIELCAP_L1EL_FLD)
#define PCIELCAP_SDERR_DLLLA_LBN_FLD		19
#define PCIELCAP_SDERR_DLLLA_LBN_DS			((uint32_t)0x7 << PCIELCAP_SDERR_DLLLA_LBN_FLD)
#define PCIELCAP_INIT_US \
	(PCIELCAP_MAXLNKWDTH | PCIELCAP_L0SEL | PCIELCAP_L1EL)
#define PCIELCAP_INIT_DS \
	(PCIELCAP_MAXLNKWDTH | PCIELCAP_L0SEL | PCIELCAP_L1EL | \
	 PCIELCAP_SDERR_DLLLA_LBN_DS)

/*****************************************************************************/

/*! @def PCIELCTL
 *   Fields of the PCIELCTL PCIe-switch register
 */
#define PCIELCTL_ESYNC_FLD	7
#define PCIELCTL_ESYNC		((uint32_t)1 << PCIELCTL_ESYNC_FLD)
#define PCIELCTL_INIT \
	(PCIELCTL_ESYNC)

/*****************************************************************************/

/*! @def SWCTL
 *   Fields of the SWCTL PCIe-switch register
 */
#define SWCTL_DDDNC_FLD		9
#define SWCTL_DDDNC_ALL		((uint32_t)0x0 << SWCTL_DDDNC_FLD)
#define SWCTL_DDDNC_CFG		((uint32_t)0x1 << SWCTL_DDDNC_FLD)
#define SWCTL_DDDNC_NON		((uint32_t)0x2 << SWCTL_DDDNC_FLD)
#define SWCTL_R64BAB4GB_FLD	13
#define SWCTL_R64BAB4GB		((uint32_t)1 << SWCTL_R64BAB4GB_FLD)
#define SWCTL_INIT \
	(SWCTL_DDDNC_NON | SWCTL_R64BAB4GB)

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
#define IOE4ADDR (uint8_t)0x74

/*! @def IOEXPADDR1_*
 *   Fields of the IOEXPADDR4 PCIe-switch register
 *
 *  Set the expanders to enable the corresponding LEDs when the port link is
 *  active
 */
#define IOEXPADDR1_IOE4ADDR_FLD 1
#define IOEXPADDR1_INIT \
	    ((uint32_t)IOE4ADDR << IOEXPADDR1_IOE4ADDR_FLD)

/*****************************************************************************/

/*! @def PHYLSTATE0
 *   Fields of the PHYLSTATE0 PCIe-switch register
 */
#define PHYLSTATE0_FLRET_FLD	31
#define PHYLSTATE0_FLRET		((uint32_t)1 << PHYLSTATE0_FLRET_FLD)
#define PHYLSTATE0_INIT \
	(PHYLSTATE0_FLRET)

#endif /* IDT_89HPESXT3_H */

