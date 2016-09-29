/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file EEBasicBlock.cpp
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */

#include <cassert>
#include <endian.h>
#include "EEBasicBlock.h"
#include "EEAlloc.h"

/*! @fn void EEBasicBlock::init(uint32_t csr, uint32_t data)
 *   Write IDT EEPROM basic init block of DWORD data
 *
 *  @param csr IDT PCIe-swtich CSR address
 *  @param data DWORD output data
 *  @exception EEEXception
 */
void EEBasicBlock::init(uint32_t csr, uint32_t data)
{
	/* Create the data structure to send */
	eebasic_dw dw;

	/* Initialize fields */
	dw.csrl = BASIC_CSRL(csr);
	dw.csru_type = BASIC_DW_TYPE | BASIC_CSRU(csr);
	dw.data = (uint32_t)htole32(data);

	/* Write data to the file */
	EEBase::write((void *)&dw, sizeof(eebasic_dw));
}

/*! @fn void EEBasicBlock::init(uint32_t csr, uint16_t count, uint32_t *data)
 *   Write IDT EEPROM basic init block of sequential DWORD data
 *
 *  @param csr IDT PCIe-swtich CSR address
 *  @param count number of DWORD's to write
 *  @param data DWORD output data
 *  @exception EEEXception
 */
void EEBasicBlock::init(uint32_t csr, uint16_t count, const uint32_t *data)
{
	/* Assert of count is zero */
	assert(count != 0);

	/* Calculate size of output structure */
	size_t size = sizeof(eebasic_ndw) + (count - 1)*4;
	/* Allocate raw memory for NxDWORD block with data */
	EEAlloc buf(size);
	/* Cast pointer with data */
	eebasic_ndw *ndw = (eebasic_ndw *)buf.get_data();

	/* Initialize fields */
	ndw->csrl = BASIC_CSRL(csr);
	ndw->csru_type = BASIC_NDW_TYPE | BASIC_CSRU(csr);
	ndw->cnt = (uint16_t)htole16(count);
	/* Copy data to the structure converting it to little endian */
	for (uint16_t idx = 0; idx < count; idx++)
		ndw->data[idx] = (uint32_t)htole32(data[idx]);

	/* Write data to the file */
	EEBase::write((void *)ndw, size);
}

/*! @fn void EEBasicBlock::chksum()
 *   Write IDT EEPROM basic control sum block
 *  @exception EEEXception
 */
void EEBasicBlock::chksum()
{
	/* Create the data structure to send */
	eebasic_chksum sum;

	/* Initialize fields */
	sum.type = BASIC_CHKSUM_TYPE;
	sum.sum = ~(~EEBase::get_sum() + sum.type);

	/* Write data to the file */
	EEBase::write((void *)&sum, sizeof(eebasic_chksum));
}

