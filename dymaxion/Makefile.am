AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)

lib_LTLIBRARIES = libdymaxion-0.3.la

libdymaxion_0_3_la_LDFLAGS = -version-info @DYMAXION_VERSION_INFO@

libdymaxion_0_3_la_SOURCES = \
	Area.cpp \
	AreaShader.cpp \
	BasePoint.cpp \
	Buffer.cpp \
	Clip.h \
	DepthShader.cpp \
	dymaxion.cpp \
	Edge.h \
	Effector.cpp \
	FillShader.cpp \
	Forest.cpp \
	GrassShader.cpp \
	Interp.h \
	Intersect.cpp \
	Matrix.cpp \
	Plant.cpp \
	Segment.cpp \
	Shader.cpp \
	ShaderFactory.cpp \
	Surface.cpp \
	Terrain.cpp \
	TerrainMod.cpp \
	ThresholdShader.cpp \
	TileShader.cpp \
	tuple_vector.h

libdymaxiondir = $(includedir)/dymaxion-0.3/dymaxion

libdymaxion_HEADERS = \
	Area.h \
	AreaShader.h \
	BasePoint.h \
	Buffer_impl.h Buffer.h \
	DepthShader.h \
	dymaxion.h \
	Effector.h \
	FillShader.h \
	Forest.h \
	GrassShader.h \
	Intersect.h \
	Matrix.h \
	Plant.h \
	RandCache.h \
	Segment_impl.h Segment.h \
	Shader.h \
	ShaderFactory_impl.h ShaderFactory.h \
	Surface.h \
	Terrain_impl.h Terrain.h \
	TerrainMod.h \
	TerrainMod_impl.h \
	ThresholdShader.h \
	TileShader.h \
	traits.h \
	tuple_traits.h \
	wfmath_traits.h

TESTS = Areaintegration AreaShadertest Areatest BasePointtest Buffertest \
        Cliptest DepthShadertest Edgetest Effectortest FillShadertest \
        Foresttest GrassShadertest Interptest Intersecttest Matrixtest \
        mercatortest Planttest Segmentperf Segmenttest ShaderFactorytest \
        Shadertest Terraintest TerrainaddAreatest TerrainModtest testPhys \
        testQRNG testWFMath ThresholdShadertest TileShadertest timeSeg \
        traitstest

RECHECK_LOGS =

check_PROGRAMS = $(TESTS)

DISTCLEANFILES = test1.pgm test2.pgm

Areaintegration_SOURCES = Areaintegration.cpp
Areaintegration_LDADD = libdymaxion-0.3.la

AreaShadertest_SOURCES = AreaShadertest.cpp
AreaShadertest_LDADD = libdymaxion-0.3.la

Areatest_SOURCES = Areatest.cpp
Areatest_LDADD = Area.lo

BasePointtest_SOURCES = BasePointtest.cpp
BasePointtest_LDADD = BasePoint.lo

Buffertest_SOURCES = Buffertest.cpp
Buffertest_LDADD = Buffer.lo

Cliptest_SOURCES = Cliptest.cpp

DepthShadertest_SOURCES = DepthShadertest.cpp
DepthShadertest_LDADD = libdymaxion-0.3.la

Edgetest_SOURCES = Edgetest.cpp

Effectortest_SOURCES = Effectortest.cpp
Effectortest_LDADD = Effector.lo

FillShadertest_SOURCES = FillShadertest.cpp
FillShadertest_LDADD = libdymaxion-0.3.la

Foresttest_SOURCES = Foresttest.cpp
Foresttest_LDADD = libdymaxion-0.3.la

GrassShadertest_SOURCES = GrassShadertest.cpp
GrassShadertest_LDADD = libdymaxion-0.3.la

Interptest_SOURCES = Interptest.cpp

Intersecttest_SOURCES = Intersecttest.cpp
Intersecttest_LDADD = \
    Area.lo \
    BasePoint.lo \
    Buffer.lo \
    Effector.lo \
    Intersect.lo \
    Segment.lo \
    Shader.lo \
    Surface.lo \
    Terrain.lo

Matrixtest_SOURCES = Matrixtest.cpp
Matrixtest_LDADD = Matrix.lo

mercatortest_SOURCES = main.cpp
mercatortest_LDADD = libdymaxion-0.3.la

Planttest_SOURCES = Planttest.cpp
Planttest_LDADD = Plant.lo

Segmentperf_SOURCES = Segmentperf.cpp
Segmentperf_LDADD = Segment.lo

Segmenttest_SOURCES = Segmenttest.cpp
Segmenttest_LDADD = Segment.lo

ShaderFactorytest_SOURCES = ShaderFactorytest.cpp
ShaderFactorytest_LDADD = libdymaxion-0.3.la

Shadertest_SOURCES = Shadertest.cpp
Shadertest_LDADD = libdymaxion-0.3.la

TerrainaddAreatest_SOURCES = TerrainaddAreatest.cpp
TerrainaddAreatest_LDADD = Terrain.lo \
                           Segment.lo \
                           Area.lo

TerrainModtest_SOURCES = TerrainModtest.cpp
TerrainModtest_LDADD = libdymaxion-0.3.la

Terraintest_SOURCES = Terraintest.cpp
Terraintest_LDADD = libdymaxion-0.3.la

testPhys_SOURCES = testPhys.cpp
testPhys_LDADD = libdymaxion-0.3.la

testQRNG_SOURCES = testQRNG.cpp

testWFMath_SOURCES = testWFMath.cpp

ThresholdShadertest_SOURCES = ThresholdShadertest.cpp
ThresholdShadertest_LDADD = libdymaxion-0.3.la

TileShadertest_SOURCES = TileShadertest.cpp
TileShadertest_LDADD = libdymaxion-0.3.la

timeSeg_SOURCES = timeSeg.cpp util_timer.h util_timer.cpp
timeSeg_LDADD = libdymaxion-0.3.la

traitstest_SOURCES = traitstest.cpp
