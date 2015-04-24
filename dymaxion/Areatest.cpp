// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2015 Alistair Riddoch

#include "test/Test.h"

#include <dymaxion/Area.h>
#include <dymaxion/Segment.h>

class Areatest : public Test::Suite
{
 public:
  Areatest();

  void setup() override;
  void teardown() override;

  void test_Area();
  void test_setShape();
  void test_setShader();
  void test_contains_true();
  void test_contains_false();
  void test_checkIntersects_true();
  void test_checkIntersects_false();
  void test_clipToSegment();

};

Areatest::Areatest()
{
  ADD_TEST(Areatest::test_Area);
  ADD_TEST(Areatest::test_setShape);
  ADD_TEST(Areatest::test_setShader);
  ADD_TEST(Areatest::test_contains_true);
  ADD_TEST(Areatest::test_contains_false);
  ADD_TEST(Areatest::test_checkIntersects_true);
  ADD_TEST(Areatest::test_checkIntersects_false);
  ADD_TEST(Areatest::test_clipToSegment);
}

void Areatest::setup()
{
}

void Areatest::teardown()
{
}

void Areatest::test_Area()
{
  dymaxion::Area a(0, false);
}

void Areatest::test_setShape()
{
  dymaxion::Area a(0, false);

  dymaxion::Area::ring r;
  r.push_back(dymaxion::Area::point(1, 0));
  r.push_back(dymaxion::Area::point(0, -1));
  r.push_back(dymaxion::Area::point(-1, 0));
  r.push_back(dymaxion::Area::point(0, 1));
  r.push_back(dymaxion::Area::point(1, 0));
  a.setShape(r);

}

void Areatest::test_setShader()
{
  dymaxion::Area a(0, false);

  a.setShader(nullptr);
}

void Areatest::test_contains_true()
{
  dymaxion::Area a(0, false);

  dymaxion::Area::ring r;
  r.push_back(dymaxion::Area::point(1, 0));
  r.push_back(dymaxion::Area::point(0, -1));
  r.push_back(dymaxion::Area::point(-1, 0));
  r.push_back(dymaxion::Area::point(0, 1));
  r.push_back(dymaxion::Area::point(1, 0));
  a.setShape(r);

  ASSERT_TRUE(a.contains(0.f, 0.f));
}

void Areatest::test_contains_false()
{
  dymaxion::Area a(0, false);

  dymaxion::Area::ring r;
  r.push_back(dymaxion::Area::point(1, 0));
  r.push_back(dymaxion::Area::point(0, -1));
  r.push_back(dymaxion::Area::point(-1, 0));
  r.push_back(dymaxion::Area::point(0, 1));
  r.push_back(dymaxion::Area::point(1, 0));
  a.setShape(r);

  ASSERT_TRUE(!a.contains(2.f, 2.f));
}

void Areatest::test_checkIntersects_true()
{
  dymaxion::Area a(0, false);

  dymaxion::Area::ring r;
  r.push_back(dymaxion::Area::point(1, 0));
  r.push_back(dymaxion::Area::point(0, -1));
  r.push_back(dymaxion::Area::point(-1, 0));
  r.push_back(dymaxion::Area::point(0, 1));
  r.push_back(dymaxion::Area::point(1, 0));
  a.setShape(r);

  dymaxion::Segment s(0, 0, dymaxion::defaultResolution);

  std::cout << "BAR: " << std::endl;

  ASSERT_TRUE(a.checkIntersects(s));
}

void Areatest::test_checkIntersects_false()
{
  dymaxion::Area a(0, false);

  dymaxion::Area::ring r;
  r.push_back(dymaxion::Area::point(-1, -2));
  r.push_back(dymaxion::Area::point(-2, -3));
  r.push_back(dymaxion::Area::point(-3, -2));
  r.push_back(dymaxion::Area::point(-2, -1));
  r.push_back(dymaxion::Area::point(-1, -2));
  a.setShape(r);

  dymaxion::Segment s(0, 0, dymaxion::defaultResolution);

  std::cout << "BAR: " << std::endl;

  ASSERT_TRUE(!a.checkIntersects(s));
}

void Areatest::test_clipToSegment()
{
  dymaxion::Area a(0, false);

  dymaxion::Area::ring r;
  r.push_back(dymaxion::Area::point(1, 0));
  r.push_back(dymaxion::Area::point(0, -1));
  r.push_back(dymaxion::Area::point(-1, 0));
  r.push_back(dymaxion::Area::point(0, 1));
  r.push_back(dymaxion::Area::point(1, 0));
  a.setShape(r);

  dymaxion::Segment s(0, 0, dymaxion::defaultResolution);

  std::cout << "BAR: " << std::endl;

  dymaxion::Area::ring result = a.clipToSegment(s);

  std::cout << "FOO: " << result.size() << std::endl;

  dymaxion::Area::ring::const_iterator I = result.begin();
  dymaxion::Area::ring::const_iterator Iend = result.end();
  for (; I != Iend; ++I)
  {
    std::cout << I->x() << "," << I->y() << std::endl;
  }
}

int main()
{
  Areatest t;

  return t.run();
}

// stubs

#include <dymaxion/Segment.h>

#include <wfmath/point.h>

namespace dymaxion {

Effector::Effector()
{
}

Effector::~Effector()
{
}

Segment::Segment(int x, int y, unsigned int res) : m_res(res), m_size(res + 1),
                                                   m_xRef(x), m_yRef(y)
{
}

Segment::~Segment()
{
}

Segment::rect_type Segment::getRect() const
{
  point_type lp(0, 0), hp(64, 64);
  return rect_type(lp, hp);
}

int Segment::addArea(Area const * area)
{
  return 0;
}

int Segment::updateArea(Area const * area)
{
  return 0;
}

int Segment::removeArea(Area const * area)
{
  return 0;
}

}
