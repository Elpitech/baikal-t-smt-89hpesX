/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file EEAlloc.h
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */
#ifndef EEALLOC_H
#define EEALLOC_H

/*! @class EEAlloc class
 *   Basic wrapper for blocks allocation
 *
 *  Wrapper allocate and automatically delete an array or data
 */
class EEAlloc {
	/* Private allocated data */
	char *m_data;
	/* Size of allocated data */
	size_t m_size;

public:
	/* Class constructors and destructor */
	EEAlloc(size_t size): m_size(size) {
		m_data = new char[m_size];
	}
	~EEAlloc() {
		delete[] m_data;
	}

	/* Get pointer to the allocated data */
	void *get_data() {
		return m_data;
	}

	/* Retrieve the size of allocated data */
	size_t get_size() {
		return m_size;
	}
};

#endif /* EEALLOC_H */

