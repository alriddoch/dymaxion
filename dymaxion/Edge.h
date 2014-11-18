// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_EDGE_H
#define DYMAXION_EDGE_H

#include <wfmath/point.h>
#include <wfmath/vector.h>

#include <list>
#include <set>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <cassert>

class Edgetest;
class EdgeAtYtest;

namespace dymaxion
{

typedef WFMath::Point<2> Point2;
typedef WFMath::Vector<2> Vector2;

/// \brief The edge of an area.
class Edge
{
public: 
    /// \brief Constructor
    ///
    /// @param a one end of the line defining the edge.
    /// @param b one end of the line defining the edge.
    Edge(const Point2& a, const Point2& b)
    {
        // horizontal segments should be discarded earlier
        assert(a.y() != b.y());
        
        if (a.y() < b.y()) {
            m_start = a;
            m_seg = b - a;
        } else {
            m_start = b;
            m_seg = a - b;
        }
        
        // normal gradient is y/x, here we use x/y. seg.y() will be != 0,
        // as we already asserted above.
        m_inverseGradient = m_seg.x() / m_seg.y();
    }
    
    /// Accessor for the point describing the start of the edge.
    Point2 start() const { return m_start; }
    /// Determine the point describing the end of the edge.
    Point2 end() const { return m_start + m_seg; }
    
    /// \brief Determine the x coordinate at a given y coordinate.
    ///
    /// Calculate the x coordinate on the edge line where the y coordinate
    /// is the value specified.
    /// @param y the y coordinate where the calculation is required.
    WFMath::CoordType xValueAtY(WFMath::CoordType y) const
    {
        WFMath::CoordType x = m_start.x() + ((y - m_start.y()) * m_inverseGradient);
     //   std::cout << "edge (" << m_start << ", " << m_start + m_seg << ") at y=" << y << " has x=" << x << std::endl; 
        return x;
    }
    
    /// \brief Compare the y coordinate of the start with another edge.
    ///
    /// This operator ensures that edges can be sorted, compares the y
    /// y coordinate of the start of the edges.
    bool operator<(const Edge& other) const
    {
        return m_start.y() < other.m_start.y();
    }

    friend class ::Edgetest;
protected:
    /// The point describing the start of the edge.
    Point2 m_start;
    /// The vector describing the edge from its start.
    Vector2 m_seg;
    /// The inverse of the gradient of the line.
    WFMath::CoordType m_inverseGradient;
};

/// \brief The edge of an area parallel to the x axis.
class EdgeAtY
{
public:
    /// Constructor
    ///
    /// @param y coordinate on the y axis of the edge.
    EdgeAtY(WFMath::CoordType y) : m_y(y) {}
    
    /// Determine which edge crosses this edge at a lower x coordinate.
    bool operator()(const Edge& u, const Edge& v) const
    {
        return u.xValueAtY(m_y) < v.xValueAtY(m_y);
    }

    friend class ::EdgeAtYtest;
private:
    /// The coordinate on the y axis of the edge.
    WFMath::CoordType m_y;
};

} // of namespace

#endif // DYMAXION_EDGE_H
