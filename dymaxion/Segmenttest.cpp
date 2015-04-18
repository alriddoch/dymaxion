// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2009 Alistair Riddoch

#include "Test.h"

#include <dymaxion/Segment_impl.h>

#include <dymaxion/tuple_traits.h>

#include <wfmath/point.h>
#include <wfmath/axisbox.h>

class Segmenttest : public Test::Suite
{
 private:
  dymaxion::Segment * s;
 public:
  Segmenttest();

  void setup() override;
  void teardown() override;

  void test_getHeightAndNormalAny();

};

Segmenttest::Segmenttest()
{
  ADD_TEST(Segmenttest::test_getHeightAndNormalAny);
}

void Segmenttest::setup()
{
  s = new dymaxion::Segment(0, 0, 64);

  s->populate();
  s->populateNormals();
}

void Segmenttest::teardown()
{
  delete s;
}

void Segmenttest::test_getHeightAndNormalAny()
{
  std::tuple<float, float, float> normal;
  float h;
  s->getHeightAndNormalAny(0, 0, h, normal);
}

int main()
{
  dymaxion::Segment s(0, 0, 64);

  s.populate();
  s.populateNormals();
  s.populateSurfaces();
  s.invalidate();

  s.populate();
  s.populateNormals();
  s.populateSurfaces();

  float h;
  std::tuple<float, float, float> normal;
  s.getHeightAndNormal(17.0, 23.0, h, normal);
  s.getHeightAndNormal(17.9, 23.1, h, normal);
  s.getHeightAndNormal(17.1, 23.9, h, normal);

  unsigned int lx, ly, hx, hy;
  s.clipToSegment(dymaxion::Segment::rect_type(
                    dymaxion::Segment::point_type(50, 50),
                    dymaxion::Segment::point_type(100, 100)
                    ), lx, hx, ly, hy);

  Segmenttest t;
  return t.run();
}

// stubs

#include <dymaxion/Shader.h>
#include <dymaxion/Surface.h>

namespace dymaxion {

constexpr float BasePoint::HEIGHT;
constexpr float BasePoint::ROUGHNESS;
constexpr float BasePoint::FALLOFF;

void Surface::populate()
{
}

Surface * Shader::newSurface(Segment const & segment) const
{
  return 0;
}

}
