SUBDIRS = dymaxion math melkor

ACLOCAL_AMFLAGS = -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = dymaxion-0.3.pc

EXTRA_DIST = dymaxion.spec Doxyfile autogen.sh

docs:
	@echo "running doxygen..."
	@doxygen Doxyfile
	@echo "documentation is in doc/."
