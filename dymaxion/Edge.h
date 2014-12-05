// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_EDGE_H
#define DYMAXION_EDGE_H

#include <dymaxion/traits.h>

#include <wfmath/vector.h>

#include <tuple>

#include <cassert>

class Edgetest;
class EdgeAtYtest;

namespace dymaxion
{

typedef std::tuple<float, float> Point2;
typedef WFMath::Vector<2> Vector2;

/// \brief The edge of an area.
template <class Point = Point2>
class Edge
{
    typedef typename traits::types<Point>::coord_type coord_type;
public: 
    /// \brief Constructor
    ///
    /// @param a one end of the line defining the edge.
    /// @param b one end of the line defining the edge.
    Edge(const Point & a, const Point & b)
    {
        // horizontal segments should be discarded earlier
        assert((traits::point_access<Point, 1>::get(a)) !=
               (traits::point_access<Point, 1>::get(b)));
        
        if (traits::point_access<Point, 1>::get(a) <
            traits::point_access<Point, 1>::get(b)) {
            m_start = a;
            m_seg = traits::point_subtract<decltype(m_seg),
                                           Point,
                                           Point,
                                           2>::op(b, a);
        } else {
            m_start = b;
            m_seg = traits::point_subtract<decltype(m_seg),
                                           Point,
                                           Point,
                                           2>::op(a, b);
        }
        
        // normal gradient is y/x, here we use x/y. seg.y() will be != 0,
        // as we already asserted above.
        m_inverseGradient = m_seg.x() / m_seg.y();
    }
    
    /// Accessor for the point describing the start of the edge.
    Point start() const { return m_start; }
    /// Determine the point describing the end of the edge.
    Point end() const { return traits::point_add<Point,
                                                 Point,
                                                 decltype(m_seg),
                                                 2>::op(m_start, m_seg); }
    
    /// \brief Determine the x coordinate at a given y coordinate.
    ///
    /// Calculate the x coordinate on the edge line where the y coordinate
    /// is the value specified.
    /// @param y the y coordinate where the calculation is required.
    coord_type xValueAtY(coord_type y) const
    {
        coord_type x =
            traits::point_access<decltype(m_start), 0>::get(m_start) +
            ((y - traits::point_access<decltype(m_start), 1>::get(m_start)) *
             m_inverseGradient);
     //   std::cout << "edge (" << m_start << ", " << m_start + m_seg << ") at y=" << y << " has x=" << x << std::endl; 
        return x;
    }
    
    /// \brief Compare the y coordinate of the start with another edge.
    ///
    /// This operator ensures that edges can be sorted, compares the y
    /// y coordinate of the start of the edges.
    bool operator<(const Edge& other) const
    {
        return traits::point_access<decltype(m_start), 1>::get(m_start) <
               traits::point_access<decltype(m_start), 1>::get(other.m_start);
    }

    friend class ::Edgetest;
private:

    /// The point describing the start of the edge.
    Point m_start;
    /// The vector describing the edge from its start.
    Vector2 m_seg;
    /// The inverse of the gradient of the line.
    coord_type m_inverseGradient;
};

/// \brief The edge of an area parallel to the x axis.
template <class Point = Point2>
class EdgeAtY
{
    typedef typename traits::types<Point>::coord_type coord_type;
public:
    /// Constructor
    ///
    /// @param y coordinate on the y axis of the edge.
    EdgeAtY(coord_type y) : m_y(y) {}
    
    /// Determine which edge crosses this edge at a lower x coordinate.
    bool operator()(const Edge<Point>& u, const Edge<Point>& v) const
    {
        return u.xValueAtY(m_y) < v.xValueAtY(m_y);
    }

    friend class ::EdgeAtYtest;
private:

    /// The coordinate on the y axis of the edge.
    coord_type m_y;
};

} // of namespace

#endif // DYMAXION_EDGE_H
