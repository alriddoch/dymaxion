// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2015 Alistair Riddoch, Damien McGinnes

#ifndef DYMAXION_SEGMENT_IMPL_H
#define DYMAXION_SEGMENT_IMPL_H

#include <dymaxion/Segment.h>

#include <boost/geometry/core/access.hpp>

namespace dymaxion {

template <typename Vector>
void Segment::getHeightAndNormalAny(float x, float y, float & n,
                                    Vector & normal) const
{
  std::tuple<float, float, float> inner_normal;
  getHeightAndNormal(x, y, n, inner_normal);

  std::get<0>(inner_normal) =
    boost::geometry::traits::access<Vector, 0>::get(normal);
  std::get<1>(inner_normal) =
    boost::geometry::traits::access<Vector, 1>::get(normal);
  std::get<2>(inner_normal) =
    boost::geometry::traits::access<Vector, 1>::get(normal);
}

} // namespace dymaxion

#endif // DYMAXION_SEGMENT_IMPL_H
