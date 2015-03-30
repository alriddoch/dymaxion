
// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2009 Alistair Riddoch

#include <dymaxion/Terrain.h>
#include <dymaxion/GrassShader.h>
#include <dymaxion/Segment.h>

#include <cassert>

void testGrassShader()
{
  dymaxion::Terrain terrain(dymaxion::Terrain::SHADED, 16);

  dymaxion::Shader::Parameters params;
  params[dymaxion::GrassShader::key_lowThreshold] = 2.f;
  params[dymaxion::GrassShader::key_highThreshold] = 15.f;
  params[dymaxion::GrassShader::key_cutoff] = 0.4f;
  params[dymaxion::GrassShader::key_intercept] = 4.f;

  dymaxion::GrassShader* dshade = new dymaxion::GrassShader();
  delete dshade;
  dshade = new dymaxion::GrassShader(params);
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

  // This segment is too low to shade
  seg = terrain.getSegment(1, 0);
  dshade->checkIntersect(*seg);
}

int main()
{
  testGrassShader();

  return 0;
}

