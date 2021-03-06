
// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2009 Alistair Riddoch

#include <dymaxion/Terrain.h>
#include <dymaxion/FillShader.h>
#include <dymaxion/Segment.h>

#include <cassert>

void testFillShader()
{
  dymaxion::Terrain terrain(dymaxion::Terrain::SHADED, 16);

  dymaxion::Shader::Parameters params;

  dymaxion::FillShader * dshade = new dymaxion::FillShader();
  delete dshade;
  dshade = new dymaxion::FillShader(params);
  terrain.addShader(dshade, 0);

  terrain.setBasePoint(0, 0, -20);
  terrain.setBasePoint(0, 1, 1);
  terrain.setBasePoint(1, 0, 2);
  terrain.setBasePoint(1, 1, 0.5);

  dymaxion::Segment * seg = terrain.getSegment(0, 0);

  seg->populate();
  seg->populateSurfaces();
}

int main()
{
  testFillShader();

  return 0;
}

