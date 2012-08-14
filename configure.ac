AC_PREREQ([2.65])

AC_INIT([Game Engine], [0.1], [zhuoyin@gmail.com])
AM_INIT_AUTOMAKE([-Wall])

AC_CONFIG_SRCDIR([libinfra/ThreadPool.cpp])
AC_CONFIG_HEADERS([config.h:config.h.in])
AC_CONFIG_MACRO_DIR([m4])

# made compile process more clean
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

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
AC_TYPE_UINT64_T

# check if the system has clock_gettime
AC_MSG_CHECKING([if system has clock_gettime])
AC_TRY_COMPILE(
	[#include <time.h>],
	[
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
	],
	[has_clock_gettime=true],
	[has_clock_gettime=false]
)

if test x$has_clock_gettime = xtrue; then
	AC_MSG_RESULT([yes])
	AC_DEFINE(
		[HAVE_CLOCK_GETTIME],
		[1],
	    	[Define to 1 if system has clock_gettime]
	)
else
	AC_MSG_RESULT([no])
fi

AM_CONDITIONAL([ENABLE_CLOCK_GETTIME], [test x$has_clock_gettime = xtrue])

# Checks for library functions.
AC_CONFIG_FILES([
	Makefile
	libinfra/Makefile
	libstate/Makefile
	test/Makefile
	test/function/Makefile
	test/performance/Makefile
	test/unit/Makefile
])
AC_OUTPUT


