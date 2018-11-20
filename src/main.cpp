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
		"  " << progname << " -i <image> [-d <ports> -l -o <file>]" << std::endl <<
		"Print EEPROM <image> either to a <file> or to stdout" << std::endl <<
		std::endl <<
		"Options:" << std::endl <<
		"  -i <image> - image being generated: cnccu, cncbp, empty" << std::endl <<
		"  -l         - low-swing SerDes mode (makes sense for cncbp image only)" << std::endl <<
		"  -d <ports> - comma-separated dowstream ports (cncbp specific subset of 4,6,8,12,16,20)" << std::endl <<
		"  -o <file>  - file name to print image to (stdout used by default)" <<
		std::endl << std::endl;
}

int main(int argc, char *argv[]) {
	try {
		struct eeparams params = {0};
		bool lse = false;
		int opt;

		/* Parse the arguments passed to the program */
		opterr = 0; /* No need to print an error */
		while ((opt = getopt(argc,argv,"i:ld:o:h")) != -1) {
			switch (opt) {
			case 'h':
				eefw_usage(argv[0]);
				return SUCCESS;
			case 'i':
				params.iname = optarg;
				break;
			case 'l':
				params.lse = true;
				break;
			case 'd':
				params.dstr = optarg;
				break;
			case 'o':
				params.fname = optarg;
				break;
			case ':':
				throw EEException(std::string("option -") + (char)optopt + " requires an operand", true);
				break;
			case '?':
				throw EEException(std::string("invalid argument -") + (char)optopt, true);
				break;
			default:
				break;
			}
		}

		/* If image isn't specified then throw an exception */
		if (params.iname == NULL) {
			throw EEException("image name isn't specified", true);
		}

		/* Perform image write operation in complience with arguments */
		write_eeimg(&params);

		return SUCCESS;
	} catch (EEException &e) {
		std::cerr << "Error: " << e.what() << std::endl << std::endl;
		if (e.usage())
			eefw_usage(argv[0]);
	} catch (std::exception &e) {
		std::cerr << "Unkown exception: " << e.what() << std::endl << std::endl;
	}

	return FAIL;
}

