bin_PROGRAMS =					\
queue_test					\
threadpool_test					\
clock_test

AM_CPPFLAGS =					\
-I$(top_srcdir)					\
-I$(top_srcdir)/libinfra

LDALL =						\
$(top_builddir)/libinfra/libinfra.la		\
-lpthread					\
-lrt

queue_test_SOURCES =				\
queue_test.cpp

threadpool_test_SOURCES =			\
threadpool_test.cpp

clock_test_SOURCES =				\
clock_test.cpp

queue_test_LDADD =				\
$(LDALL)

threadpool_test_LDADD =				\
$(LDALL)

clock_test_LDADD =				\
$(LDALL)

