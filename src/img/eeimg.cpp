/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file eeimg.cpp
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */

#include <string.h>
#include "EEException.h"

/*! @fn void eeimg_cnccu(const char *fname)
 *   Wrapper method creating CNC CU IDT EEPROM firmware
 */
extern void eeimg_cnccu(const char *fname);

/*! @fn void eeimg_cnccu(const char *fname)
 *   Wrapper method creating CNC BP IDT EEPROM firmware
 */
extern void eeimg_cncbp(const char *fname);

/*! @fn void eeimg_empty(const char *fname)
 *   Wrapper method creating empty EEPROM firmware
 */
extern void eeimg_empty(const char *fname);

/*! @struct eeimg_desc
 *   EEPROM image descriptor structure
 */
struct eeimg_desc {
	const char *name;
	void (*write)(const char *fname);
};

/*! @var eeimg_sd
 *   EEPROM images descriptor structure
 */
static struct eeimg_desc eeimgs[] = {
	{"cnccu", eeimg_cnccu},
	{"cncbp", eeimg_cncbp},
	{"empty", eeimg_empty}
};

/*! @def EEIMGS_CNT
 *   Number of available EEPROM images
 */
#define EEIMGS_CNT \
	(sizeof(eeimgs)/sizeof(struct eeimg_desc))

/*! @fn void write_eeimg(const char *imgname, const char *fname)
 *   Write EEPROM image with name 'imgname' to file
 *
 *  @param imgname image name
 *  @param fname file name
 *  @exception EEException
 */
void write_eeimg(const char *imgname, const char *fname)
{
	/* Find an image with passed name and call it callback method */
	for (unsigned int idx = 0; idx < EEIMGS_CNT; idx++) {
		if (!strcmp(imgname, eeimgs[idx].name)) {
			eeimgs[idx].write(fname);
			return;
		}
	}

	/* If failed to find an image then throw an exception */
	throw EEException("couldn't find image with passed name");
}

