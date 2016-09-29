/* vi: set ts=4 sw=4 cindent :
 *
 * $Id$
 *
 * Copyright (C) 2016, T-Platforms
 * All rights reserved
 */
/*! @file main.cpp
 *  @author Sergey Semin <Sergey.Semin (at) t-platforms.ru>
 *  @date September, 2016
 *   @brief
 *
 *   Details about the file
 */

#include <iostream>
#include <unistd.h>
#include "EEException.h"
#include "img/eeimg.h"
#include "helpers.h"

/*! @fn void eefw_usage(const char *progname)
 *   Print help message to stdout
 *
 *  @param progname current program name
 */
static void eefw_usage(const char *progname) {
	std::cout << "Usage:" << std::endl <<
		"  " << progname << " -i <image> [-o <file>]" << std::endl <<
		"Print EEPROM <image> either to a <file> or to stdout" << std::endl <<
		std::endl <<
		"Options:" << std::endl <<
		"  -i  name of image to print: cnccu, cncbp, empty" << std::endl <<
		"  -o  optional file name to print image to (stdout used by default)" <<
		std::endl << std::endl;
}

int main(int argc, char *argv[]) {
	bool usage_flag = false;

	try {
		const char *image = NULL, *fname = NULL;
		int opt;

		/* Parse the arguments passed to the program */
		opterr = 0; /* No need to print an error */
		while ((opt = getopt(argc,argv,"i:o:h")) != -1) {
			switch (opt) {
			case 'h':
				eefw_usage(argv[0]);
				return SUCCESS;
			case 'i':
				image = optarg;
				break;
			case 'o':
				fname = optarg;
				break;
			case ':':
				usage_flag = true;
				throw EEException(std::string("option -") + (char)optopt + " requires an operand");
				break;
			case '?':
				usage_flag = true;
				throw EEException(std::string("invalid argument -") + (char)optopt);
				break;
			default:
				break;
			}
		}

		/* If image isn't specified then throw an exception */
		if (image == NULL) {
			usage_flag = true;
			throw EEException("image name isn't specified");
		}

		/* Perform image write operation in complience with arguments */
		write_eeimg(image, fname);

		return SUCCESS;
	} catch (std::exception &e) {
		std::cerr << "Got an exception: " << e.what() << std::endl << std::endl;
		if (usage_flag)
			eefw_usage(argv[0]);
	}

	return FAIL;
}

