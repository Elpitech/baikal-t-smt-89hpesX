/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file eeimg_empty.cpp
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */

#include <stdint.h>
#include "EEBasicBlock.h"

/*! @def EMPTY_CNT
 *   Number of empty blocks
 */
#define EMPTY_CNT ((uint16_t)1024)

/*! @fn void eeimg_empty(const char *fname)
 *   Write empty EEPROM image
 *
 *  @param fname file name to write firmware to
 *  @exception EEEXception
 */
void eeimg_empty(const char *fname)
{
	EEBasicBlock iface(fname);

	/* Just output EMPTY_CNT empty blocks */
	iface.empty(EMPTY_CNT);
}
