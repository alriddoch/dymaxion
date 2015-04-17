TESTS = mercatortest Terraintest Shadertest TerrainModtest Intersecttest \
        testPhys timeSeg Foresttest testQRNG Areatest \
        TileShadertest ShaderFactorytest testWFMath \
        AreaShadertest DepthShadertest \
        FillShadertest GrassShadertest ThresholdShadertest

AM_CPPFLAGS = -I$(top_srcdir)

LDADD = $(top_builddir)/dymaxion/libdymaxion-0.3.la

DISTCLEANFILES = test1.pgm test2.pgm

RECHECK_LOGS =

check_PROGRAMS = $(TESTS)

noinst_HEADERS = Test.h compose.hpp

mercatortest_SOURCES = main.cpp

Terraintest_SOURCES = Terraintest.cpp

Shadertest_SOURCES = Shadertest.cpp

TerrainModtest_SOURCES = TerrainModtest.cpp

Intersecttest_SOURCES = Intersecttest.cpp
Intersecttest_LDADD = \
    $(top_builddir)/dymaxion/Area.lo \
    $(top_builddir)/dymaxion/BasePoint.lo \
    $(top_builddir)/dymaxion/Buffer.lo \
    $(top_builddir)/dymaxion/Effector.lo \
    $(top_builddir)/dymaxion/Intersect.lo \
    $(top_builddir)/dymaxion/Segment.lo \
    $(top_builddir)/dymaxion/Shader.lo \
    $(top_builddir)/dymaxion/Surface.lo \
    $(top_builddir)/dymaxion/Terrain.lo

testPhys_SOURCES = testPhys.cpp

timeSeg_SOURCES = timeSeg.cpp util_timer.h util_timer.cpp

Foresttest_SOURCES = Foresttest.cpp

testQRNG_SOURCES = testQRNG.cpp

Areatest_SOURCES = Areatest.cpp

TileShadertest_SOURCES = TileShadertest.cpp

ShaderFactorytest_SOURCES = ShaderFactorytest.cpp

testWFMath_SOURCES = testWFMath.cpp

AreaShadertest_SOURCES = AreaShadertest.cpp

DepthShadertest_SOURCES = DepthShadertest.cpp

FillShadertest_SOURCES = FillShadertest.cpp

GrassShadertest_SOURCES = GrassShadertest.cpp

ThresholdShadertest_SOURCES = ThresholdShadertest.cpp
