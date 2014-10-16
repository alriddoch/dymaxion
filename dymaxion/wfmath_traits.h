// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_WFMATH_TRAITS_H
#define DYMAXION_WFMATH_TRAITS_H

#include <dymaxion/traits.h>

#include <wfmath/point.h>

namespace dymaxion
{

namespace traits
{

template <int idx>
class point_access<WFMath::Point<2>, idx>
{
 public:
  typedef WFMath::CoordType coord_type;
  typedef WFMath::Point<2> point_type;

  static coord_type get(const point_type & p)
  {
    return p[idx];
  }

  static void set(point_type & p, coord_type v)
  {
    p[idx] = v;
  }
};

template <>
point_access<WFMath::Point<2>, 0>::coord_type point_access<WFMath::Point<2>, 0>::get(const point_access<WFMath::Point<2>, 0>::point_type & p)
{
  return p.x();
}

template <>
point_access<WFMath::Point<2>, 1>::coord_type point_access<WFMath::Point<2>, 1>::get(const point_access<WFMath::Point<2>, 1>::point_type & p)
{
  return p.y();
}

template <>
void point_access<WFMath::Point<2>, 0>::set(point_access<WFMath::Point<2>, 0>::point_type & p,
                                            point_access<WFMath::Point<2>, 0>::coord_type val)
{
  p.x() = val;
}

template <>
void point_access<WFMath::Point<2>, 1>::set(point_access<WFMath::Point<2>, 1>::point_type & p,
                                            point_access<WFMath::Point<2>, 1>::coord_type val)
{
  p.y() = val;
}

template <>
class point_construct<WFMath::Point<2>>
{
 public:
  typedef WFMath::CoordType coord_type;
  typedef WFMath::Point<2> point_type;

};

}

}

#endif // DYMAXION_WFMATH_TRAITS_H
