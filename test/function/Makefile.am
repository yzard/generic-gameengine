bin_PROGRAMS =			\
queue_test			\
threadpool_test

LDALL =				\
-lpthread

AM_CPPFLAGS =			\
-I$(top_srcdir)			\
-I$(top_srcdir)/libinfra

queue_test_SOURCES =		\
queue_test.cpp

threadpool_test_SOURCES =	\
threadpool_test.cpp

queue_test_LDADD =		\
$(LDALL)

threadpool_test_LDADD =		\
$(LDALL)
