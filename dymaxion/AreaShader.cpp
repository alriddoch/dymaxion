// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#include <dymaxion/AreaShader.h>
#include <dymaxion/Area.h>
#include <dymaxion/Edge.h>
#include <dymaxion/Segment.h>
#include <dymaxion/Surface.h>
#include <dymaxion/tuple_traits.h>
#include <dymaxion/wfmath_traits.h>

#include <list>
#include <set>
#include <iostream>
#include <algorithm>
#include <tuple>

#include <cmath>

#include <cassert>

namespace dymaxion
{

using traits::point_access;

const WFMath::CoordType ROW_HEIGHT = 1 / 4.0f; // 4x over-sample

static void contribute(Surface& s,
                       unsigned int x, unsigned int y,
                       WFMath::CoordType amount)
{    
    unsigned int sz = s.getSize() - 1;
    if ((x == 0) || (x == sz))
        amount *= 2;
        
    if ((y == 0) || (y == sz))
        amount *= 2;
        
    s(x, y, 0) = std::min(std::lrint(amount * 255) + s(x,y,0), 255l);
}

static void span(Surface& s,
                 WFMath::CoordType y,
                 WFMath::CoordType xStart,
                 WFMath::CoordType xEnd)
{
    assert(xStart <= xEnd); 

    // quantize and accumulate into the buffer data
    unsigned int row = std::lrint(y),
        ixStart = std::lrint(xStart),
        ixEnd = std::lrint(xEnd);
 
    //std::cout << "span @ y=" << row << ", " << ixStart << " -> " << ixEnd << std::endl;
    
    if (ixStart == ixEnd) {
        contribute(s, ixStart, row, ROW_HEIGHT * (xEnd - xStart));
    } else {
        contribute(s, ixStart, row, ROW_HEIGHT * (ixStart - xStart + 0.5f));
        
        for (unsigned int i=ixStart+1; i < ixEnd; ++i)
            contribute(s, i, row, ROW_HEIGHT);
        
        contribute(s, ixEnd, row, ROW_HEIGHT * (xEnd - ixEnd + 0.5f));
    }
}

template <class Polygon>
static void scanConvert(const Polygon & inPoly, Surface& sf)
{
    typedef typename traits::types<Polygon>::point_type Point;

    if (!inPoly.isValid()) return;
    
    // TODO templatize Edge, so it will work with whatever we have here
    std::list<Edge<Point>> pending;
    std::vector<Edge<Point>> active;

    auto lastPt = inPoly.getCorner(inPoly.numCorners() - 1);
    for (std::size_t p=0; p < inPoly.numCorners(); ++p) {
        auto curPt = inPoly.getCorner(p);
        
        // skip horizontal edges
        if (curPt.y() != lastPt.y())
            pending.push_back(
                Edge<Point>(Point(point_access<Point, 0>::get(lastPt),
                                  point_access<Point, 1>::get(lastPt)),
                            Point(point_access<Point, 0>::get(curPt),
                                  point_access<Point, 1>::get(curPt)))
            );
        
        lastPt = curPt;
    }
    
    if (pending.empty()) return;
    
    // sort edges by starting (lowest) y value
    pending.sort();
    active.push_back(pending.front());
    pending.pop_front();
    
    // advance to the row of the first y value, and ensure y sits in the
    // middle of sample rows - we do this by offseting by 1/2 a row height
    // if you don't do this, you'll find alternating rows are over/under
    // sampled, producing a charming striped effect.
    typename traits::types<Point>::coord_type y = std::floor(active.front().start().y()) + ROW_HEIGHT * 0.5f;
    
    for (; !pending.empty() || !active.empty();  y += ROW_HEIGHT)
    {
        while (!pending.empty() && (pending.front().start().y() <= y)) {
            active.push_back(pending.front());
            pending.pop_front();
        }
        
        // sort by x value - note active will be close to sorted anyway
        std::sort(active.begin(), active.end(), EdgeAtY<Point>(y));
        
        // delete finished edges
        for (decltype(active.size()) i = 0; i < active.size(); ) {
            if (active[i].end().y() <= y)
                active.erase(active.begin() + i);
            else
                ++i;
        }
        
        // draw pairs of active edges
        for (unsigned int i=1; i < active.size(); i += 2)
            span(sf, y, active[i-1].xValueAtY(y), active[i].xValueAtY(y));
    } // of active edges loop
}

AreaShader::AreaShader(int layer) :
    Shader(false /* no color */, true),
    m_layer(layer)
{

}

bool AreaShader::checkIntersect(const Segment& s) const
{
    auto const & areas(s.getAreas());
    return (areas.count(m_layer) > 0);
}

void AreaShader::shade(Surface &s) const
{
    auto * data = s.getData();
    auto size = s.getSegment().getSize();

    decltype(size) buflen = size * size;
    for (decltype(buflen) i = 0; i < buflen; ++i) data[i] = 0;

    auto const & areas(s.getSegment().getAreas());
    Segment::Areastore::const_iterator it = areas.lower_bound(m_layer);
    Segment::Areastore::const_iterator itend = areas.upper_bound(m_layer);
    
    for (;it != itend; ++it) {
        // apply to surface in turn
        if (it->second->isHole()) {
            // shadeHole
        } else
            shadeArea(s, it->second);
    } // of areas in layer
}

void AreaShader::shadeArea(Surface& s, const Area* const ar) const
{
    auto clipped = ar->clipToSegment(s.getSegment());
    assert(clipped.isValid());
    
    if (clipped.numCorners() == 0) return;
 
    auto segOrigin = s.getSegment().getRect().lowCorner();
    clipped.shift(traits::point_subtract<WFMath::Vector<2>,
                                         Point2,
                                         decltype(segOrigin),
                                         2>::op(Point2(0,0), segOrigin));
    scanConvert(clipped, s);
}

} // of namespace
