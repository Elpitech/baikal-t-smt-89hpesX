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
 *   NT registers base addresses
 */
#define NT0_BASE	((uint32_t)0x01000)
#define NT2_BASE	((uint32_t)0x05000)
#define NT4_BASE	((uint32_t)0x09000)
#define NT6_BASE	((uint32_t)0x0D000)
#define NT8_BASE	((uint32_t)0x11000)
#define NT12_BASE	((uint32_t)0x19000)
#define NT16_BASE	((uint32_t)0x21000)
#define NT20_BASE	((uint32_t)0x29000)

/*! @def USx_BASE
 *   Upstream ports registers base addresses
 */
#define US0_BASE	((uint32_t)0x00000)
#define US2_BASE	((uint32_t)0x04000)
#define US4_BASE	((uint32_t)0x08000)
#define US6_BASE	((uint32_t)0x0C000)
#define US8_BASE	((uint32_t)0x10000)
#define US12_BASE	((uint32_t)0x18000)
#define US16_BASE	((uint32_t)0x20000)
#define US20_BASE	((uint32_t)0x28000)

/*! @def SW_BASE
 *   Global registers base addresses
 */
#define SW_BASE		((uint32_t)0x3E000)

/*! @def PCIELCTLSTS
 *   IDT 89HPESxNT8 PCIe link control/status (NTx_BASE)
 */
#define PCIELCTLSTS	((uint32_t)0x00050)

/*! @def ACSCAP
 *   IDT 89HPESxNT8 PCIe ACS capability register (USx_BASE)
 */
#define ACSCAP		((uint32_t)0x00324)

/*! @def SERDESCFG
 *   IDT 89HPESxNT8 PCe-port SerDes Configuration (USx_BASE)
 */
#define SERDESCFG	((uint32_t)0x00510)

/*! @def NTSDATA
 *   IDT 89HPESxNT8 NT-function data register (NTx_BASE)
 */
#define NTSDATA		((uint32_t)0x0040C)

/*! @def BARx
 *   IDT 89HPESxNT8 BAR setup registers
 */
#define BARSETUP0	((uint32_t)0x00470)
#define BARLIMIT0	((uint32_t)0x00474)
#define BARSETUP1	((uint32_t)0x00480)
#define BARLIMIT1	((uint32_t)0x00484)
#define BARSETUP2	((uint32_t)0x00490)
#define BARLIMIT2	((uint32_t)0x00494)
#define BARSETUP3	((uint32_t)0x004A0)
#define BARLIMIT3	((uint32_t)0x004A4)
#define BARSETUP4	((uint32_t)0x004B0)
#define BARLIMIT4	((uint32_t)0x004B4)
#define BARSETUP5	((uint32_t)0x004C0)
#define BARLIMIT5	((uint32_t)0x004C4)

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

/*! @def SxTXLCTL1
 *   IDT 89HPESxNT8 SerDes x Tramitter Lane Control 1 on (SW_BASE)
 */
#define S0TXLCTL1		((uint32_t)0x01008)
#define S1TXLCTL1		((uint32_t)0x01028)
#define S2TXLCTL1		((uint32_t)0x01048)
#define S3TXLCTL1		((uint32_t)0x01068)
#define S4TXLCTL1		((uint32_t)0x01088)
#define S5TXLCTL1		((uint32_t)0x010A8)
#define S6TXLCTL1		((uint32_t)0x010C8)
#define S7TXLCTL1		((uint32_t)0x010E8)

/*! @def IOEXPINTF
 *   IDT 89HPESxNT8 SMBus GPIO-expanders test register
 */
#define IOEXPINTF		((uint32_t)0x01194)

/*! @def IOEXPADDR*
 *   IDT 89HPESxNT8 SMBus GPIO-expanders
 */
#define IOEXPADDR0		((uint32_t)0x01198)
#define IOEXPADDR1		((uint32_t)0x0119C)
#define IOEXPADDR2		((uint32_t)0x011A0)
#define IOEXPADDR3		((uint32_t)0x011A4)
#define IOEXPADDR4		((uint32_t)0x011A8)
#define IOEXPADDR5		((uint32_t)0x011AC)

/*! @def TMLCTL
 *   Temperature sensor control register
 */
#define TMPCTL			((uint32_t)0x011D4)

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

/*! @def ACSCAP_*
 *   Field of the ACSCAP PCIe-switch register
 *
 *  Set/unset corresponding modes of ACS
 */
#define ACSCAP_R_FLD 2
#define ACSCAP_C_FLD 3
#define ACSCAP_T_FLD 6
#define ACSCAP_R ((uint32_t)1 << ACSCAP_R_FLD)
#define ACSCAP_C ((uint32_t)1 << ACSCAP_C_FLD)
#define ACSCAP_T ((uint32_t)1 << ACSCAP_T_FLD)
#define ACSCAP_INIT \
	(~ACSCAP_R & ~ACSCAP_C & ~ACSCAP_T)

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

/*! @def PCIELCTLSTS_CLK
 *   Field of the PCIELCTLSTS PCIe-switch register
 *
 *  Set clock common/non-common mode of ports
 */
#define PCIELCTL_CCLK_FLD 6
#define PCIELCTL_CCLK_COM ((uint32_t)0x1 << PCIELCTL_CCLK_FLD)
#define PCIELCTL_CCLK_NONCOM ((uint32_t)0x0 << PCIELCTL_CCLK_FLD)
#define PCIELSTS_SCLK_FLD 28
#define PCIELSTS_SCLK_COM ((uint32_t)0x1 << PCIELSTS_SCLK_FLD)
#define PCIELSTS_SCLK_NONCOM ((uint32_t)0x0 << PCIELSTS_SCLK_FLD)
#define PCIELCTLSTS_CLK_NONCOM \
	(PCIELCTL_CCLK_NONCOM | PCIELSTS_SCLK_NONCOM)

/*****************************************************************************/

/*! @def SERDESCFG_LSE
 *   Fields of the SERDESCFG PCIe-switch register
 *
 *  Disbale/Enable Low-Swing configs
 */
#define SERDESCFG_LSE_FLD 16
#define SERDESCFG_LSE_EN ((uint32_t)0x1 << SERDESCFG_LSE_FLD)
#define SERDESCFG_LSE_DIS ((uint32_t)0x0 << SERDESCFG_LSE_FLD)

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
#define SWPORTxCTL_DNUM_FLD 10
#define SWPORTxCTL_OMA_FLD  16
#define SWPORTxCTL_MODE_DIS  ((uint32_t)0x0 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_DS ((uint32_t)0x1 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_US ((uint32_t)0x2 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_NT ((uint32_t)0x3 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_USNT ((uint32_t)0x4 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_UNA ((uint32_t)0x5 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_USD ((uint32_t)0x6 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_MODE_NTD ((uint32_t)0x7 << SWPORTxCTL_MODE_FLD)
#define SWPORTxCTL_OMA_RESET ((uint32_t)0x1 << SWPORTxCTL_OMA_FLD)

/*! @def SWPORTxCTL_INIT
 *   Macros to init the PCIe-switch port MODE and PARTition
 */
#define SWPORTxCTL_INIT(mode, dnum, part) \
	    ((uint32_t)(mode) | ((uint32_t)(dnum) << SWPORTxCTL_DNUM_FLD) | \
		 ((uint32_t)(part) << SWPORTxCTL_PART_FLD) | SWPORTxCTL_OMA_RESET)

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

/*! @def SxTXCTL1
 *   Fields of the SxTXCTL1 PCIe-switch register
 *
 *  Set SerDes x Transmitter Lane Control 1 settings
 */
#define SxTXCTL1_TDVL_FS3DBG1_FLD	0
#define SxTXCTL1_CDC_FS3DBG1_FLD	5
#define SxTXCTL1_TDVL_FS3DBG2_FLD	8
#define SxTXCTL1_CDC_FS3DBG2_FLD	13
#define SxTXCTL1_TDVL_FS6DBG2_FLD	16
#define SxTXCTL1_CDC_FS6DBG2_FLD	21
#define SxTXCTL1_TDVL_LSG1_FLD		24
#define SxTXCTL1_TDVL_LSG2_FLD		28
#define SxTXCTL1_TDVL_FS3DBG1		((uint32_t)0x12 << SxTXCTL1_TDVL_FS3DBG1_FLD)
#define SxTXCTL1_CDC_FS3DBG1		((uint32_t)0x3 << SxTXCTL1_CDC_FS3DBG1_FLD)
#define SxTXCTL1_TDVL_FS3DBG2		((uint32_t)0x18 << SxTXCTL1_TDVL_FS3DBG2_FLD)
#define SxTXCTL1_CDC_FS3DBG2		((uint32_t)0x3 << SxTXCTL1_CDC_FS3DBG2_FLD)
#define SxTXCTL1_TDVL_FS6DBG2		((uint32_t)0x15 << SxTXCTL1_TDVL_FS6DBG2_FLD)
#define SxTXCTL1_CDC_FS6DBG2		((uint32_t)0x6 << SxTXCTL1_CDC_FS6DBG2_FLD)
#define SxTXCTL1_TDVL_LSG1			((uint32_t)0x3 << SxTXCTL1_TDVL_LSG1_FLD)
#define SxTXCTL1_TDVL_LSG2			((uint32_t)0x4 << SxTXCTL1_TDVL_LSG2_FLD)
// Default
//#define SxTXCTL1_TDVL_LSG1			((uint32_t)0xA << SxTXCTL1_TDVL_LSG1_FLD)
//#define SxTXCTL1_TDVL_LSG2			((uint32_t)0xC << SxTXCTL1_TDVL_LSG2_FLD)
#define SxTXCTL1_INIT \
	(SxTXCTL1_TDVL_FS3DBG1 | SxTXCTL1_CDC_FS3DBG1 | \
	 SxTXCTL1_TDVL_FS3DBG2 | SxTXCTL1_CDC_FS3DBG2 | \
	 SxTXCTL1_TDVL_FS6DBG2 | SxTXCTL1_CDC_FS6DBG2 | \
	 SxTXCTL1_TDVL_LSG1 | SxTXCTL1_TDVL_LSG2)

/*****************************************************************************/

/*! @def IOEXPINTF_*
 *   Fields of the IOEXPINTF PCIe-switch register
 *
 *  Use the GPIO-expanders test register to workaround Errata #9
 */
#define IOEXPINTF_IOEDATA_FLD 0
#define IOEXPINTF_IOEXTM_FLD  25
#define IOEXPINTF_SELECT_FLD  26
#define IOEXPINTF_IOEDATA_EXP20 ((uint32_t)0xFFFF << IOEXPINTF_IOEDATA_FLD)
#define IOEXPINTF_IOEXTM ((uint32_t)1 << IOEXPINTF_IOEXTM_FLD)
#define IOEXPINTF_SELECT_EXP20 ((uint32_t)0x14 << IOEXPINTF_SELECT_FLD)
#define IOEXPINTF_INIT \
	(IOEXPINTF_IOEDATA_EXP20 | IOEXPINTF_IOEXTM | IOEXPINTF_SELECT_EXP20)

/*! @def IOExADDR
 *   PCIe-switch GPIO-expaners addresses
 *
 *  @IOE17ADDR - P0..P12 link up output status
 *  @IOE18ADDR - P0..P12 link active status
 *  @IOE19ADDR - P16..P20 link up/link active status
 *  @IOE20ADDR - P0..P20 reset output, P0...P7 fundamental reset input
 */
#define IOE17ADDR (uint8_t)0x74
#define IOE18ADDR (uint8_t)0x76
#define IOE19ADDR (uint8_t)0x75
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

/*
 * IDT PCIe-switch NTB function BAR setup parameters:
 * @BARSETUP_CFG_32BIT:		32-bits BAR0 mapping non-prefetchable memory
 *							mapped registers configuration space
 * @BARSETUP_CFG_64BIT:		64-bits BAR{0,1} mapping prefetchable memory
 *							mapped registers configuration space
 * @BARSETUP_DIRMW_32BIT:	32-bits BARx mapping prefetchable direct
 *							address translatable memory window
 * @BARSETUP_DIRMW_64BIT:	64-bits BARx mapping prefetchable direct
 *							address translatable memory window
 * @BARSETUP_12LUMW_32BIT:	32-bits BARx mapping prefetchable 12-entries
 *							lookup table memory window
 * @BARSETUP_12LUMW_64BIT:	64-bits BARx mapping prefetchable 12-entries
 *							lookup table memory window
 * @BARSETUP_24LUMW_32BIT:	32-bits BARx mapping prefetchable 24-entries
 *							lookup table memory window
 * @BARSETUP_24LUMW_64BIT:	64-bits BARx mapping prefetchable 24-entries
 *							lookup table memory window
 */
#define BARSETUP_CFG_32BIT		((uint32_t)0x800004C0U)
#define BARSETUP_CFG_64BIT		((uint32_t)0x800004CCU)
#define BARSETUP_DIRMW_32BIT	((uint32_t)0x80000008U)
#define BARSETUP_DIRMW_64BIT	((uint32_t)0x8000000CU)
#define BARSETUP_12LUMW_32BIT	((uint32_t)0x80000808U)
#define BARSETUP_12LUMW_64BIT	((uint32_t)0x8000080CU)
#define BARSETUP_24LUMW_32BIT	((uint32_t)0x80001008U)
#define BARSETUP_24LUMW_64BIT	((uint32_t)0x8000100CU)
#define MWAPRT_OFF				4

/*
 * IDT PCIe-switch NTB function related parameters:
 * @DEFAULT_MW_APRT:	Default aperture of the memory windows (that is
 *						maximum size of the memory windows)
 * @MIN_MW_APRT:		Minimum possible aperture of the memory windows
 * @MAX_X86_MW_APRT:	Maximum aperture for x86 architecture
 * @MAX_X64_MW_APRT:	Maximum aperture for x64 architecture
 * @MWLUTBL_APRT:		Additional value to translate the per memory
 *						windows specific aperture to the aperture of
 *						the whole lookup table
 * @LUMW_1MB_APRT:		BARx aperture to get 1Mb lookup table MWs
 * @DIRMW_1MB_APRT:		BARx aperture to get 1Mb direct translated MWs
 */
#define DEFAULT_MW_APRT	(uint32_t)20
#define MIN_MW_APRT		(uint32_t)9
#define MAX_X86_MW_APRT	(uint32_t)26
#define MAX_X64_MW_APRT	(uint32_t)32
#define MWLUTBL_APRT	(uint32_t)5
#define LUMW_1MB_APRT	((DEFAULT_MW_APRT + MWLUTBL_APRT) << MWAPRT_OFF)
#define DIRMW_1MB_APRT	((DEFAULT_MW_APRT) << MWAPRT_OFF)

/*****************************************************************************/

/*
 * IDT PCIe-switch Temperature sensor control parameters:
 * @TMPCTL_PDOWN:	Power down
 */
#define TMPCTL_PDOWN_FLD	31
#define TMPCTL_PDOWN		((uint32_t)0 << TMPCTL_PDOWN_FLD)
#define TMPCTL_INIT \
		TMPCTL_PDOWN

#endif /* IDT_89HPESXNT8_H */

