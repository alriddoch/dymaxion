// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_AREA_H
#define DYMAXION_AREA_H

#include <dymaxion/Effector.h>

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/ring.hpp>

namespace dymaxion
{

class Segment;
class Shader;

/// \brief Region of terrain surface which is modified.
///
/// Objects of this class describe regions of the surface which have
/// been changed. Which layers of the shaded terrain is affected by
/// their layer number. For example, if they are below the snow layer
/// then the snow shader will cover them where the area affected by
/// snow intersects with the area, but the lower grass area will be
/// overriden. In order to get the best effect it is important to
/// select the layer carefully.
class Area : public Effector
{
public:
    friend class Areatest;

    typedef boost::geometry::model::d2::point_xy<
        float, boost::geometry::cs::cartesian> point;
    typedef boost::geometry::model::ring<point> ring;

    /// \brief Constructor
    ///
    /// @param layer layer number.
    /// @param hole flag indicating whether this is a hole.
    Area(int layer, bool hole);
    
    /// \brief Set the layer number and flag indicating whether this is a hole.
    ///
    /// @param layer layer number.
    /// @param hole flag indicating whether this is a hole.
    void setLayer(int layer, bool hole);

    /// Set the geometric shape of this area.
    void setShape(ring const & p);

    void setShader(Shader const * shader) const;

    /// Determine if a point is contained by the shape of this area.
    template <typename FloatType>
    bool contains(FloatType x, FloatType y) const;

    /// Accessor for the layer number.
    int getLayer() const
    {
        return m_layer;
    }
    
    /// Accessor for the flag indicating whether this is a hole.
    bool isHole() const
    {
        return m_hole;
    }
    
    /// Accessor for the geometric shape.
    const ring & shape() const
    {
        return m_shape;
    }

    const Shader * getShader() const
    {
        return m_shader;
    }

    int addToSegment(Segment &) const;
    void updateToSegment(Segment &) const;
    void removeFromSegment(Segment &) const;
    
    /**
    Test if a segment intersects this area
    */
    bool checkIntersects(Segment const & s) const;

    /// \brief Clip the shape of this area to a given segment.
    ///
    /// Determines the intersection of the geometric shape of this area
    /// with a square terrain segment, and returns the intersection as
    /// a geometric shape.
    /// @param s the segment that the shape should be clipped to.
    /// @returns the shape of the intersection of this area with the segment.
    ring clipToSegment(Segment const & s) const;
private:
    /// The layer number.
    int m_layer;
    /// A flag indicating whether this is a hole.
    bool m_hole;
    /// The geometric shape.
    ring m_shape;
    /// Shader that shades this area
    mutable const Shader * m_shader = 0;
};

}

#endif // of DYMAXION_AREA_H
