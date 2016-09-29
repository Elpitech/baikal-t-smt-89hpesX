/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file EEException.h
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */
#ifndef EEEXCEPTION_H
#define EEEXCEPTION_H

#include <exception>
#include <string>

/*! @class EEException class
 *   Custom exception class
 */
class EEException: public std::exception {
	/* String to hold the exception description */
	std::string m_msg;

public:
	/* Class constructor */
	EEException(const std::string &msg) throw(): m_msg(msg) {}
	~EEException() throw() {}

	/* String description of the exception */
	virtual const char *what() const throw() {
		return m_msg.c_str();
	}
};

#endif /* EEEXCEPTION_H */

