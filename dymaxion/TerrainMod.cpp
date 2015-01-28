// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch, Damien McGinnes

#include <dymaxion/TerrainMod_impl.h>

#include <dymaxion/Segment.h>

#include <wfmath/point.h>
#include <wfmath/polygon.h>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/ring.hpp>

namespace dymaxion {

TerrainMod::TerrainMod() : m_function(set)
{
}

TerrainMod::~TerrainMod()
{
}

int TerrainMod::addToSegment(Segment & s) const
{
    if (!checkIntersects(s)) {
        return -1;
    }
    return s.addMod(this);
}

void TerrainMod::updateToSegment(Segment & s) const
{
    if (!checkIntersects(s)) {
        s.removeMod(this);
        return;
    }
    if (s.updateMod(this) != 0) {
        s.addMod(this);
    }
}

void TerrainMod::removeFromSegment(Segment & s) const
{
    s.removeMod(this);
}

using point = boost::geometry::model::d2::point_xy<
    float, boost::geometry::cs::cartesian>;
using ring = boost::geometry::model::ring<point>;

// template class ShapeTerrainMod<WFMath::Ball >;
template class ShapeTerrainMod<ring>;
// template class ShapeTerrainMod<WFMath::RotBox >;

// template class LevelTerrainMod<WFMath::Ball >;
template class LevelTerrainMod<ring>;
// template class LevelTerrainMod<WFMath::RotBox >;

// template class AdjustTerrainMod<WFMath::Ball >;
template class AdjustTerrainMod<ring>;
// template class AdjustTerrainMod<WFMath::RotBox >;

// template class SlopeTerrainMod<WFMath::Ball >;
template class SlopeTerrainMod<ring>;
// template class SlopeTerrainMod<WFMath::RotBox >;

// template class CraterTerrainMod<WFMath::Ball >;
template class CraterTerrainMod<ring>;
// template class CraterTerrainMod<WFMath::RotBox >;

} // namespace dymaxion
