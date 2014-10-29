// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#ifndef DYMAXION_TUPLE_TRAITS_H
#define DYMAXION_TUPLE_TRAITS_H

#include <dymaxion/traits.h>

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

#endif // DYMAXION_TUPLE_TRAITS_H

