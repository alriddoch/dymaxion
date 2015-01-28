// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Damien McGinnes, Alistair Riddoch

#ifndef DYMAXION_TERRAIN_MOD_IMPL_H
#define DYMAXION_TERRAIN_MOD_IMPL_H

#include <dymaxion/TerrainMod.h>

#include <dymaxion/Segment.h>

#include <wfmath/point.h>

#include <boost/geometry/algorithms/centroid.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace dymaxion {

template <class Shape>
ShapeTerrainMod<Shape>::ShapeTerrainMod(const Shape &s) : m_shape(s)
{
    boost::geometry::envelope(m_shape, m_box);
}


template <class Shape> ShapeTerrainMod<Shape>::~ShapeTerrainMod()
{
}

template <class Shape>
bool ShapeTerrainMod<Shape>::checkIntersects(const Segment& s) const
{
  // FIXME: This can go once s.getRect() returns a boost box
  auto segBox = s.getRect();
  boost::geometry::model::box<point_type> seg_box(
      point_type(segBox.lowCorner().x(), segBox.lowCorner().y()),
      point_type(segBox.highCorner().x(), segBox.highCorner().y())
  );

  point_type const & c = m_shape[0];
  return boost::geometry::intersects(m_shape, seg_box) ||
      boost::geometry::within(c, seg_box);
}
    
template <class Shape>
void ShapeTerrainMod<Shape>::setShape(const Shape & s)
{
  m_shape = s;
  boost::geometry::envelope(m_shape, m_box);
}

template <class Shape> LevelTerrainMod<Shape>::~LevelTerrainMod()
{
}
    
template <class Shape>
void LevelTerrainMod<Shape>::apply(float &point, int x, int y) const
{
  if (boost::geometry::within(point_type(x, y), this->m_shape)) {
    point = this->m_function(point, m_level);
  }
}

template <class Shape>
void LevelTerrainMod<Shape>::setShape(float level, const Shape & s)
{
    ShapeTerrainMod<Shape>::setShape(s);
    m_level = level;
}

template <class Shape> AdjustTerrainMod<Shape>::~AdjustTerrainMod()
{
}
    
template <class Shape>
void AdjustTerrainMod<Shape>::apply(float &point, int x, int y) const
{
  if (boost::geometry::within(point_type(x, y), this->m_shape)) {
    point += m_dist;
  }
}
    
template <class Shape>
void AdjustTerrainMod<Shape>::setShape(float dist, const Shape & s)
{
    ShapeTerrainMod<Shape>::setShape(s);
    m_dist = dist;
}

template <class Shape> SlopeTerrainMod<Shape>::~SlopeTerrainMod()
{
}
    
template <class Shape>
void SlopeTerrainMod<Shape>::apply(float &point, int x, int y) const
{
    if (boost::geometry::within(point_type(x, y), this->m_shape)) {
        // FIXME The centroid is possibly non-trivial to compute
        // so should be computed when the shape is set.
        // FIXME Why does g++ think that centroid may be used uninitialised?
        point_type centroid;
        boost::geometry::centroid(this->m_shape, centroid);
        float level = m_level + (centroid.x() - x) * m_dx 
                              + (centroid.y() - y) * m_dy;
        point = this->m_function(point, level);
    }
}
    
template <class Shape>
void SlopeTerrainMod<Shape>::setShape(float level,
                                      float dx, float dy,
                                      const Shape & s)
{
    ShapeTerrainMod<Shape>::setShape(s);
    m_level = level;
    m_dx = dx;
    m_dy = dy;
}


template <class Shape> CraterTerrainMod<Shape>::~CraterTerrainMod()
{
}
    
template <class Shape>
void CraterTerrainMod<Shape>::apply(float &point, int x, int y) const
{
    if (boost::geometry::within(point_type(x, y), this->m_shape)) {
        point += m_level;
    }
}
    
template <class Shape>
void CraterTerrainMod<Shape>::setShape(float level, const Shape & s)
{
    ShapeTerrainMod<Shape>::setShape(s);
    m_level = level;
}


} //namespace dymaxion

#endif // DYMAXION_TERRAIN_MOD_IMPL_H
