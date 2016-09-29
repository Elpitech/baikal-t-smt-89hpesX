/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file EEExtBlock.h
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */
#ifndef EEEXTBLOCK_H
#define EEEXTBLOCK_H

#include <endian.h>
#include <stdint.h>

#include "EEBase.h"
#include "helpers.h"

/*! @def EXT_DW_TYPE
 *   One DWORD init block type
 */
#define EXT_DW_TYPE		((uint8_t)0x0)

/*! @def EXT_NDW_TYPE
 *   NxDWORD init block type
 */
#define EXT_NDW_TYPE	((uint8_t)0x20)

/*! @def EXT_JMP_TYPE
 *   Jump block type
 */
#define EXT_JMP_TYPE	((uint8_t)0x40)

/*! @def EXT_WAIT_TYPE
 *   Wait block type
 */
#define EXT_WAIT_TYPE	((uint8_t)0x60)

/*! @def EXT_CHKSUM_TYPE
 *   Control sum init block type
 */
#define EXT_CHKSUM_TYPE	((uint8_t)0xE0)

/*! @def EXT_CSR(csr)
 *   Retrieve CSR address
 */
#define EXT_CSR(csr) \
	(htole16(uint16_t(((csr) >> 2) & 0xFFFF)))

/*! @struct eeext_dw
 *   Extended init DWORD block
 */
PACKED_STRUCT(
	struct eeext_dw {
		uint8_t type;
		uint16_t csr;
		uint32_t data;
	}
);

/*! @struct eeext_ndw
 *   Extended init NxDWORD block
 */
PACKED_STRUCT(
	struct eeext_ndw {
		uint8_t type;
		uint16_t csr;
		uint16_t cnt;
		uint32_t data[1];
	}
);

/*! @struct eeext_jump
 *   Extended jump block
 */
PACKED_STRUCT(
	struct eeext_jump {
		uint8_t type;
		uint16_t eeaddr;
	}
);

/*! @struct eeext_wait
 *   Extended wait block
 */
PACKED_STRUCT(
	struct eeext_wait {
		uint8_t type;
		uint16_t csr;
		uint32_t data;
		uint32_t mask;
	}
);

/*! @struct eeext_chksum
 *   Extended control sum block
 */
PACKED_STRUCT(
	struct eeext_chksum {
		uint8_t type;
		uint8_t sum;
	}
);

/*! @class EEExtBlock class
 *   IDT EEPROM extended blocks
 *
 *  Class of IDT EEPROM blocks write-methods for extended interface
 */
class EEExtBlock: public EEBase {
public:
	/* Class constructor */
	EEExtBlock(const char *fname): EEBase(fname) {}

	/* Initialization DWORD data write-method */
	virtual void init(uint32_t csr, uint32_t data);

	/* Initialization sequential DWORD data write-method */
	virtual void init(uint32_t csr, uint16_t count, const uint32_t *data);

	/* Control sum write-method (necessary to implement) */
	virtual void chksum();

	/* Wait block wite-method */
	virtual void wait(uint32_t csr, uint32_t data, uint32_t mask);

	/* Jump block write-method (Unsupported at this logic) */
	virtual void jump(uint8_t code, uint32_t eeaddr);
};

#endif /* EEEXTBLOCK_H */

