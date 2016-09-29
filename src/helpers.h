/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file helpers.h
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */
#ifndef HELPERS_H
#define HELPERS_H

/*! @def SUCCESS
 *   Success return status
 */
#define SUCCESS (0)

/*! @def FAIL
 *   Failed return status
 */
#define FAIL (-1)

/*! @def PACKED_STRUCT
 *   Define tightly packed structure
 */
#define PACKED_STRUCT(name) name __attribute__((packed))

#endif /* HELPERS_H */

