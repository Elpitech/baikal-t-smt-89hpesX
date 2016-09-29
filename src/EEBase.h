/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file EEBase.h
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */
#ifndef EEBASE_H
#define EEBASE_H

#include <iostream>
#include <fstream>
#include <stdint.h>

/*! @class EEBase class
 *   EEPROM basic IO methods
 *
 *  Basic class to write data to IDT EEPROM firmware
 */
class EEBase {
	/* Filename of output file */
	const char *m_fname;
	/* File stream of output data */
	std::fstream m_fs;
	/* Control sum of transfered data */
	uint8_t m_sum;

protected:
	/* Class constructors and destructor */
	EEBase(const char *fname);
	~EEBase();

	/* Write data to the file */
	void write(const void *data, size_t count);

	/* Retrieve the current check sum of written values */
	uint8_t get_sum();

public:
	/* Initialization DWORD data write-method (necessary to implement) */
	virtual void init(uint32_t csr, uint32_t data) = 0;

	/* Initialization DWORD sequential data write-method (necessary to implement) */
	virtual void init(uint32_t csr, uint16_t count, const uint32_t *data) = 0;
	
	/* Control sum write-method (necessary to implement) */
	virtual void chksum() = 0;

	/* Empty block write-method */
	virtual void empty(uint16_t count);

	/* Wait block wite-method */
	virtual void wait(uint32_t csr, uint32_t data, uint32_t mask);

	/* Jump block write-method (Unsupported at this logic) */
	virtual void jump(uint8_t code, uint32_t eeaddr);
};

#endif /* EEBASE_H */

