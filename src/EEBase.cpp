/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file EEBase.cpp
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */

#include "EEBase.h"
#include "EEException.h"

/*! @fn EEBase::EEBase(const char *fname) 
 *   EEBase constructor
 *
 *  @param fname name of output file
 *  @exception std::fstream::failure
 */
EEBase::EEBase(const char *fname): m_fname(fname), m_sum(0)
{
	/* Enable file stream exceptions */
	m_fs.exceptions(std::ios::failbit | std::ios::badbit);

	/* Open the file if filename is passed */
	if (m_fname != NULL)
		m_fs.open(m_fname, std::ios::out | std::ios::binary);
}

/*! @fn EEBase::~EEBase() 
 *   EEBase destructor
 */
EEBase::~EEBase()
{
	/* Just close the opened file */
	if (m_fname != NULL)
		m_fs.close();
}

/*! @fn void EEBase::write(void *data, size_t count) 
 *   Write data to output file
 *
 *  @param data pointer to data to be written
 *  @param count size of data
 *  @exception std::fstream::failure
 */
void EEBase::write(const void *data, size_t count)
{
	const uint8_t *buf = (uint8_t *)data;
	/* Don't have time to find a better solution */
	std::ostream &ofs = (m_fname != NULL ? m_fs : std::cout);

	/* Write the data to the file - can through an exception */
	ofs.write((const char *)data, count);

	/* Calculate the written data control sum */
	for (size_t idx = 0; idx < count; idx++)
		m_sum += buf[idx];
}

/*! @fn uint8_t EEBase::get_sum() 
 *   Control sum of written data
 */
uint8_t EEBase::get_sum()
{
	return ~m_sum;
}

/*! @fn void EEBase::empty(uint16_t count)
 *   Write empty blocks
 *
 *  @exception std::fstream::failure
 */
void EEBase::empty(uint16_t count)
{
	char data = 0xFF;

	/* Just write 0xFF blocks byte-by-byte */
	while (count != 0) {
		EEBase::write(&data, 1);
		count--;
	}
}

/*! @fn void EEBase::wait(uint32_t csr, uint32_t data, uint32_t mask)
 *   Write wait block to EEPROM
 *
 *  @param csr IDT PCIe-swtich CSR address
 *  @param data value of masked register value to wait for
 *  @param mask allied mask to csr real value
 *  @exception EEEXception
 */
void EEBase::wait(uint32_t csr, uint32_t data, uint32_t mask)
{
	/* It's not supported by the base class */
	throw EEException("wait block is unsupported", false);
}

/*! @fn void EEBase::jump(uint8_t code, uint32_t eeaddr)
 *   Write jump block to EEPROM
 *
 *  @param code jump image selector
 *  @param eeaddr EEPROM address to jump to
 *  @exception EEEXception
 */
void EEBase::jump(uint8_t code, uint32_t eeaddr)
{
	throw EEException("jump block is unsupported", false);
}

