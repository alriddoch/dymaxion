// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2004 Alistair Riddoch

#include "Test.h"

#include <dymaxion/Plant.h>
#include <dymaxion/wfmath_traits.h>

#ifdef NDEBUG
#undef NDEBUG
#endif
#ifndef DEBUG
#define DEBUG
#endif

#include <cassert>

class Planttest : public Test::Suite
{
 private:
  dymaxion::Plant * a = 0;
 public:
  Planttest();

  void setup() override;
  void teardown() override;

  void test_getDisplacement();
  void test_setDisplacement_wfmath();
  void test_setDisplacement();
  void test_getOrientation();
  void test_setHeight();

};

Planttest::Planttest()
{
  ADD_TEST(Planttest::test_getDisplacement);
  ADD_TEST(Planttest::test_setDisplacement_wfmath);
  ADD_TEST(Planttest::test_setDisplacement);
  ADD_TEST(Planttest::test_getOrientation);
  ADD_TEST(Planttest::test_setHeight);
}

void Planttest::setup()
{
  a = new dymaxion::Plant();
}

void Planttest::teardown()
{
  delete a;
}

void Planttest::test_getDisplacement()
{
  WFMath::Point<2> p1 = a->getDisplacement<WFMath::Point<2> >();
  assert(p1.isValid());
}

void Planttest::test_setDisplacement_wfmath()
{
  a->setDisplacement(WFMath::Point<2>(2.5f, 3.f));
  WFMath::Point<2> p3 = a->getDisplacement<WFMath::Point<2> >();
  assert(p3.isValid());
}

void Planttest::test_setDisplacement()
{
  a->setDisplacement(2.5f, 3.f);
  WFMath::Point<2> p3 = a->getDisplacement<WFMath::Point<2> >();
  assert(p3.isValid());
}

void Planttest::test_getOrientation()
{
  WFMath::Quaternion const & q1 = a->getOrientation();
  assert(!q1.isValid());
  WFMath::Quaternion q2 = a->getOrientation();
  assert(!q2.isValid());
  a->setOrientation(WFMath::Quaternion(2, 2.124f));
  WFMath::Quaternion const & q3 = a->getOrientation();
  assert(q3.isValid());

}

void Planttest::test_setHeight()
{
  a->setHeight(5.5f);
}

int main()
{
  Planttest t;

  t.run();
}

