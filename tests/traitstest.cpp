// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include "Test.h"

#include <dymaxion/tuple_traits.h>
#include <dymaxion/wfmath_traits.h>

using dymaxion::traits::axisbox_access;
using dymaxion::traits::point_access;
using dymaxion::traits::point_construct;
using dymaxion::traits::point_subtract;
using dymaxion::traits::point_add;

using dymaxion::TuplePoint2;

class Tuple_Point2_traitstest : public Test::Suite
{
 public:
  Tuple_Point2_traitstest();

  void setup() override;
  void teardown() override;

  void test_access_get();
  void test_access_set();

};

Tuple_Point2_traitstest::Tuple_Point2_traitstest()
{
  ADD_TEST(Tuple_Point2_traitstest::test_access_get);
  ADD_TEST(Tuple_Point2_traitstest::test_access_set);
}

void Tuple_Point2_traitstest::setup()
{
}

void Tuple_Point2_traitstest::teardown()
{
}

void Tuple_Point2_traitstest::test_access_get()
{
  std::tuple<float, float> a { 1.2f, 2.3f };

  ASSERT_EQUAL((point_access<TuplePoint2, 0>::get(a)), 1.2f);
  ASSERT_EQUAL((point_access<TuplePoint2, 1>::get(a)), 2.3f);
}

void Tuple_Point2_traitstest::test_access_set()
{
  std::tuple<float, float> b;

  point_access<TuplePoint2, 0>::set(b, 7.9f);
  point_access<TuplePoint2, 1>::set(b, 6.3f);

  ASSERT_EQUAL(std::get<0>(b), 7.9f);
  ASSERT_EQUAL(std::get<1>(b), 6.3f);
}

class WFMath_AxisBox_traitstest : public Test::Suite
{
 public:
  WFMath_AxisBox_traitstest();

  void setup() override;
  void teardown() override;

};

WFMath_AxisBox_traitstest::WFMath_AxisBox_traitstest()
{
}

void WFMath_AxisBox_traitstest::setup()
{
}

void WFMath_AxisBox_traitstest::teardown()
{
}

class WFMath_Point_traitstest : public Test::Suite
{
 private:
  template <class P>
  P getPoint2();

  template <class P>
  P getPoint3();

  template <class P>
  void setPoint2(const P &);

  template <class P>
  void setPoint3(const P &);

  static constexpr float getPoint_x = .23f;
  static constexpr float getPoint_y = 1.7f;
  static constexpr float getPoint_z = 5.9f;

  static constexpr float setPoint_x = .17f;
  static constexpr float setPoint_y = 2.3f;
  static constexpr float setPoint_z = 9.5f;

  float m_x = 0.f;
  float m_y = 0.f;
  float m_z = 0.f;
 public:
  WFMath_Point_traitstest();

  void setup() override;
  void teardown() override;

  void test_access_wfmath_point2_set();
  void test_access_wfmath_point2_get();
  void test_access_wfmath_point3_set();
  void test_access_wfmath_point3_get();
  void test_construct_point2();
  void test_construct_point3();
  void test_subtract();
  void test_add();

};

constexpr float WFMath_Point_traitstest::getPoint_x;
constexpr float WFMath_Point_traitstest::getPoint_y;
constexpr float WFMath_Point_traitstest::getPoint_z;

constexpr float WFMath_Point_traitstest::setPoint_x;
constexpr float WFMath_Point_traitstest::setPoint_y;
constexpr float WFMath_Point_traitstest::setPoint_z;

WFMath_Point_traitstest::WFMath_Point_traitstest()
{
  ADD_TEST(WFMath_Point_traitstest::test_access_wfmath_point2_set);
  ADD_TEST(WFMath_Point_traitstest::test_access_wfmath_point2_get);
  ADD_TEST(WFMath_Point_traitstest::test_access_wfmath_point3_set);
  ADD_TEST(WFMath_Point_traitstest::test_access_wfmath_point3_get);
  ADD_TEST(WFMath_Point_traitstest::test_construct_point2);
  ADD_TEST(WFMath_Point_traitstest::test_construct_point3);
  ADD_TEST(WFMath_Point_traitstest::test_subtract);
  ADD_TEST(WFMath_Point_traitstest::test_add);
}

void WFMath_Point_traitstest::setup()
{
  m_x = 0.f;
  m_y = 0.f;
  m_z = 0.f;
}

void WFMath_Point_traitstest::teardown()
{
}

template <class P>
P WFMath_Point_traitstest::getPoint2()
{
  P p;
  point_access<P, 0>::set(p, getPoint_x);
  point_access<P, 1>::set(p, getPoint_y);
  return p;
}

template <class P>
void WFMath_Point_traitstest::setPoint2(const P & p)
{
  m_x = point_access<P, 0>::get(p);
  m_y = point_access<P, 1>::get(p);
}

template <class P>
P WFMath_Point_traitstest::getPoint3()
{
  P p;
  point_access<P, 0>::set(p, getPoint_x);
  point_access<P, 1>::set(p, getPoint_y);
  point_access<P, 2>::set(p, getPoint_z);
  return p;
}

template <class P>
void WFMath_Point_traitstest::setPoint3(const P & p)
{
  m_x = point_access<P, 0>::get(p);
  m_y = point_access<P, 1>::get(p);
  m_z = point_access<P, 2>::get(p);
}

void WFMath_Point_traitstest::test_access_wfmath_point2_set()
{
  WFMath::Point<2> p;
  p = getPoint2<WFMath::Point<2> >();

  ASSERT_EQUAL(p.x(), getPoint_x);
  ASSERT_EQUAL(p.y(), getPoint_y);
}

void WFMath_Point_traitstest::test_access_wfmath_point2_get()
{
  WFMath::Point<2> p(setPoint_x, setPoint_y);

  setPoint2(p);

  ASSERT_EQUAL(m_x, setPoint_x);
  ASSERT_EQUAL(m_y, setPoint_y);
}

void WFMath_Point_traitstest::test_access_wfmath_point3_set()
{
  WFMath::Point<3> p;
  p = getPoint3<WFMath::Point<3> >();

  ASSERT_EQUAL(p.x(), getPoint_x);
  ASSERT_EQUAL(p.y(), getPoint_y);
  ASSERT_EQUAL(p.z(), getPoint_z);
}

void WFMath_Point_traitstest::test_access_wfmath_point3_get()
{
  WFMath::Point<3> p(setPoint_x, setPoint_y, setPoint_z);

  setPoint3(p);

  ASSERT_EQUAL(m_x, setPoint_x);
  ASSERT_EQUAL(m_y, setPoint_y);
  ASSERT_EQUAL(m_z, setPoint_z);
}

void WFMath_Point_traitstest::test_construct_point2()
{
  WFMath::Point<2> p = point_construct<WFMath::Point<2> >::make(setPoint_x, setPoint_y);

  ASSERT_EQUAL(p.x(), setPoint_x);
  ASSERT_EQUAL(p.y(), setPoint_y);
}

void WFMath_Point_traitstest::test_construct_point3()
{
  WFMath::Point<3> p = point_construct<WFMath::Point<3> >::make(setPoint_x, setPoint_y, setPoint_z);

  ASSERT_EQUAL(p.x(), setPoint_x);
  ASSERT_EQUAL(p.y(), setPoint_y);
  ASSERT_EQUAL(p.z(), setPoint_z);
}

void WFMath_Point_traitstest::test_subtract()
{
  WFMath::Point<2> p1(3.7f, 9.4f);
  WFMath::Point<2> p2(8.1f, 7.3f);

  WFMath::Vector<2> res = point_subtract<WFMath::Vector<2>,
                                         WFMath::Point<2>,
                                         WFMath::Point<2>, 2>::op(p1, p2);

  WFMath::Vector<2> re2 = p1 - p2;

  WFMath::Vector<2> ref_val(-4.4f, 2.1f);

  ASSERT_EQUAL(res, ref_val);
  ASSERT_EQUAL(re2, ref_val);
  ASSERT_EQUAL(res, re2);
}

void WFMath_Point_traitstest::test_add()
{
  WFMath::Point<2> p1(3.7f, 9.4f);
  WFMath::Vector<2> v2(8.1f, 7.3f);

  WFMath::Point<2> res = point_add<WFMath::Point<2>,
                                   WFMath::Point<2>,
                                   WFMath::Vector<2>, 2>::op(p1, v2);

  WFMath::Point<2> re2 = p1 + v2;

  WFMath::Point<2> ref_val(11.8f, 16.7f);

  ASSERT_EQUAL(res, ref_val);
  ASSERT_EQUAL(re2, ref_val);
  ASSERT_EQUAL(res, re2);
}

int main()
{
  Tuple_Point2_traitstest t1;
  WFMath_Point_traitstest t2;
  WFMath_AxisBox_traitstest t3;

  return t1.run() + t2.run() + t3.run();
}

