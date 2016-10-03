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
#ifndef IDT_89HPESXNT8_H
#define IDT_89HPESXNT8_H

#include <stdint.h>

/*! @def CSR(base, reg)
 *   Form CSR address
 */
#define CSR(base, reg) \
	(base | reg)

/*! @def IDT_PORTCNT/IDT_PARTCNT
 *   Number of ports and partitions
 */
#define IDT_PORTCNT		(8)
#define IDT_PARTCNT		(8)

/*! @def NTx_BASE
 *   NT base registers
 */
#define NT0_BASE	((uint32_t)0x01000)
#define NT2_BASE	((uint32_t)0x05000)
#define NT4_BASE	((uint32_t)0x09000)
#define NT6_BASE	((uint32_t)0x0D000)
#define NT8_BASE	((uint32_t)0x11000)
#define NT12_BASE	((uint32_t)0x19000)
#define NT16_BASE	((uint32_t)0x21000)
#define NT20_BASE	((uint32_t)0x29000)
#define SW_BASE		((uint32_t)0x3E000)

/*! @def PCIELSTS
 *   IDT 89HPESxNT8 PCIe link status (NTx_BASE)
 */
#define PCIELSTS	((uint32_t)0x00052)

/*! @def NTSDATA
 *   IDT 89HPESxNT8 NT-function data register (NTx_BASE)
 */
#define NTSDATA		((uint32_t)0x0040C)

/*! @def PCLKMODE
 *   IDT 89HPESxNT8 clock mode (SW_BASE)
 */
#define PCLKMODE		((uint32_t)0x00008)

/*! @def *DELAY
 *   IDT 89HPESxNT8 init delays (SW_BASE)
 */
#define RDRAINDELAY		((uint32_t)0x00080)
#define POMCDELAY		((uint32_t)0x00084)
#define SEDELAY			((uint32_t)0x00088)
#define USSBRDELAY		((uint32_t)0x0008C)
#define BASE_DELAY		RDRAINDELAY
#define DELAYS_CNT		(4)

/*! @def SWPARTxCTL/SWPARTxSTS
 *   IDT 89HPESxNT8 partition control and status (SW_BASE)
 */
#define SWPART0CTL		((uint32_t)0x00100)
#define SWPART0STS		((uint32_t)0x00104)
#define SWPART1CTL		((uint32_t)0x00120)
#define SWPART1STS		((uint32_t)0x00124)
#define SWPART2CTL		((uint32_t)0x00140)
#define SWPART2STS		((uint32_t)0x00144)
#define SWPART3CTL		((uint32_t)0x00160)
#define SWPART3STS		((uint32_t)0x00164)
#define SWPART4CTL		((uint32_t)0x00180)
#define SWPART4STS		((uint32_t)0x00184)
#define SWPART5CTL		((uint32_t)0x001A0)
#define SWPART5STS		((uint32_t)0x001A4)
#define SWPART6CTL		((uint32_t)0x001C0)
#define SWPART6STS		((uint32_t)0x001C4)
#define SWPART7CTL		((uint32_t)0x001E0)
#define SWPART7STS		((uint32_t)0x001E4)

/*! @def SWPORTxCTL/SWPORTxSTS
 *   IDT 89HPESxNT8 ports control and status (SW_BASE)
 */
#define SWPORT0CTL		((uint32_t)0x00200)
#define SWPORT0STS		((uint32_t)0x00204)
#define SWPORT2CTL		((uint32_t)0x00240)
#define SWPORT2STS		((uint32_t)0x00244)
#define SWPORT4CTL		((uint32_t)0x00280)
#define SWPORT4STS		((uint32_t)0x00284)
#define SWPORT6CTL		((uint32_t)0x002C0)
#define SWPORT6STS		((uint32_t)0x002C4)
#define SWPORT8CTL		((uint32_t)0x00300)
#define SWPORT8STS		((uint32_t)0x00304)
#define SWPORT12CTL		((uint32_t)0x00380)
#define SWPORT12STS		((uint32_t)0x00384)
#define SWPORT16CTL		((uint32_t)0x00400)
#define SWPORT16STS		((uint32_t)0x00404)
#define SWPORT20CTL		((uint32_t)0x00480)
#define SWPORT20STS		((uint32_t)0x00484)

/*! @def IOEXPADDR*
 *   IDT 89HPESxNT8 SMBus GPIO-expanders
 */
#define IOEXPADDR0		((uint32_t)0x01198)
#define IOEXPADDR1		((uint32_t)0x0119C)
#define IOEXPADDR2		((uint32_t)0x011A0)
#define IOEXPADDR3		((uint32_t)0x011A4)
#define IOEXPADDR4		((uint32_t)0x011A8)
#define IOEXPADDR5		((uint32_t)0x011AC)

/*****************************************************************************/

/*! @def RDRAINDELAY_*
 *   Field of the DRAINDELAY PCIe-switch register
 */
#define RDRAINDELAY_FLD 0
#define RDRAINDELAY_NODELAY ((uint32_t)0x0 << RDRAINDELAY_FLD)
#define RDRAINDELAY_DEFAULT ((uint32_t)0x0FA << RDRAINDELAY_FLD)

/*! @def POMCDELAY_*
 *   Field of the POMCDELAY PCIe-switch register
 */
#define POMCDELAY_FLD 0
#define POMCDELAY_NODELAY ((uint32_t)0x0 << POMCDELAY_FLD)
#define POMCDELAY_DEFAULT ((uint32_t)0x03E8 << POMCDELAY_FLD)

/*! @def SEDELAY_*
 *   Field of the SEDELAY PCIe-switch register
 */
#define SEDELAY_FLD 0
#define SEDELAY_NODELAY ((uint32_t)0x0 << SEDELAY_FLD)
#define SEDELAY_DEFAULT ((uint32_t)0x03E8 << SEDELAY_FLD)

/*! @def USSBRDELAY_*
 *   Field of the USSBRDELAY PCIe-switch register
 */
#define USSBRDELAY_FLD 0
#define USSBRDELAY_NODELAY ((uint32_t)0x0 << USSBRDELAY_FLD)
#define USSBRDELAY_DEFAULT ((uint32_t)0x0 << USSBRDELAY_FLD)

/*****************************************************************************/

/*! @def Px_CLKMODE_*
 *   Fields of the PCLKMODE PCIe-switch register
 *
 *  Set the ports clocking Global/Local modes
 */
#define P0_1_CLKMODE_FLD 0
#define P2_3_CLKMODE_FLD 2
#define P4_5_CLKMODE_FLD 4
#define P6_7_CLKMODE_FLD 6
#define P8_11_CLKMODE_FLD 8
#define P12_15_CLKMODE_FLD 10
#define P16_19_CLKMODE_FLD 12
#define P20_23_CLKMODE_FLD 14
#define PxCLKMODE_GLOBAL(port_fld)  ((uint32_t)0x0 << port_fld)
#define PxCLKMODE_LOCAL(port_fld)  ((uint32_t)0x1 << port_fld)

/*! @def PCLKMODE_INIT
 *   Macros to init the PCIe-switch port PCLKMODE
 */
#define PCLKMODE_INIT \
	(PxCLKMODE_GLOBAL(P0_1_CLKMODE_FLD) | \
	 PxCLKMODE_GLOBAL(P2_3_CLKMODE_FLD) | \
	 PxCLKMODE_GLOBAL(P4_5_CLKMODE_FLD) | \
	 PxCLKMODE_GLOBAL(P6_7_CLKMODE_FLD) | \
	 PxCLKMODE_GLOBAL(P8_11_CLKMODE_FLD) | \
	 PxCLKMODE_GLOBAL(P12_15_CLKMODE_FLD) | \
	 PxCLKMODE_GLOBAL(P16_19_CLKMODE_FLD) | \
	 PxCLKMODE_GLOBAL(P20_23_CLKMODE_FLD))

/*! @def PCIELSTS_SCK
 *   Field of the PCIELSTS PCIe-switch register
 *
 *  Set clock common/non-common mode of ports
 */
#define PCIELSTS_SCK_FLD 12
#define PCIELSTS_SCK_COM ((uint32_t)0x1 << PCIELSTS_SCK_FLD)
#define PCIELSTS_SCK_NONCOM ((uint32_t)0x0 << PCIELSTS_SCK_FLD)

/*****************************************************************************/

/*! @def SWPARTxCTL_STATE_*
 *   Field of the SWPARTxCTL PCIe-switch register
 *
 *  Disbale/Enable the corresponding partition
 */
#define SWPARTxCTL_STATE_FLD 0
#define SWPARTxCTL_STATE_EN ((uint32_t)0x1 << SWPARTxCTL_STATE_FLD)
#define SWPARTxCTL_STATE_DIS ((uint32_t)0x0 << SWPARTxCTL_STATE_FLD)

/*! @def SWPARTxSTS_SCI/SWPARTxSTS_SCC
 *   Field of the SWPARTxCTL PCIe-switch register
 *
 *  Check whether the partition state has changed
 */
#define SWPARTxSTS_SCI_FLD 0
#define SWPARTxSTS_SCC_FLD 1
#define SWPARTxSTS_SCI ((uint32_t)1 << SWPARTxSTS_SCI_FLD)
#define SWPARTxSTS_SCC ((uint32_t)1 << SWPARTxSTS_SCC_FLD)
#define SWPARTxSTS_SCC_UNMSK (~SWPARTxSTS_SCC)
#define SWPARTxSTS_SCI_SCC_CLEAR \
	    (SWPARTxSTS_SCI | SWPARTxSTS_SCC)

/*****************************************************************************/

/*! @def SWPORTxCTL_MODE/SWPORTxCTL_PART
 *   Fields of the SWPORTxCTL PCIe-switch register
 *
 *  Set the ports mode and partitions
 */
#define SWPORTxCTL_MODE_FLD 0
#define SWPORTxCTL_PART_FLD 4
#define SWPORTxCTL_MODE_DIS  ((uint32_t)0x0 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_DS ((uint32_t)0x1 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_US ((uint32_t)0x2 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_NT ((uint32_t)0x3 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_USNT ((uint32_t)0x4 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_UNA ((uint32_t)0x5 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_USD ((uint32_t)0x6 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_NTD ((uint32_t)0x7 << SWPORTxCTL_MODE_FLD)

/*! @def SWPORTxCTL_INIT
 *   Macros to init the PCIe-switch port MODE and PARTition
 */
#define SWPORTxCTL_INIT(mode, part) \
	    ((uint32_t)(mode) | ((uint32_t)(part) << SWPORTxCTL_PART_FLD))

/*! @def SWPORTxSTS_OMCC/SWPORTxSTS_OMCI
 *   Fields of the SWPORTxCTL PCIe-switch register
 *
 *  Check whether the port mode has changed
 */
#define SWPORTxSTS_OMCI_FLD 0
#define SWPORTxSTS_OMCC_FLD 1
#define SWPORTxSTS_OMCI ((uint32_t)1 << SWPORTxSTS_OMCI_FLD)
#define SWPORTxSTS_OMCC ((uint32_t)1 << SWPORTxSTS_OMCC_FLD)
#define SWPORTxSTS_OMCC_UNMSK (~SWPORTxSTS_OMCC)
#define SWPORTxSTS_OMCI_OMCC_CLEAR \
	    (SWPORTxSTS_OMCI | SWPORTxSTS_OMCC)

/*****************************************************************************/

/*! @def IOExADDR
 *   PCIe-switch GPIO-expaners addresses
 *
 *  @IOE17ADDR - P0..P12 link up output status
 *  @IOE18ADDR - P0..P12 link active status
 *  @IOE19ADDR - P16..P20 link up/link active status
 *  @IOE20ADDR - P0..P20 reset output, P0...P7 fundamental reset input
 */
#define IOE17ADDR (uint8_t)0x74
#define IOE18ADDR (uint8_t)0x75
#define IOE19ADDR (uint8_t)0x76
#define IOE20ADDR (uint8_t)0x77

/*! @def IOEXPADDR4_*
 *   Fields of the IOEXPADDR4 PCIe-switch register
 *
 *  Set the expanders to enable the corresponding LEDs when the port link is
 *  active
 */
#define IOEXPADDR4_IOE17ADDR_FLD 9
#define IOEXPADDR4_IOE18ADDR_FLD 17
#define IOEXPADDR4_IOE19ADDR_FLD 25
#define IOEXPADDR4_INIT \
	    ((uint32_t)IOE17ADDR << IOEXPADDR4_IOE17ADDR_FLD | \
		 (uint32_t)IOE18ADDR << IOEXPADDR4_IOE18ADDR_FLD | \
		 (uint32_t)IOE19ADDR << IOEXPADDR4_IOE19ADDR_FLD)

/*! @def IOEXPADDR5_
 *   Fields of the IOEXPADDR5 PCIe-switch register
 *
 *  Set the expanders to perform ports reset output and retrieve fundamental
 *  reset intput
 */
#define IOEXPADDR5_IOE20ADDR_FLD 1
#define IOEXPADDR5_INIT \
	    ((uint32_t)IOE20ADDR << IOEXPADDR5_IOE20ADDR_FLD)

/*****************************************************************************/

/*! @def NTSDATA
 *   NT-function private datae register
 *
 *  NTSDATA is predefined with the port number, which is primary for the
 *  corresponding port. According to our specification it's going to be port 0.
 */
#define NTSDATA_PORT0_PRI ((uint32_t)0)

#endif /* IDT_89HPESXNT8_H */

