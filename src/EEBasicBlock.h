/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file EEBasicBlock.h
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */
#ifndef EEBASIC_BLOCK_H
#define EEBASIC_BLOCK_H

#include <stdint.h>

#include "EEBase.h"
#include "helpers.h"

/*! @def BASIC_DW_TYPE
 *   One DWORD init block type
 */
#define BASIC_DW_TYPE		((uint8_t)0x0)

/*! @def BASIC_NDW_TYPE
 *   NxDWORD init block type
 */
#define BASIC_NDW_TYPE		((uint8_t)0x40)

/*! @def BASIC_CHKSUM_TYPE
 *   Control sum init block type
 */
#define BASIC_CHKSUM_TYPE	((uint8_t)0xC0)

/*! @def BASIC_CSRL(csr)
 *   Retrieve lower part of CSR address
 */
#define BASIC_CSRL(csr) \
	(uint8_t(((csr) >> 2) & 0xFF))

/*! @def BASIC_CSRU(csr)
 *   Retrieve upper part of CSR address
 */
#define BASIC_CSRU(csr) \
	(uint8_t(((csr) >> 10) & 0x3F))

/*! @struct eebasic_dw
 *   Basic init DWORD block
 */
PACKED_STRUCT(
	struct eebasic_dw {
		uint8_t csrl;
		uint8_t csru_type;
		uint32_t data;
	}
);

/*! @struct eebasic_ndw
 *   Basic init NxDWORD block
 */
PACKED_STRUCT(
	struct eebasic_ndw {
		uint8_t csrl;
		uint8_t csru_type;
		uint16_t cnt;
		uint32_t data[1];
	}
);

/*! @struct eebasic_chksum
 *   Basic control sum block
 */
PACKED_STRUCT(
	struct eebasic_chksum {
		uint8_t sum;
		uint8_t type;
	}
);

/*! @class EEBasicBlock class
 *   IDT EEPROM basic blocks
 *
 *  Class of IDT EEPROM blocks write-methods for basic interface
 */
class EEBasicBlock: public EEBase {
public:
	/* Class constructor */
	EEBasicBlock(const char *fname): EEBase(fname) {}

	/* Initialization DWORD data write-method */
	virtual void init(uint32_t csr, uint32_t data);

	/* Initialization sequential DWORD data write-method */
	virtual void init(uint32_t csr, uint16_t count, const uint32_t *data);

	/* Control sum write-method */
	virtual void chksum();
};

#endif /* EEBASIC_BLOCK_H */

