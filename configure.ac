dnl Initialise autoconf

AC_INIT([dymaxion], [0.3.2], [alriddoch@googlemail.com])
AC_CONFIG_SRCDIR([dymaxion/dymaxion.cpp])
AC_CONFIG_HEADERS([config.h])

dnl Detect the canonical host and target environment

AC_CANONICAL_HOST

dnl Initialise automake

AM_INIT_AUTOMAKE([nostdinc dist-bzip2 check-news color-tests parallel-tests no-define silent-rules])
AM_SILENT_RULES([yes])

dnl versioning info for libtool
DYMAXION_CURRENT=3
DYMAXION_REVISION=0
DYMAXION_AGE=0
DYMAXION_VERSION_INFO=$DYMAXION_CURRENT:$DYMAXION_REVISION:$DYMAXION_AGE

DYMAXION_LIB_SUFFIX="-0.3"
DYMAXION_LIBS="-ldymaxion$DYMAXION_LIB_SUFFIX"
DYMAXION_REQUIRES=""

AC_SUBST(DYMAXION_VERSION_INFO)

dnl Test for GNU libtool

LT_INIT([disable-static])

AC_PROG_CXX

AC_ARG_ENABLE(debug,
    [  --enable-debug          enable debug information [default=no]],
    [
        if test "$enableval" = "yes"; then
            CXXFLAGS="$CXXFLAGS -Wall -DDEBUG"
        else
            CXXFLAGS="$CXXFLAGS -Wall -DNDEBUG"
        fi
    ],[
        CXXFLAGS="$CXXFLAGS -Wall -DNDEBUG"
    ]
)

dnl Make sure we've got sensible versions of the sources (eg to get lrintf)

AC_DEFINE(_XOPEN_SOURCE, 500, [This is XOpen source])
AC_DEFINE(_ISOC99_SOURCE,1, [This is C99 source])

AC_LANG(C++)

AX_CXX_COMPILE_STDCXX_11

dnl Check for float to int converters

AC_CHECK_FUNCS([lrintf rintf rint])
AC_CHECK_FUNCS([fabsf powf floorf ceilf])

PKG_PROG_PKG_CONFIG

dnl Check for wfmath library
PKG_CHECK_MODULES(WF, wfmath-1.0 >= 1.0.0,
    [
        CPPFLAGS="$CPPFLAGS $WF_CFLAGS"
        LIBS="$LIBS $WF_LIBS"
        DYMAXION_REQUIRES="$DYMAXION_REQUIRES wfmath-1.0"
    ],
    [
        AC_MSG_ERROR([
Cannot find valid versions of required WorldForge maths library, wfmath:
$WF_PKG_ERRORS
Perhaps you should add the directory containing the missing libraries to the
PKG_CONFIG_PATH environment variable.
Please see dymaxion for details of
the libraries required and where to obtain them.])
    ])

AX_BOOST_BASE(
    [1.54],
    [],
    [
        AC_MSG_ERROR([
Cannot find Boost library 1.54 or later.
Please see http://www.boost.org/ for details of how to download and install
Boost.])
    ]
)

SYSTEM_LIBS=""
DYMAXION_CFLAGS=""
AC_SUBST(SYSTEM_LIBS)
AC_SUBST(DYMAXION_LIB_SUFFIX)
AC_SUBST(DYMAXION_LIBS)
AC_SUBST(DYMAXION_CFLAGS)
AC_SUBST(DYMAXION_REQUIRES)

AC_CONFIG_FILES([
	Makefile
	dymaxion/Makefile
	math/Makefile
	dymaxion.spec
	mingw32-dymaxion.spec
	dymaxion-0.3.pc
])
AC_OUTPUT
