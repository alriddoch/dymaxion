AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)

noinst_LIBRARIES = libgeomath.a

libgeomath_a_SOURCES = \
  matrix.cpp matrix.h \
  quaternion.cpp quaternion.h \
  vector.cpp vector.h

TESTS = matrixtest quaterniontest vectortest

RECHECK_LOGS =

check_PROGRAMS = $(TESTS)

matrixtest_SOURCES = matrixtest.cpp
matrixtest_LDADD = matrix.o

quaterniontest_SOURCES = quaterniontest.cpp
quaterniontest_LDADD = quaternion.cpp

vectortest_SOURCES = vectortest.cpp
vectortest_LDADD = vector.o
