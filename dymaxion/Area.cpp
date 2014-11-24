// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <dymaxion/Area.h>
#include <dymaxion/Clip.h>
#include <dymaxion/Segment.h>

#include <wfmath/intersect.h>
#include <iostream>
#include <cmath>

#include <cassert>

using WFMath::CoordType;

namespace dymaxion
{

typedef WFMath::Point<2> Point2;
typedef WFMath::Vector<2> Vector2;

// FIXME Why pass Clip by value?
template <class Clip>
WFMath::Polygon<2> sutherlandHodgmanKernel(const WFMath::Polygon<2>& inpoly, Clip clipper)
{
    WFMath::Polygon<2> outpoly;
    
    if (!inpoly.isValid()) return inpoly;
    auto points = inpoly.numCorners();
    if (points < 3) return outpoly; // i.e an invalid result
    
    auto lastPt = inpoly.getCorner(points - 1);
    bool lastInside = clipper.inside(lastPt);
    
    for (std::size_t p = 0; p < points; ++p) {
    
        auto curPt = inpoly.getCorner(p);
        bool inside = clipper.inside(curPt);
        
        if (lastInside) {
            if (inside) {
                // emit curPt
                outpoly.addCorner(outpoly.numCorners(), curPt);
            } else {
                // emit intersection of edge with clip line
                outpoly.addCorner(outpoly.numCorners(), clipper.clip(lastPt, curPt));
            }
        } else {
            if (inside) {
                // emit both
                outpoly.addCorner(outpoly.numCorners(), clipper.clip(lastPt, curPt));
                outpoly.addCorner(outpoly.numCorners(), curPt);
            } else {
                // don't emit anything
            }
        } // last was outside
        
        lastPt = curPt;
        lastInside = inside;
    }
    
    return outpoly;
}

Area::Area(int layer, bool hole) :
    m_layer(layer),
    m_hole(hole)
{
}

void Area::setShape(const WFMath::Polygon<2>& p)
{
    assert(p.isValid());
    m_shape = p;
    m_box = p.boundingBox();
}

void Area::setShader(const Shader * shader) const
{
    m_shader = shader;
}

bool Area::contains(CoordType x, CoordType y) const
{
    if (!WFMath::Contains(m_box, Point2(x,y), false)) return false;
    
    return WFMath::Contains(m_shape, Point2(x,y), false);
}

int Area::addToSegment(Segment & s) const
{
    if (!checkIntersects(s)) {
        return -1;
    }
    return s.addArea(this);
}

void Area::updateToSegment(Segment & s) const
{
    if (!checkIntersects(s)) {
        s.removeArea(this);
        return;
    }
    if (s.updateArea(this) != 0) {
        s.addArea(this);
    }
}

void Area::removeFromSegment(Segment & s) const
{
    if (checkIntersects(s)) {
        s.removeArea(this);
    }
}

WFMath::Polygon<2> Area::clipToSegment(const Segment& s) const
{
    // box reject
    if (!checkIntersects(s)) return WFMath::Polygon<2>();
    
    auto segBox = s.getRect();
    auto clipped = sutherlandHodgmanKernel(m_shape, TopClip(segBox.lowCorner().y()));
    
    clipped = sutherlandHodgmanKernel(clipped, BottomClip(segBox.highCorner().y()));
    clipped = sutherlandHodgmanKernel(clipped, LeftClip(segBox.lowCorner().x()));
    clipped = sutherlandHodgmanKernel(clipped, RightClip(segBox.highCorner().x()));
    
    return clipped;
}

bool Area::checkIntersects(const Segment& s) const
{
    return WFMath::Intersect(m_shape, s.getRect(), false) ||
        WFMath::Contains(s.getRect(), m_shape.getCorner(0), false);
}

} // of namespace
