// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2009 Alistair Riddoch

#include <dymaxion/Terrain.h>
#include <dymaxion/ThresholdShader.h>
#include <dymaxion/Segment.h>

#include <cassert>

void testHighShader()
{
  dymaxion::Terrain terrain(dymaxion::Terrain::SHADED, 16);

  dymaxion::Shader::Parameters params;
  params[dymaxion::HighShader::key_threshold] = 5.f;

  dymaxion::HighShader* dshade = new dymaxion::HighShader();
  delete dshade;
  dshade = new dymaxion::HighShader(params);
  terrain.addShader(dshade, 0);

  terrain.setBasePoint(0, 0, 20);
  terrain.setBasePoint(0, 1, 1);
  terrain.setBasePoint(1, 0, 2);
  terrain.setBasePoint(1, 1, 0.5);
  terrain.setBasePoint(2, 0, 2);
  terrain.setBasePoint(2, 1, 0.5);

  dymaxion::Segment* seg = terrain.getSegment(0, 0);

  seg->populateSurfaces();
  seg->populate();
  seg->populateSurfaces();

  seg = terrain.getSegment(1, 0);
  dshade->checkIntersect(*seg);
}

void testLowShader()
{
  dymaxion::Terrain terrain(dymaxion::Terrain::SHADED, 16);

  dymaxion::Shader::Parameters params;
  params[dymaxion::LowShader::key_threshold] = 5.f;

  dymaxion::LowShader* dshade = new dymaxion::LowShader();
  delete dshade;
  dshade = new dymaxion::LowShader(params);
  terrain.addShader(dshade, 0);

  terrain.setBasePoint(0, 0, 2);
  terrain.setBasePoint(0, 1, 1);
  terrain.setBasePoint(1, 0, 20);
  terrain.setBasePoint(1, 1, 10);
  terrain.setBasePoint(2, 0, 15);
  terrain.setBasePoint(2, 1, 19);

  dymaxion::Segment* seg = terrain.getSegment(0, 0);

  seg->populateSurfaces();
  seg->populate();
  seg->populateSurfaces();

  seg = terrain.getSegment(1, 0);
  dshade->checkIntersect(*seg);
}

void testBandShader()
{
  dymaxion::Terrain terrain(dymaxion::Terrain::SHADED, 16);

  dymaxion::Shader::Parameters params;
  params[dymaxion::BandShader::key_lowThreshold] = 2.f;
  params[dymaxion::BandShader::key_highThreshold] = 8.f;

  dymaxion::BandShader* dshade = new dymaxion::BandShader();
  delete dshade;
  dshade = new dymaxion::BandShader(params);
  terrain.addShader(dshade, 0);

  terrain.setBasePoint(0, 0, 2);
  terrain.setBasePoint(0, 1, 1);
  terrain.setBasePoint(1, 0, 20);
  terrain.setBasePoint(1, 1, 10);
  terrain.setBasePoint(2, 0, 15);
  terrain.setBasePoint(2, 1, 19);

  dymaxion::Segment* seg = terrain.getSegment(0, 0);

  seg->populateSurfaces();
  seg->populate();
  seg->populateSurfaces();

  seg = terrain.getSegment(1, 0);
  dshade->checkIntersect(*seg);
}

int main()
{
  testHighShader();
  testLowShader();
  testBandShader();

  return 0;
}

