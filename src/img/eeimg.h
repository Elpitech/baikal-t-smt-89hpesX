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

/*! @fn void write_eeimg(const char *imgname, const char *fname)
 *   Write EEPROM image with name 'imgname' to file
 *
 *  @param imgname image name
 *  @param fname file name
 *  @exception EEException
 */
extern void write_eeimg(const char *imgname, const char *fname);

#endif /* EEIMG_H */

