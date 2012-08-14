bin_PROGRAMS =					\
queue_test					\
threadpool_test					\
clock_test					\
state_test

AM_CPPFLAGS =					\
-I$(top_srcdir)					\
-I$(top_srcdir)/libinfra			\
-I$(top_srcdir)/libstate

LDALL =						\
$(top_builddir)/libinfra/libinfra.la		\
$(top_builddir)/libstate/libstate.la		\
-lpthread

queue_test_SOURCES =				\
queue_test.cpp

threadpool_test_SOURCES =			\
threadpool_test.cpp

clock_test_SOURCES =				\
clock_test.cpp

state_test_SOURCES =				\
state_test.cpp

if ENABLE_CLOCK_GETTIME
queue_test_LDADD =				\
$(LDALL)					\
-lrt
else !ENABLE_CLOCK_GETTIME
queue_test_LDADD =				\
$(LDALL)
endif !ENABLE_CLOCK_GETTIME

threadpool_test_LDADD =				\
$(LDALL)

if ENABLE_CLOCK_GETTIME
clock_test_LDADD =				\
$(LDALL)					\
-lrt
else !ENABLE_CLOCK_GETTIME
clock_test_LDADD =				\
$(LDALL)
endif !ENABLE_CLOCK_GETTIME
