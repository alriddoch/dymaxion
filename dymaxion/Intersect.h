// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Damien McGinnes

#ifndef DYMAXION_INTERSECT
#define DYMAXION_INTERSECT

#include <wfmath/axisbox.h>
#include <wfmath/point.h>
#include <dymaxion/Terrain.h>

namespace dymaxion {

bool Intersect(const Terrain &t, const WFMath::AxisBox<3> &bbox);
bool Intersect(const Terrain &t, const WFMath::Point<3> &pt);

bool Intersect(const Terrain &t, const WFMath::Point<3> &sPt, const std::tuple<float, float, float>& dir,
               WFMath::Point<3> &intersection, std::tuple<float, float, float> &normal, float &par);

} // namespace dymaxion

#endif
