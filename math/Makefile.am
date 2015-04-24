AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)

noinst_LIBRARIES = libgeomath.a

libgeomath_a_SOURCES = \
  matrix.cpp matrix.h \
  quaternion.cpp quaternion.h \
  vector.cpp vector.h

TESTS = vectortest

RECHECK_LOGS =

check_PROGRAMS = $(TESTS)

vectortest_SOURCES = vectortest.cpp
vectortest_LDADD = vector.o
