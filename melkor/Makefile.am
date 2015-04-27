AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)

bin_PROGRAMS = melkor

melkor_CPPFLAGS = $(AM_CPPFLAGS) @SDL_CFLAGS@
melkor_SOURCES = melkor.cpp
melkor_LDADD = $(top_builddir)/math/libgeomath.a \
               @SDL_LIBS@ \
               -lGL -lGLEW
