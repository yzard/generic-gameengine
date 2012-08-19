bin_PROGRAMS =					\
bytestream_test					\
queue_test					\
threadpool_test					\
clock_test					\
state_test					\
state_udpreceiver_test

AM_CPPFLAGS =					\
-I$(top_srcdir)					\
-I$(top_srcdir)/libinfra			\
-I$(top_srcdir)/libstate

LDALL =						\
$(top_builddir)/libinfra/libinfra.la		\
$(top_builddir)/libstate/libstate.la		\
-lpthread

bytestream_test_SOURCES = 			\
bytestream_test.cpp

queue_test_SOURCES =				\
queue_test.cpp

threadpool_test_SOURCES =			\
threadpool_test.cpp

clock_test_SOURCES =				\
clock_test.cpp

state_test_SOURCES =				\
state_test.cpp

state_udpreceiver_test_SOURCES =		\
state_udpreceiver_test.cpp

bytestream_test_LDADD =				\
$(LDALL)

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

state_test_LDADD =				\
$(LDALL)

state_udpreceiver_test_LDADD =			\
$(LDALL)
