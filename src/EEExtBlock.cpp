/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file EEExtBlock.cpp
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */

#include <cassert>
#include <endian.h>
#include "EEExtBlock.h"
#include "EEAlloc.h"
#include "EEException.h"

/*! @fn void EEExtBlock::init(uint32_t csr, uint32_t data)
 *   Write IDT EEPROM extended init block of DWORD data
 *
 *  @param csr IDT PCIe-swtich CSR address
 *  @param data DWORD output data
 *  @exception EEEXception
 */
void EEExtBlock::init(uint32_t csr, uint32_t data)
{
	/* Create the data structure to send */
	eeext_dw dw;

	/* Initialize fields */
	dw.type = EXT_DW_TYPE;
	dw.csr = EXT_CSR(csr);
	dw.data = (uint32_t)htole32(data);

	/* Write data to the file */
	EEBase::write((void *)&dw, sizeof(eeext_dw));
}

/*! @fn void EEExtBlock::init(uint32_t csr, uint16_t count, uint32_t *data)
 *   Write IDT EEPROM extended init block of sequential DWORD data
 *
 *  @param csr IDT PCIe-swtich CSR address
 *  @param count number of DWORD's to write
 *  @param data DWORD output data
 *  @exception EEEXception
 */
void EEExtBlock::init(uint32_t csr, uint16_t count, const uint32_t *data)
{
	/* Assert of count is zero */
	assert(count != 0);

	/* Calculate size of output structure */
	size_t size = sizeof(eeext_ndw) + (count - 1)*4;
	/* Allocate raw memory for NxDWORD block with data */
	EEAlloc buf(size);
	/* Cast pointer with data */
	eeext_ndw *ndw = (eeext_ndw *)buf.get_data();

	/* Initialize fields */
	ndw->type = EXT_NDW_TYPE;
	ndw->csr = EXT_CSR(csr);
	ndw->cnt = (uint16_t)htole16(count);
	/* Copy data to the structure converting it to little endian */
	for (uint16_t idx = 0; idx < count; idx++)
		ndw->data[idx] = (uint32_t)htole32(data[idx]);

	/* Write data to the file */
	EEBase::write((void *)ndw, size);
}

/*! @fn void EEExtBlock::chksum()
 *   Write IDT EEPROM extended control sum block
 *  @exception EEEXception
 */
void EEExtBlock::chksum()
{
	/* Create the data structure to send */
	eeext_chksum sum;

	/* Initialize fields */
	sum.type = EXT_CHKSUM_TYPE;
	sum.sum = ~(~EEBase::get_sum() + sum.type);

	/* Write data to the file */
	EEBase::write((void *)&sum, sizeof(eeext_chksum));
}

/*! @fn void EEExtBlock::wait(uint32_t csr, uint32_t data, uint32_t mask)
 *   Write IDT EEPROM wait block
 *
 *  @param csr IDT PCIe-swtich CSR address
 *  @param data CSR value to wait for
 *  @param mask 1's in this field mask CSR bits from comparison
 *  @exception EEEXception
 */
void EEExtBlock::wait(uint32_t csr, uint32_t data, uint32_t mask)
{
	/* Create the data structure to send */
	eeext_wait wait;

	/* Initialize fields */
	wait.type = EXT_WAIT_TYPE;
	wait.csr = EXT_CSR(csr);
	wait.data = (uint32_t)htole32(data);
	wait.mask = (uint32_t)htole32(mask);

	/* Write data to the file */
	EEBase::write((void *)&wait, sizeof(eeext_wait));
}

/*! @fn void EEExtBlock::jump(uint8_t code, uint32_t eeaddr)
 *   Write IDT EEPROM extended jump block
 *
 *  @param code Jump external image selector
 *  @param eeaddr EEPROM address to jump to
 *  @exception EEEXception
 */
void EEExtBlock::jump(uint8_t code, uint32_t eeaddr)
{
	throw EEException("jump block is unsupported");
}

