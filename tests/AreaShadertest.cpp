// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2009 Alistair Riddoch

#include "Test.h"

#include <dymaxion/Terrain.h>
#include <dymaxion/Area.h>
#include <dymaxion/AreaShader.h>
#include <dymaxion/Segment.h>

#include <cassert>

typedef WFMath::Point<2> Point2;

class AreaShadertest : public Test::Suite
{
 public:
  AreaShadertest();

  void setup() override;
  void teardown() override;

  void test_AreaShader();
};

AreaShadertest::AreaShadertest()
{
  ADD_TEST(AreaShadertest::test_AreaShader);
}

void AreaShadertest::setup()
{
}

void AreaShadertest::teardown()
{
}

void AreaShadertest::test_AreaShader()
{
    dymaxion::Area* a1 = new dymaxion::Area(1, false);
    
    dymaxion::Area::ring p;
    p.push_back(dymaxion::Area::point(3, 4));
    p.push_back(dymaxion::Area::point(3, 10));
    p.push_back(dymaxion::Area::point(14, 12));
    p.push_back(dymaxion::Area::point(18, 4));
    p.push_back(dymaxion::Area::point(17, 2));
    p.push_back(dymaxion::Area::point(6, -2));
    p.push_back(dymaxion::Area::point(3, 4));
    a1->setShape(p);
    
    dymaxion::Terrain terrain(dymaxion::Terrain::SHADED, 16);
    
    dymaxion::AreaShader* ashade = new dymaxion::AreaShader(1);
    terrain.addShader(ashade, 0);
    
    terrain.setBasePoint(0, 0, -1);
    terrain.setBasePoint(0, 1, 8);
    terrain.setBasePoint(1, 0, 2);
    terrain.setBasePoint(1, 1, 11);
    
    terrain.addArea(a1);
    
    dymaxion::Segment* seg = terrain.getSegment(0,0);
    assert(a1->checkIntersects(*seg));
    
    seg->populateSurfaces();
}

int main()
{
    AreaShadertest t;

    return t.run();
}
