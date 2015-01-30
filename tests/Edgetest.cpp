// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include "Test.h"

#include <dymaxion/Edge.h>
#include <dymaxion/tuple_traits.h>
#include <dymaxion/wfmath_traits.h>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

using boost_point = boost::geometry::model::d2::point_xy<
    float,
    boost::geometry::cs::cartesian
>;

template <class PointT>
std::ostream & operator<<(std::ostream & os,
                          dymaxion::Edge<PointT> const & e)
{
  os << "Edge(" << boost::geometry::traits::access<PointT, 0>::get(e.start())
     << "," << boost::geometry::traits::access<PointT, 1>::get(e.start())
     << "),(" << boost::geometry::traits::access<PointT, 0>::get(e.end())
     << "," << boost::geometry::traits::access<PointT, 1>::get(e.end()) << ")";
  return os;
}

std::ostream & operator<<(std::ostream & os,
                          dymaxion::Point2 const & e)
{
  os << "Point2("
     << boost::geometry::traits::access<dymaxion::Point2, 0>::get(e) << ","
     << boost::geometry::traits::access<dymaxion::Point2, 1>::get(e) << ")";
  return os;
}

std::ostream & operator<<(std::ostream & os,
                          boost_point const & e)
{
  os << "Point2("
     << boost::geometry::traits::access<boost_point, 0>::get(e) << ","
     << boost::geometry::traits::access<boost_point, 1>::get(e) << ")";
  return os;
}

bool operator!=(boost_point const & lhs, boost_point const & rhs)
{
  return (lhs.x() != rhs.x() || lhs.y() != rhs.y());
}

template <typename PointT>
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

template <typename PointT>
Edgetest<PointT>::Edgetest()
{
  ADD_TEST(Edgetest<PointT>::test_Edge);
  ADD_TEST(Edgetest<PointT>::test_xValueAtY);
  ADD_TEST(Edgetest<PointT>::test_xValueAtY_oob);
  ADD_TEST(Edgetest<PointT>::test_sort_order);
  ADD_TEST(Edgetest<PointT>::test_sort_order_inv);
  ADD_TEST(Edgetest<PointT>::test_sort_order_equal);
}

template <typename PointT>
void Edgetest<PointT>::setup()
{
}

template <typename PointT>
void Edgetest<PointT>::teardown()
{
}

template <typename PointT>
void Edgetest<PointT>::test_Edge()
{
  dymaxion::Edge<PointT> a(PointT(1, 2), PointT(7, 8));

  ASSERT_EQUAL(a.m_start, PointT(1, 2));
  ASSERT_EQUAL(a.m_seg, dymaxion::Vector2(6, 6));
  ASSERT_EQUAL(a.m_inverseGradient, 1);
}

template <typename PointT>
void Edgetest<PointT>::test_xValueAtY()
{
  dymaxion::Edge<PointT> a(PointT(1, 2), PointT(7, 8));

  ASSERT_EQUAL(a.xValueAtY(3), 2);
  ASSERT_EQUAL(a.xValueAtY(4), 3);
  ASSERT_EQUAL(a.xValueAtY(5), 4);
  ASSERT_EQUAL(a.xValueAtY(6), 5);
  ASSERT_EQUAL(a.xValueAtY(3.5), 2.5);
}

template <typename PointT>
void Edgetest<PointT>::test_xValueAtY_oob()
{
  dymaxion::Edge<PointT> a(PointT(1, 2), PointT(7, 8));

  ASSERT_EQUAL(a.xValueAtY(1), 0);
  ASSERT_EQUAL(a.xValueAtY(-1), -2);
  ASSERT_EQUAL(a.xValueAtY(10), 9);
  ASSERT_EQUAL(a.xValueAtY(0.5), -0.5);
  ASSERT_EQUAL(a.xValueAtY(10.5), 9.5);
}

template <typename PointT>
void Edgetest<PointT>::test_sort_order()
{
  dymaxion::Edge<PointT> a(PointT(1, 2), PointT(7, 8));
  dymaxion::Edge<PointT> b(PointT(2, 3), PointT(7, 8));

  ASSERT_LESS(a, b);
}

template <typename PointT>
void Edgetest<PointT>::test_sort_order_inv()
{
  dymaxion::Edge<PointT> a(PointT(2, 3), PointT(7, 8));
  dymaxion::Edge<PointT> b(PointT(1, 2), PointT(7, 8));

  ASSERT_NOT_LESS(a, b);
}

template <typename PointT>
void Edgetest<PointT>::test_sort_order_equal()
{
  dymaxion::Edge<PointT> a(PointT(1, 2), PointT(7, 8));
  dymaxion::Edge<PointT> b(PointT(1, 2), PointT(7, 8));

  ASSERT_NOT_LESS(a, b);
  ASSERT_NOT_LESS(b, a);
}

template <class PointT>
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

template <class PointT>
EdgeAtYtest<PointT>::EdgeAtYtest()
{
  ADD_TEST(EdgeAtYtest<PointT>::test_EdgeAtY);
  ADD_TEST(EdgeAtYtest<PointT>::test_intersect);
  ADD_TEST(EdgeAtYtest<PointT>::test_intersect_false);
}

template <class PointT>
void EdgeAtYtest<PointT>::setup()
{
}

template <class PointT>
void EdgeAtYtest<PointT>::teardown()
{
}

template <class PointT>
void EdgeAtYtest<PointT>::test_EdgeAtY()
{
  dymaxion::EdgeAtY<PointT> a(1);

  ASSERT_EQUAL(a.m_y, 1);
}

template <class PointT>
void EdgeAtYtest<PointT>::test_intersect()
{
  dymaxion::EdgeAtY<PointT> a(2);

  dymaxion::Edge<PointT> c(PointT(1, 2), PointT(7, 8));
  dymaxion::Edge<PointT> d(PointT(2, 2), PointT(8, 8));
  
  ASSERT_TRUE(a(c, d));
}

template <class PointT>
void EdgeAtYtest<PointT>::test_intersect_false()
{
  dymaxion::EdgeAtY<PointT> a(2);

  dymaxion::Edge<PointT> c(PointT(2, 2), PointT(8, 8));
  dymaxion::Edge<PointT> d(PointT(1, 2), PointT(7, 8));
  
  ASSERT_TRUE(!a(c, d));
}

int main()
{
    Edgetest<dymaxion::Point2> t;
    Edgetest<WFMath::Point<2>> tw;
    Edgetest<boost_point> tb;

    EdgeAtYtest<dymaxion::Point2> t2;
    EdgeAtYtest<WFMath::Point<2>> t2w;
    EdgeAtYtest<boost_point> t2b;

    return t.run() + tw.run() + tb.run() + t2.run() + t2w.run() + t2b.run();
}
