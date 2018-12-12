# vi: set ts=4 sw=4 ai :
#
# $Id$
#
# Copyright (C) 2016, T-Platforms
# All rights reserved
#

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#                                Boilerplate
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
AC_PREREQ([2.69])
AC_INIT([IDT EEPROM firmware], [1.0], [Sergey.Semin@t-platforms.ru])
: ${CXXFLAGS="-O3 -std=c++11"}
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/])

AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_LANG(C++)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#                                  Programs
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
AC_PROG_MAKE_SET
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#                                  Libraries
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
AC_CHECK_LIB([stdc++], [main], [], [AC_MSG_ERROR(Cannot find lib stdc++)])

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#                                  Headers
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
AC_CHECK_HEADERS([iostream fstream exception string cassert \
				  stdint.h endian.h unistd.h string.h])

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#                           Typedefs and structures
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#                                 Functions
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
AC_CHECK_FUNCS([getopt])

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#                                 Output
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT

echo \
"----------------------------------------------------------
Configuration:

        Source location:        ${srcdir}
        Compile:                ${CXX}
        Compiler flags:         ${CXXFLAGS}
        Linker flags:           ${LIBS} ${LDFLAGS}
        Host system type:       ${host}
        Install path:           ${prefix}

        This project is for T-platforms internal usage only.
        See src/config.h for further configuration.
----------------------------------------------------------"

