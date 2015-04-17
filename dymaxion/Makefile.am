AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)

lib_LTLIBRARIES = libdymaxion-0.3.la

libdymaxion_0_3_la_LDFLAGS = -version-info @DYMAXION_VERSION_INFO@

libdymaxion_0_3_la_SOURCES = \
	dymaxion.cpp \
	Matrix.cpp \
	Terrain.cpp \
	Effector.cpp \
	TerrainMod.cpp \
	BasePoint.cpp \
	Buffer.cpp \
	Segment.cpp \
	Shader.cpp \
	FillShader.cpp \
	ThresholdShader.cpp \
	DepthShader.cpp \
	GrassShader.cpp \
	TileShader.cpp \
	ShaderFactory.cpp \
	Intersect.cpp \
	Surface.cpp \
	Plant.cpp \
	Forest.cpp \
	Area.cpp \
	AreaShader.cpp \
	tuple_vector.h

libdymaxiondir = $(includedir)/dymaxion-0.3/dymaxion

libdymaxion_HEADERS = \
	dymaxion.h \
	Matrix.h \
	Terrain_impl.h Terrain.h \
	Effector.h \
	TerrainMod.h \
	TerrainMod_impl.h \
	BasePoint.h \
	Segment_impl.h Segment.h \
	Buffer_impl.h Buffer.h \
	Shader.h \
	FillShader.h \
	ThresholdShader.h \
	DepthShader.h \
	GrassShader.h \
	TileShader.h \
	ShaderFactory.h \
	ShaderFactory_impl.h \
	Intersect.h \
	Surface.h \
	Plant.h \
	Forest.h \
	RandCache.h \
	Area.h \
	AreaShader.h \
	traits.h \
	tuple_traits.h \
	wfmath_traits.h

noinst_HEADERS = Clip.h Edge.h Interp.h

TESTS = Areatest BasePointtest Buffertest Cliptest Edgetest Effectortest \
        Interptest Matrixtest Planttest Segmentperf Segmenttest \
        TerrainaddAreatest traitstest

check_PROGRAMS = $(TESTS)

Areatest_SOURCES = Areatest.cpp
Areatest_LDADD = Area.lo

BasePointtest_SOURCES = BasePointtest.cpp
BasePointtest_LDADD = BasePoint.lo

Buffertest_SOURCES = Buffertest.cpp
Buffertest_LDADD = Buffer.lo

Cliptest_SOURCES = Cliptest.cpp

Edgetest_SOURCES = Edgetest.cpp

Effectortest_SOURCES = Effectortest.cpp
Effectortest_LDADD = Effector.lo

Interptest_SOURCES = Interptest.cpp

Matrixtest_SOURCES = Matrixtest.cpp
Matrixtest_LDADD = Matrix.lo

Planttest_SOURCES = Planttest.cpp
Planttest_LDADD = Plant.lo

Segmentperf_SOURCES = Segmentperf.cpp
Segmentperf_LDADD = Segment.lo

Segmenttest_SOURCES = Segmenttest.cpp
Segmenttest_LDADD = Segment.lo

TerrainaddAreatest_SOURCES = TerrainaddAreatest.cpp
TerrainaddAreatest_LDADD = $(top_builddir)/dymaxion/Terrain.lo \
                           $(top_builddir)/dymaxion/Segment.lo \
                           $(top_builddir)/dymaxion/Area.lo

traitstest_SOURCES = traitstest.cpp
