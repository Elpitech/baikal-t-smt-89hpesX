/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file eeimg.h
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date Sempteber, 2016
 *   @brief
 *
 *   Details about the file
 */
#ifndef EEIMG_H
#define EEIMG_H

/*! @struct EE-image parameters
 *   Requested EE-image setting passed to ancestors class methods
 */
struct eeparams {
	const char *iname;
	const char *fname;
	const char *dstr;
	bool lse;
};

/*! @fn void write_eeimg(struct eeparams *params)
 *   Write EEPROM image with paramters from the structure 
 *
 *  @param params set of image paramters
 *  @exception EEException
 */
extern void write_eeimg(struct eeparams *params);

#endif /* EEIMG_H */

