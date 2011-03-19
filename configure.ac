#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([Game Engine], [0.1], [zhuoyin@gmail.com])
AC_CONFIG_SRCDIR([libinfra/ThreadPool.cpp])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([-Wall])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT32_T


# Checks for library functions.

AC_CONFIG_FILES([
	Makefile
	test/function/Makefile
])
AC_OUTPUT
