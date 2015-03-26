// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#ifndef DYMAXION_TUPLE_TRAITS_H
#define DYMAXION_TUPLE_TRAITS_H

#include <dymaxion/traits.h>

#include <boost/geometry.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>

#include <tuple>

namespace dymaxion
{

typedef std::tuple<float, float> TuplePoint2;

namespace traits
{

template <>
class types<TuplePoint2>
{
 public:
  typedef float coord_type;
};

template <int idx>
class point_access<TuplePoint2, idx>
{
 public:
  typedef typename types<TuplePoint2>::coord_type coord_type;
  typedef TuplePoint2 point_type;

  static coord_type get(const point_type & p)
  {
    static_assert(2 > idx,
                  "Index of accessed coordinate must be smaller than dimensions");
    return std::get<idx>(p);
  }

  static void set(point_type & p, coord_type v)
  {
    static_assert(2 > idx,
                  "Index of accessed coordinate must be smaller than dimensions");
    std::get<idx>(p) = v;
  }

};

template <>
class point_construct<TuplePoint2>
{
 public:
  typedef typename types<TuplePoint2>::coord_type coord_type;
  typedef TuplePoint2 point_type;

  static point_type make(coord_type x, coord_type y)
  {
    return point_type(x, y);
  }

};

}

}

namespace boost
{

namespace geometry
{

namespace traits
{

template <class FloatT>
struct tag<std::tuple<FloatT, FloatT> >
{
  typedef point_tag type;
};

template <class FloatT>
struct coordinate_type<std::tuple<FloatT, FloatT> >
{
  typedef FloatT type;
};

template <class FloatT>
struct coordinate_system<std::tuple<FloatT, FloatT> >
{
  typedef cs::cartesian type;
};

template <class FloatT>
struct dimension<std::tuple<FloatT, FloatT> >
  : boost::mpl::int_<2>
{ };

template <class FloatT>
struct access<std::tuple<FloatT, FloatT>, 0>
{
  static FloatT get(std::tuple<FloatT, FloatT> const & p)
  {
    return std::get<0>(p);

  };

  static void set(std::tuple<FloatT, FloatT> & p, FloatT const & value)
  {
    std::get<0>(p) = value;
  }

};

template <class FloatT>
struct access<std::tuple<FloatT, FloatT>, 1>
{
  static FloatT get(std::tuple<FloatT, FloatT> const & p)
  {
    return std::get<1>(p);

  };

  static void set(std::tuple<FloatT, FloatT> & p, FloatT const & value)
  {
    std::get<1>(p) = value;
  }

};

}

}
}

#endif // DYMAXION_TUPLE_TRAITS_H

