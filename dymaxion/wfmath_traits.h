// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_WFMATH_TRAITS_H
#define DYMAXION_WFMATH_TRAITS_H

#include <dymaxion/traits.h>

#include <wfmath/axisbox.h>
#include <wfmath/point.h>
#include <wfmath/vector.h>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

namespace dymaxion
{

namespace traits
{

template <int dim>
class types<WFMath::AxisBox<dim>>
{
  public:
    typedef WFMath::CoordType coord_type;
    typedef WFMath::Point<dim> point_type;
};

template <int dim, int idx>
class axisbox_access<WFMath::AxisBox<dim>, idx>
{
 public:
  typedef typename types<WFMath::AxisBox<dim>>::coord_type coord_type;
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
inline types<WFMath::AxisBox<2>>::coord_type
axisbox_access<WFMath::AxisBox<2>, 0>::get_near(const WFMath::AxisBox<2> & b)
{
  return b.lowCorner().x();
}

template <>
inline types<WFMath::AxisBox<2>>::coord_type
axisbox_access<WFMath::AxisBox<2>, 0>::get_far(const WFMath::AxisBox<2> & b)
{
  return b.highCorner().x();
}

template <>
inline types<WFMath::AxisBox<2>>::coord_type
axisbox_access<WFMath::AxisBox<2>, 1>::get_near(const WFMath::AxisBox<2> & b)
{
  return b.lowCorner().y();
}

template <>
inline types<WFMath::AxisBox<2>>::coord_type
axisbox_access<WFMath::AxisBox<2>, 1>::get_far(const WFMath::AxisBox<2> & b)
{
  return b.highCorner().y();
}

template <>
inline void axisbox_access<WFMath::AxisBox<2>, 0>::set_near(
    WFMath::AxisBox<2> & b, types<WFMath::AxisBox<2>>::coord_type val)
{
  b.lowCorner().x() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<2>, 0>::set_far(
    WFMath::AxisBox<2> & b, types<WFMath::AxisBox<2>>::coord_type val)
{
  b.highCorner().x() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<2>, 1>::set_near(
    WFMath::AxisBox<2> & b, types<WFMath::AxisBox<2>>::coord_type val)
{
  b.lowCorner().y() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<2>, 1>::set_far(
    WFMath::AxisBox<2> & b, types<WFMath::AxisBox<2>>::coord_type val)
{
  b.highCorner().y() = val;
}

template <>
inline types<WFMath::AxisBox<3>>::coord_type
axisbox_access<WFMath::AxisBox<3>, 0>::get_near(const WFMath::AxisBox<3> & b)
{
  return b.lowCorner().x();
}

template <>
inline types<WFMath::AxisBox<3>>::coord_type
axisbox_access<WFMath::AxisBox<3>, 0>::get_far(const WFMath::AxisBox<3> & b)
{
  return b.highCorner().x();
}

template <>
inline types<WFMath::AxisBox<3>>::coord_type
axisbox_access<WFMath::AxisBox<3>, 1>::get_near(const WFMath::AxisBox<3> & b)
{
  return b.lowCorner().y();
}

template <>
inline types<WFMath::AxisBox<3>>::coord_type
axisbox_access<WFMath::AxisBox<3>, 1>::get_far(const WFMath::AxisBox<3> & b)
{
  return b.highCorner().y();
}

template <>
inline types<WFMath::AxisBox<3>>::coord_type
axisbox_access<WFMath::AxisBox<3>, 2>::get_near(const WFMath::AxisBox<3> & b)
{
  return b.lowCorner().z();
}

template <>
inline types<WFMath::AxisBox<3>>::coord_type
axisbox_access<WFMath::AxisBox<3>, 2>::get_far(const WFMath::AxisBox<3> & b)
{
  return b.highCorner().z();
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 0>::set_near(
    WFMath::AxisBox<3> & b, types<WFMath::AxisBox<3>>::coord_type val)
{
  b.lowCorner().x() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 0>::set_far(
    WFMath::AxisBox<3> & b, types<WFMath::AxisBox<3>>::coord_type val)
{
  b.highCorner().x() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 1>::set_near(
    WFMath::AxisBox<3> & b, types<WFMath::AxisBox<3>>::coord_type val)
{
  b.lowCorner().y() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 1>::set_far(
    WFMath::AxisBox<3> & b, types<WFMath::AxisBox<3>>::coord_type val)
{
  b.highCorner().y() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 2>::set_near(
    WFMath::AxisBox<3> & b, types<WFMath::AxisBox<3>>::coord_type val)
{
  b.lowCorner().z() = val;
}

template <>
inline void axisbox_access<WFMath::AxisBox<3>, 2>::set_far(
    WFMath::AxisBox<3> & b, types<WFMath::AxisBox<3>>::coord_type val)
{
  b.highCorner().z() = val;
}

template <template <int> class AxisBoxT, int dim>
class axisbox_construct<AxisBoxT<dim>>
{
 public:
  typedef WFMath::Point<dim> point_type;
  typedef typename types<point_type>::coord_type coord_type;
  typedef AxisBoxT<dim> axisbox_type;

  static axisbox_type make(const point_type & near, const point_type & far)
  {
    return axisbox_type(near, far);
  }
};

template <int dim>
class types<WFMath::Point<dim>>
{
 public:
  typedef WFMath::CoordType coord_type;
};

template <int dim>
class types<WFMath::Vector<dim>>
{
 public:
  typedef WFMath::CoordType coord_type;
};

template <template <int> class VectorT, int dim, int idx>
class point_access<VectorT<dim>, idx>
{
 public:
  typedef typename types<VectorT<dim>>::coord_type coord_type;
  typedef VectorT<dim> point_type;

  static coord_type get(const point_type & p)
  {
    static_assert((dim != 2) && (dim != 3),
        "Specializations for dim = 2,3 failing to work");
    static_assert(dim > idx,
        "Index of accessed coordinate must be smaller than dimensions");
    return p[idx];
  }

  static void set(point_type & p, coord_type v)
  {
    static_assert((dim != 2) && (dim != 3),
        "Specializations for dim = 2,3 failing to work");
    static_assert(dim > idx,
        "Index of accessed coordinate must be smaller than dimensions");
    p[idx] = v;
  }
};

template <>
inline types<WFMath::Point<2>>::coord_type
point_access<WFMath::Point<2>, 0>::get(const WFMath::Point<2> & p)
{
  return p.x();
}

template <>
inline types<WFMath::Point<2>>::coord_type
point_access<WFMath::Point<2>, 1>::get(const WFMath::Point<2> & p)
{
  return p.y();
}

template <>
inline void point_access<WFMath::Point<2>, 0>::set(
    WFMath::Point<2> & p, types<WFMath::Point<2>>::coord_type val)
{
  p.setValid(true);
  p.x() = val;
}

template <>
inline void point_access<WFMath::Point<2>, 1>::set(
    WFMath::Point<2> & p, types<WFMath::Point<2>>::coord_type val)
{
  p.y() = val;
}

template <>
inline types<WFMath::Point<3>>::coord_type
point_access<WFMath::Point<3>, 0>::get(const WFMath::Point<3> & p)
{
  return p.x();
}

template <>
inline types<WFMath::Point<3>>::coord_type
point_access<WFMath::Point<3>, 1>::get(const WFMath::Point<3> & p)
{
  return p.y();
}

template <>
inline types<WFMath::Point<3>>::coord_type
point_access<WFMath::Point<3>, 2>::get(const WFMath::Point<3> & p)
{
  return p.z();
}

template <>
inline void point_access<WFMath::Point<3>, 0>::set(
    WFMath::Point<3> & p, types<WFMath::Point<3>>::coord_type val)
{
  p.setValid(true);
  p.x() = val;
}

template <>
inline void point_access<WFMath::Point<3>, 1>::set(
    WFMath::Point<3> & p, types<WFMath::Point<3>>::coord_type val)
{
  p.y() = val;
}

template <>
inline void point_access<WFMath::Point<3>, 2>::set(
    WFMath::Point<3> & p, types<WFMath::Point<3>>::coord_type val)
{
  p.z() = val;
}

template <>
inline types<WFMath::Vector<2>>::coord_type
point_access<WFMath::Vector<2>, 0>::get(const WFMath::Vector<2> & p)
{
  return p.x();
}

template <>
inline types<WFMath::Vector<2>>::coord_type
point_access<WFMath::Vector<2>, 1>::get(const WFMath::Vector<2> & p)
{
  return p.y();
}

template <>
inline void point_access<WFMath::Vector<2>, 0>::set(
    WFMath::Vector<2> & p, types<WFMath::Vector<2>>::coord_type val)
{
  p.setValid(true);
  p.x() = val;
}

template <>
inline void point_access<WFMath::Vector<2>, 1>::set(
    WFMath::Vector<2> & p, types<WFMath::Vector<2>>::coord_type val)
{
  p.y() = val;
}

template <>
inline types<WFMath::Vector<3>>::coord_type
point_access<WFMath::Vector<3>, 0>::get(const WFMath::Vector<3> & p)
{
  return p.x();
}

template <>
inline types<WFMath::Vector<3>>::coord_type
point_access<WFMath::Vector<3>, 1>::get(const WFMath::Vector<3> & p)
{
  return p.y();
}

template <>
inline types<WFMath::Vector<3>>::coord_type
point_access<WFMath::Vector<3>, 2>::get(const WFMath::Vector<3> & p)
{
  return p.z();
}

template <>
inline void point_access<WFMath::Vector<3>, 0>::set(
    WFMath::Vector<3> & p, types<WFMath::Vector<3>>::coord_type val)
{
  p.setValid(true);
  p.x() = val;
}

template <>
inline void point_access<WFMath::Vector<3>, 1>::set(
    WFMath::Vector<3> & p, types<WFMath::Vector<3>>::coord_type val)
{
  p.y() = val;
}

template <>
inline void point_access<WFMath::Vector<3>, 2>::set(
    WFMath::Vector<3> & p, types<WFMath::Vector<3>>::coord_type val)
{
  p.z() = val;
}

template <template <int> class VectorT>
class point_construct<VectorT<2>>
{
 public:
  typedef typename types<VectorT<2>>::coord_type coord_type;
  typedef VectorT<2> point_type;

  static point_type make(coord_type x, coord_type y)
  {
    return point_type(x, y);
  }
};

template <template <int> class VectorT>
class point_construct<VectorT<3>>
{
 public:
  typedef typename types<VectorT<3>>::coord_type coord_type;
  typedef VectorT<3> point_type;

  static point_type make(coord_type x, coord_type y, coord_type z)
  {
    return point_type(x, y, z);
  }
};

template <int dim>
class types<WFMath::Polygon<dim>>
{
  public:
    typedef WFMath::CoordType coord_type;
    typedef WFMath::Point<dim> point_type;
};

}

}

namespace boost { namespace geometry {

namespace traits
{

template <int dim>
struct tag<WFMath::Point<dim>>
{
  typedef point_tag type;
};

template <int dim>
struct coordinate_type<WFMath::Point<dim>>
{
  typedef WFMath::CoordType type;
};

template <int dim>
struct coordinate_system<WFMath::Point<dim>>
{
  typedef cs::cartesian type;
};

template <int dim>
struct dimension<WFMath::Point<dim>>
    : boost::mpl::int_<dim>
{ };

template <int dim>
struct access<WFMath::Point<dim>, 0>
{
  static WFMath::CoordType get(WFMath::Point<dim> const & p)
  {
    return p.x();
  }

  static void set(WFMath::Point<dim> & p, WFMath::CoordType value)
  {
    p.x() = value;
  }
};

template <int dim>
struct access<WFMath::Point<dim>, 1>
{
  static WFMath::CoordType get(WFMath::Point<dim> const & p)
  {
    return p.y();
  }

  static void set(WFMath::Point<dim> & p, WFMath::CoordType value)
  {
    p.y() = value;
  }
};

template <int dim>
struct access<WFMath::Point<dim>, 2>
{
  static WFMath::CoordType get(WFMath::Point<dim> const & p)
  {
    return p.z();
  }

  static void set(WFMath::Point<dim> & p, WFMath::CoordType value)
  {
    p.z() = value;
  }
};

template <int dim>
struct tag<WFMath::Vector<dim>>
{
  typedef point_tag type;
};

template <int dim>
struct coordinate_type<WFMath::Vector<dim>>
{
  typedef WFMath::CoordType type;
};

template <int dim>
struct coordinate_system<WFMath::Vector<dim>>
{
  typedef cs::cartesian type;
};

template <int dim>
struct dimension<WFMath::Vector<dim>>
    : boost::mpl::int_<dim>
{ };

template <int dim>
struct access<WFMath::Vector<dim>, 0>
{
  static WFMath::CoordType get(WFMath::Vector<dim> const & p)
  {
    return p.x();
  }

  static void set(WFMath::Vector<dim> & p, WFMath::CoordType value)
  {
    p.x() = value;
  }
};

template <int dim>
struct access<WFMath::Vector<dim>, 1>
{
  static WFMath::CoordType get(WFMath::Vector<dim> const & p)
  {
    return p.y();
  }

  static void set(WFMath::Vector<dim> & p, WFMath::CoordType value)
  {
    p.y() = value;
  }
};

template <int dim>
struct access<WFMath::Vector<dim>, 2>
{
  static WFMath::CoordType get(WFMath::Vector<dim> const & p)
  {
    return p.z();
  }

  static void set(WFMath::Vector<dim> & p, WFMath::CoordType value)
  {
    p.z() = value;
  }
};

}

}}

#endif // DYMAXION_WFMATH_TRAITS_H
