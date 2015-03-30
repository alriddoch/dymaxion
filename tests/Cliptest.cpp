// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include "Test.h"

#include <dymaxion/Clip.h>
#include <dymaxion/wfmath_traits.h>

#include <wfmath/point.h>

typedef WFMath::Point<2> Point2;

class TopCliptest : public Test::Suite
{
 public:
  TopCliptest();

  void setup() override;
  void teardown() override;

  void test_Clip();
  void test_inside();
  void test_clip();

};

TopCliptest::TopCliptest()
{
  ADD_TEST(TopCliptest::test_Clip);
  ADD_TEST(TopCliptest::test_inside);
  ADD_TEST(TopCliptest::test_clip);
}

void TopCliptest::setup()
{
}

void TopCliptest::teardown()
{
}

void TopCliptest::test_Clip()
{
  dymaxion::TopClip tc(0.5f);

  ASSERT_EQUAL(tc.threshold, 0.5f);
}

void TopCliptest::test_inside()
{
  dymaxion::TopClip tc(0.5f);

  ASSERT_TRUE(!tc.inside(Point2(1, 1)))
  ASSERT_TRUE(!tc.inside(Point2(1, 0.5)))
  ASSERT_TRUE(tc.inside(Point2(1, 0)))
}

void TopCliptest::test_clip()
{
  dymaxion::TopClip tc(0.5f);

  auto p = tc.clip(Point2 { 0, 0 }, Point2 { 1, 1 });

  ASSERT_EQUAL(p, decltype(p) (0.5, 0.5f))

  auto p1 = tc.clip(Point2 { 0, 1 }, Point2 { 1, 0 });

  ASSERT_EQUAL(p1, decltype(p) (0.5, 0.5f))

  auto p2 = tc.clip(Point2 { 1, 0 }, Point2 { 2, 1 });

  ASSERT_EQUAL(p2, decltype(p) (1.5, 0.5f))
}

class BottomCliptest : public Test::Suite
{
 public:
  BottomCliptest();

  void setup() override;
  void teardown() override;

  void test_Clip();
  void test_inside();
  void test_clip();

};

BottomCliptest::BottomCliptest()
{
  ADD_TEST(BottomCliptest::test_Clip);
  ADD_TEST(BottomCliptest::test_inside);
  ADD_TEST(BottomCliptest::test_clip);
}

void BottomCliptest::setup()
{
}

void BottomCliptest::teardown()
{
}

void BottomCliptest::test_Clip()
{
  dymaxion::BottomClip tc(0.5f);

  ASSERT_EQUAL(tc.threshold, 0.5f);
}

void BottomCliptest::test_inside()
{
  dymaxion::BottomClip tc(0.5f);

  ASSERT_TRUE(tc.inside(Point2(1, 1)))
  ASSERT_TRUE(tc.inside(Point2(1, 0.5)))
  ASSERT_TRUE(!tc.inside(Point2(1, 0)))
}

void BottomCliptest::test_clip()
{
  dymaxion::BottomClip tc(0.5f);

  auto p = tc.clip(Point2 { 0, 0 }, Point2 { 1, 1 });

  ASSERT_EQUAL(p, decltype(p) (0.5, 0.5f))

  auto p1 = tc.clip(Point2 { 0, 1 }, Point2 { 1, 0 });

  ASSERT_EQUAL(p1, decltype(p) (0.5, 0.5f))

  auto p2 = tc.clip(Point2 { 1, 0 }, Point2 { 2, 1 });

  ASSERT_EQUAL(p2, decltype(p) (1.5, 0.5f))
}

class LeftCliptest : public Test::Suite
{
 public:
  LeftCliptest();

  void setup() override;
  void teardown() override;

  void test_Clip();
  void test_inside();
  void test_clip();

};

LeftCliptest::LeftCliptest()
{
  ADD_TEST(LeftCliptest::test_Clip);
  ADD_TEST(LeftCliptest::test_inside);
  ADD_TEST(LeftCliptest::test_clip);
}

void LeftCliptest::setup()
{
}

void LeftCliptest::teardown()
{
}

void LeftCliptest::test_Clip()
{
  dymaxion::LeftClip tc(0.5f);

  ASSERT_EQUAL(tc.threshold, 0.5f);
}

void LeftCliptest::test_inside()
{
  dymaxion::LeftClip tc(0.5f);

  ASSERT_TRUE(tc.inside(Point2(1, 1)))
  ASSERT_TRUE(tc.inside(Point2(0.5, 1)))
  ASSERT_TRUE(!tc.inside(Point2(0, 1)))
}

void LeftCliptest::test_clip()
{
  dymaxion::LeftClip tc(0.5f);

  auto p = tc.clip(Point2 { 0, 0 }, Point2 { 1, 1 });

  ASSERT_EQUAL(p, decltype(p) (0.5, 0.5f))

  auto p1 = tc.clip(Point2 { 0, 1 }, Point2 { 1, 0 });

  ASSERT_EQUAL(p1, decltype(p) (0.5, 0.5f))

  auto p2 = tc.clip(Point2 { 1, 0 }, Point2 { 2, 1 });

  ASSERT_EQUAL(p2, decltype(p) (0.5, -0.5f))
}

class RightCliptest : public Test::Suite
{
 public:
  RightCliptest();

  void setup() override;
  void teardown() override;

  void test_Clip();
  void test_inside();
  void test_clip();

};

RightCliptest::RightCliptest()
{
  ADD_TEST(RightCliptest::test_Clip);
  ADD_TEST(RightCliptest::test_inside);
  ADD_TEST(RightCliptest::test_clip);
}

void RightCliptest::setup()
{
}

void RightCliptest::teardown()
{
}

void RightCliptest::test_Clip()
{
  dymaxion::RightClip tc(0.5f);

  ASSERT_EQUAL(tc.threshold, 0.5f);
}

void RightCliptest::test_inside()
{
  dymaxion::RightClip tc(0.5f);

  ASSERT_TRUE(!tc.inside(Point2(1, 1)))
  ASSERT_TRUE(!tc.inside(Point2(0.5, 1)))
  ASSERT_TRUE(tc.inside(Point2(0, 1)))
}

void RightCliptest::test_clip()
{
  dymaxion::RightClip tc(0.5f);

  auto p = tc.clip(Point2 { 0, 0 }, Point2 { 1, 1 });

  ASSERT_EQUAL(p, decltype(p) (0.5, 0.5f))

  auto p1 = tc.clip(Point2 { 0, 1 }, Point2 { 1, 0 });

  ASSERT_EQUAL(p1, decltype(p) (0.5, 0.5f))

  auto p2 = tc.clip(Point2 { 1, 0 }, Point2 { 2, 1 });

  ASSERT_EQUAL(p2, decltype(p) (0.5, -0.5f))
}

int main()
{
  TopCliptest t1;
  BottomCliptest t2;
  LeftCliptest t3;
  RightCliptest t4;

  return t1.run() + t2.run() + t3.run() + t4.run();
}

