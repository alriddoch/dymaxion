// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include "Test.h"

#include <dymaxion/Edge.h>
#include <dymaxion/tuple_traits.h>
#include <dymaxion/wfmath_traits.h>

#include <cassert>

using dymaxion::traits::point_access;

std::ostream & operator<<(std::ostream & os,
                          const dymaxion::Edge<dymaxion::Point2> & e)
{
  os << "Edge(" << point_access<dymaxion::Point2, 0>::get(e.start())
     << "," << point_access<dymaxion::Point2, 1>::get(e.start())
     << "),(" << point_access<dymaxion::Point2, 0>::get(e.end())
     << "," << point_access<dymaxion::Point2, 1>::get(e.end()) << ")";
  return os;
}

std::ostream & operator<<(std::ostream & os,
                          const dymaxion::Point2 & e)
{
  os << "Point2(" << point_access<dymaxion::Point2, 0>::get(e)
     << "," << point_access<dymaxion::Point2, 1>::get(e) << ")";
  return os;
}

class Edgetest : public Test::Suite
{
 public:
  Edgetest();

  void setup() override;
  void teardown() override;

  void test_Edge();
  void test_xValueAtY();
  void test_xValueAtY_oob();
  void test_sort_order();
  void test_sort_order_inv();
  void test_sort_order_equal();
};

Edgetest::Edgetest()
{
  ADD_TEST(Edgetest::test_Edge);
  ADD_TEST(Edgetest::test_xValueAtY);
  ADD_TEST(Edgetest::test_xValueAtY_oob);
  ADD_TEST(Edgetest::test_sort_order);
  ADD_TEST(Edgetest::test_sort_order_inv);
  ADD_TEST(Edgetest::test_sort_order_equal);
}

void Edgetest::setup()
{
}

void Edgetest::teardown()
{
}

void Edgetest::test_Edge()
{
  dymaxion::Edge<> a(dymaxion::Point2(1, 2), dymaxion::Point2(7, 8));

  ASSERT_EQUAL(a.m_start, dymaxion::Point2(1, 2));
  ASSERT_EQUAL(a.m_seg, dymaxion::Vector2(6, 6));
  ASSERT_EQUAL(a.m_inverseGradient, 1);
}

void Edgetest::test_xValueAtY()
{
  dymaxion::Edge<> a(dymaxion::Point2(1, 2), dymaxion::Point2(7, 8));

  ASSERT_EQUAL(a.xValueAtY(5), 4);
}

void Edgetest::test_xValueAtY_oob()
{
  dymaxion::Edge<> a(dymaxion::Point2(1, 2), dymaxion::Point2(7, 8));

  ASSERT_EQUAL(a.xValueAtY(10), 9);
}

void Edgetest::test_sort_order()
{
  dymaxion::Edge<> a(dymaxion::Point2(1, 2), dymaxion::Point2(7, 8));
  dymaxion::Edge<> b(dymaxion::Point2(2, 3), dymaxion::Point2(7, 8));

  ASSERT_LESS(a, b);
}

void Edgetest::test_sort_order_inv()
{
  dymaxion::Edge<> a(dymaxion::Point2(2, 3), dymaxion::Point2(7, 8));
  dymaxion::Edge<> b(dymaxion::Point2(1, 2), dymaxion::Point2(7, 8));

  ASSERT_NOT_LESS(a, b);
}

void Edgetest::test_sort_order_equal()
{
  dymaxion::Edge<> a(dymaxion::Point2(1, 2), dymaxion::Point2(7, 8));
  dymaxion::Edge<> b(dymaxion::Point2(1, 2), dymaxion::Point2(7, 8));

  ASSERT_NOT_LESS(a, b);
}

class EdgeAtYtest : public Test::Suite
{
 public:
  EdgeAtYtest();

  void setup() override;
  void teardown() override;

  void test_EdgeAtY();
  void test_intersect();
  void test_intersect_false();
};

EdgeAtYtest::EdgeAtYtest()
{
  ADD_TEST(EdgeAtYtest::test_EdgeAtY);
  ADD_TEST(EdgeAtYtest::test_intersect);
  ADD_TEST(EdgeAtYtest::test_intersect_false);
}

void EdgeAtYtest::setup()
{
}

void EdgeAtYtest::teardown()
{
}

void EdgeAtYtest::test_EdgeAtY()
{
  dymaxion::EdgeAtY<> a(1);

  ASSERT_EQUAL(a.m_y, 1);
}

void EdgeAtYtest::test_intersect()
{
  dymaxion::EdgeAtY<> a(2);

  dymaxion::Edge<> c(dymaxion::Point2(1, 2), dymaxion::Point2(7, 8));
  dymaxion::Edge<> d(dymaxion::Point2(2, 2), dymaxion::Point2(8, 8));
  
  ASSERT_TRUE(a(c, d));
}

void EdgeAtYtest::test_intersect_false()
{
  dymaxion::EdgeAtY<> a(2);

  dymaxion::Edge<> c(dymaxion::Point2(2, 2), dymaxion::Point2(8, 8));
  dymaxion::Edge<> d(dymaxion::Point2(1, 2), dymaxion::Point2(7, 8));
  
  ASSERT_TRUE(!a(c, d));
}

int main()
{
    Edgetest t;
    EdgeAtYtest t2;

    return t.run() + t2.run();
}
