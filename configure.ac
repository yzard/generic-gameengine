AC_PREREQ([2.65])

AC_INIT([Game Engine], [0.1], [zhuoyin@gmail.com])
AM_INIT_AUTOMAKE([-Wall])

AC_CONFIG_SRCDIR([libinfra/ThreadPool.cpp])
AC_CONFIG_HEADERS([config.h:config.h.in])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_LANG([C++])

AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_CC_C_O

# Checks for libraries.
AC_PROG_LIBTOOL
AC_CONFIG_MACRO_DIR([m4])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT32_T


# Checks for library functions.

AC_CONFIG_FILES([
	Makefile
	libinfra/Makefile
	test/Makefile
	test/function/Makefile
	test/unit/Makefile
])
AC_OUTPUT
