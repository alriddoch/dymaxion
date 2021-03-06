
// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2009 Alistair Riddoch

#include <dymaxion/Terrain.h>
#include <dymaxion/DepthShader.h>
#include <dymaxion/Segment.h>

#include <cassert>

void testDepthShader()
{
  dymaxion::Terrain terrain(dymaxion::Terrain::SHADED, 16);

  dymaxion::Shader::Parameters params;
  params[dymaxion::DepthShader::key_waterLevel] = 0.f;
  params[dymaxion::DepthShader::key_murkyDepth] = -12.f;

  dymaxion::DepthShader * dshade = new dymaxion::DepthShader();
  delete dshade;
  dshade = new dymaxion::DepthShader(params);
  terrain.addShader(dshade, 0);

  terrain.setBasePoint(0, 0, -20);
  terrain.setBasePoint(0, 1, 1);
  terrain.setBasePoint(1, 0, 2);
  terrain.setBasePoint(1, 1, 0.5);
  terrain.setBasePoint(2, 0, 2);
  terrain.setBasePoint(2, 1, 0.5);

  dymaxion::Segment * seg = terrain.getSegment(0, 0);

  seg->populateSurfaces();
  seg->populate();
  seg->populateSurfaces();

  seg = terrain.getSegment(1, 0);
  dshade->checkIntersect(*seg);
}

int main()
{
  testDepthShader();

  return 0;
}

