// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_WFMATH_TRAITS_H
#define DYMAXION_WFMATH_TRAITS_H

#include <dymaxion/traits.h>

#include <wfmath/axisbox.h>
#include <wfmath/point.h>

namespace dymaxion
{

namespace traits
{

template <int dim, int idx>
class axisbox_access<WFMath::AxisBox<dim>, idx>
{
 public:
  typedef WFMath::CoordType coord_type;
  typedef WFMath::AxisBox<dim> axisbox_type;

  static coord_type get_near(const axisbox_type & b)
  {
    return b.lowCorner()[idx];
  }

  static coord_type get_far(const axisbox_type & b)
  {
    return b.highCorner()[idx];
  }

  static void set_near(axisbox_type & b, coord_type v)
  {
    b.lowCorner()[idx] = v;
  }

  static void set_far(axisbox_type & b, coord_type v)
  {
    b.highCorner()[idx] = v;
  }
};

template <>
inline axisbox_access<WFMath::AxisBox<2>, 0>::coord_type axisbox_access<WFMath::AxisBox<2>, 0>::get_near(const axisbox_access<WFMath::AxisBox<2>, 0>::axisbox_type & b)
{
  return b.lowCorner().x();
}

template <>
inline axisbox_access<WFMath::AxisBox<2>, 0>::coord_type axisbox_access<WFMath::AxisBox<2>, 0>::get_far(const axisbox_access<WFMath::AxisBox<2>, 0>::axisbox_type & b)
{
  return b.highCorner().x();
}

template <>
inline axisbox_access<WFMath::AxisBox<2>, 1>::coord_type axisbox_access<WFMath::AxisBox<2>, 1>::get_near(const axisbox_access<WFMath::AxisBox<2>, 1>::axisbox_type & b)
{
  return b.lowCorner().y();
}

template <>
inline axisbox_access<WFMath::AxisBox<2>, 1>::coord_type axisbox_access<WFMath::AxisBox<2>, 1>::get_far(const axisbox_access<WFMath::AxisBox<2>, 1>::axisbox_type & b)
{
  return b.highCorner().y();
}

template <>
inline void axisbox_access<WFMath::AxisBox<2>, 0>::set_near(axisbox_access<WFMath::AxisBox<2>, 0>::axisbox_type & b,
                                                            axisbox_access<WFMath::AxisBox<2>, 0>::coord_type val)
{
  b.lowCorner().x() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<2>, 0>::set_far(axisbox_access<WFMath::AxisBox<2>, 0>::axisbox_type & b,
                                                           axisbox_access<WFMath::AxisBox<2>, 0>::coord_type val)
{
  b.highCorner().x() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<2>, 1>::set_near(axisbox_access<WFMath::AxisBox<2>, 1>::axisbox_type & b,
                                                            axisbox_access<WFMath::AxisBox<2>, 1>::coord_type val)
{
  b.lowCorner().y() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<2>, 1>::set_far(axisbox_access<WFMath::AxisBox<2>, 1>::axisbox_type & b,
                                                           axisbox_access<WFMath::AxisBox<2>, 1>::coord_type val)
{
  b.highCorner().y() = val;
}

template <>
inline axisbox_access<WFMath::AxisBox<3>, 0>::coord_type axisbox_access<WFMath::AxisBox<3>, 0>::get_near(const axisbox_access<WFMath::AxisBox<3>, 0>::axisbox_type & b)
{
  return b.lowCorner().x();
}

template <>
inline axisbox_access<WFMath::AxisBox<3>, 0>::coord_type axisbox_access<WFMath::AxisBox<3>, 0>::get_far(const axisbox_access<WFMath::AxisBox<3>, 0>::axisbox_type & b)
{
  return b.highCorner().x();
}

template <>
inline axisbox_access<WFMath::AxisBox<3>, 1>::coord_type axisbox_access<WFMath::AxisBox<3>, 1>::get_near(const axisbox_access<WFMath::AxisBox<3>, 1>::axisbox_type & b)
{
  return b.lowCorner().y();
}

template <>
inline axisbox_access<WFMath::AxisBox<3>, 1>::coord_type axisbox_access<WFMath::AxisBox<3>, 1>::get_far(const axisbox_access<WFMath::AxisBox<3>, 1>::axisbox_type & b)
{
  return b.highCorner().y();
}

template <>
inline axisbox_access<WFMath::AxisBox<3>, 1>::coord_type axisbox_access<WFMath::AxisBox<3>, 2>::get_near(const axisbox_access<WFMath::AxisBox<3>, 1>::axisbox_type & b)
{
  return b.lowCorner().z();
}

template <>
inline axisbox_access<WFMath::AxisBox<3>, 1>::coord_type axisbox_access<WFMath::AxisBox<3>, 2>::get_far(const axisbox_access<WFMath::AxisBox<3>, 1>::axisbox_type & b)
{
  return b.highCorner().z();
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 0>::set_near(axisbox_access<WFMath::AxisBox<3>, 0>::axisbox_type & b,
                                                            axisbox_access<WFMath::AxisBox<3>, 0>::coord_type val)
{
  b.lowCorner().x() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 0>::set_far(axisbox_access<WFMath::AxisBox<3>, 0>::axisbox_type & b,
                                                           axisbox_access<WFMath::AxisBox<3>, 0>::coord_type val)
{
  b.highCorner().x() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 1>::set_near(axisbox_access<WFMath::AxisBox<3>, 1>::axisbox_type & b,
                                                            axisbox_access<WFMath::AxisBox<3>, 1>::coord_type val)
{
  b.lowCorner().y() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 1>::set_far(axisbox_access<WFMath::AxisBox<3>, 1>::axisbox_type & b,
                                                           axisbox_access<WFMath::AxisBox<3>, 1>::coord_type val)
{
  b.highCorner().y() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 2>::set_near(axisbox_access<WFMath::AxisBox<3>, 1>::axisbox_type & b,
                                                            axisbox_access<WFMath::AxisBox<3>, 1>::coord_type val)
{
  b.lowCorner().z() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 2>::set_far(axisbox_access<WFMath::AxisBox<3>, 1>::axisbox_type & b,
                                                           axisbox_access<WFMath::AxisBox<3>, 1>::coord_type val)
{
  b.highCorner().z() = val;
}

template <int dim, int idx>
class point_access<WFMath::Point<dim>, idx>
{
 public:
  typedef WFMath::CoordType coord_type;
  typedef WFMath::Point<dim> point_type;

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
inline point_access<WFMath::Point<2>, 0>::coord_type point_access<WFMath::Point<2>, 0>::get(const point_access<WFMath::Point<2>, 0>::point_type & p)
{
  return p.x();
}

template <>
inline point_access<WFMath::Point<2>, 1>::coord_type point_access<WFMath::Point<2>, 1>::get(const point_access<WFMath::Point<2>, 1>::point_type & p)
{
  return p.y();
}

template <>
inline void point_access<WFMath::Point<2>, 0>::set(point_access<WFMath::Point<2>, 0>::point_type & p,
                                            point_access<WFMath::Point<2>, 0>::coord_type val)
{
  p.setValid(true);
  p.x() = val;
}

template <>
inline void point_access<WFMath::Point<2>, 1>::set(point_access<WFMath::Point<2>, 1>::point_type & p,
                                            point_access<WFMath::Point<2>, 1>::coord_type val)
{
  p.y() = val;
}

template <>
inline point_access<WFMath::Point<3>, 0>::coord_type point_access<WFMath::Point<3>, 0>::get(const point_access<WFMath::Point<3>, 0>::point_type & p)
{
  return p.x();
}

template <>
inline point_access<WFMath::Point<3>, 1>::coord_type point_access<WFMath::Point<3>, 1>::get(const point_access<WFMath::Point<3>, 1>::point_type & p)
{
  return p.y();
}

template <>
inline point_access<WFMath::Point<3>, 2>::coord_type point_access<WFMath::Point<3>, 2>::get(const point_access<WFMath::Point<3>, 2>::point_type & p)
{
  return p.z();
}

template <>
inline void point_access<WFMath::Point<3>, 0>::set(point_access<WFMath::Point<3>, 0>::point_type & p,
                                            point_access<WFMath::Point<3>, 0>::coord_type val)
{
  p.setValid(true);
  p.x() = val;
}

template <>
inline void point_access<WFMath::Point<3>, 1>::set(point_access<WFMath::Point<3>, 1>::point_type & p,
                                            point_access<WFMath::Point<3>, 1>::coord_type val)
{
  p.y() = val;
}

template <>
inline void point_access<WFMath::Point<3>, 2>::set(point_access<WFMath::Point<3>, 2>::point_type & p,
                                            point_access<WFMath::Point<3>, 2>::coord_type val)
{
  p.z() = val;
}

template <>
class point_construct<WFMath::Point<2>>
{
 public:
  typedef WFMath::CoordType coord_type;
  typedef WFMath::Point<2> point_type;

  static point_type make(coord_type x, coord_type y)
  {
    return point_type(x, y);
  }
};

template <>
class point_construct<WFMath::Point<3>>
{
 public:
  typedef WFMath::CoordType coord_type;
  typedef WFMath::Point<3> point_type;

  static point_type make(coord_type x, coord_type y, coord_type z)
  {
    return point_type(x, y, z);
  }
};

}

}

#endif // DYMAXION_WFMATH_TRAITS_H
