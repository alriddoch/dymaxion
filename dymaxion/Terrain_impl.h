// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2015 Alistair Riddoch

#ifndef DYMAXION_TERRAIN_IMPL_H
#define DYMAXION_TERRAIN_IMPL_H

#include <dymaxion/Terrain.h>

#include <boost/geometry/core/access.hpp>

namespace dymaxion {

template <typename Vector>
bool Terrain::getHeightAndNormalAny(float x, float y, float & height,
                                    Vector & normal) const
{
  std::tuple<float, float, float> inner_normal;
  bool res = getHeightAndNormal(x, y, height, inner_normal);

  if (res) {
    std::get<0>(inner_normal) =
        boost::geometry::traits::access<Vector, 0>::get(normal);
    std::get<1>(inner_normal) =
        boost::geometry::traits::access<Vector, 1>::get(normal);
    std::get<2>(inner_normal) =
        boost::geometry::traits::access<Vector, 1>::get(normal);
  }
  return res;
}

} // namespace dymaxion

#endif // DYMAXION_TERRAIN_IMPL_H
