// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_TRAITS_H
#define DYMAXION_TRAITS_H

namespace dymaxion
{

namespace traits
{

template <class Geometry>
class types;

template <class AxixBox, int idx>
class axisbox_access;

template <class AxisBox>
class axisbox_construct;

template <class Point, int idx>
class point_access;

template <class Point>
class point_construct;

template <class Vector, class PointL, class PointR, unsigned dim>
class point_subtract;

template <class Vector, class PointL, class PointR>
class point_subtract<Vector, PointL, PointR, 2>
{
 public:
  static Vector op(PointL const & pl, PointR const & pr)
  {
    return point_construct<Vector>::make(
             point_access<PointL, 0>::get(pl) - point_access<PointR, 0>::get(pr),
             point_access<PointL, 1>::get(pl) - point_access<PointR, 1>::get(pr)
             );
  }

};

template <class Vector, class PointL, class PointR>
class point_subtract<Vector, PointL, PointR, 3>
{
 public:
  static Vector op(PointL const & pl, PointR const & pr)
  {
    return point_construct<Vector>::make(
             point_access<PointL, 0>::get(pl) - point_access<PointR, 0>::get(pr),
             point_access<PointL, 1>::get(pl) - point_access<PointR, 1>::get(pr),
             point_access<PointL, 2>::get(pl) - point_access<PointR, 2>::get(pr)
             );
  }

};

template <class Point, class PointL, class VectorR, unsigned dim>
class point_add;

template <class Point, class PointL, class VectorR>
class point_add<Point, PointL, VectorR, 2>
{
 public:
  static Point op(PointL const & pl, VectorR const & pr)
  {
    return point_construct<Point>::make(
             point_access<PointL, 0>::get(pl) + point_access<VectorR, 0>::get(pr),
             point_access<PointL, 1>::get(pl) + point_access<VectorR, 1>::get(pr)
             );
  }

};

template <class Point, class PointL, class VectorR>
class point_add<Point, PointL, VectorR, 3>
{
 public:
  static Point op(PointL const & pl, VectorR const & pr)
  {
    return point_construct<Point>::make(
             point_access<PointL, 0>::get(pl) + point_access<VectorR, 0>::get(pr),
             point_access<PointL, 1>::get(pl) + point_access<VectorR, 1>::get(pr),
             point_access<PointL, 2>::get(pl) + point_access<VectorR, 2>::get(pr)
             );
  }

};

}

}

#endif // DYMAXION_TRAITS_H
