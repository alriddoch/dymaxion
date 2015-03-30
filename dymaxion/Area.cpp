// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <dymaxion/Area.h>
#include <dymaxion/Clip.h>
#include <dymaxion/Segment.h>

#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/strategies/strategies.hpp>

#include <iostream>
#include <cmath>

#include <cassert>

namespace dymaxion
{

Area::Area(int layer, bool hole) :
  m_layer(layer),
  m_hole(hole)
{
}

void Area::setShape(ring const & p)
{
  assert(!p.empty());
  m_shape = p;
  boost::geometry::envelope(m_shape, m_box);
}

void Area::setShader(const Shader * shader) const
{
  m_shader = shader;
}

template <typename FloatType>
bool Area::contains(FloatType x, FloatType y) const
{
  if (!boost::geometry::within(point(x, y), m_box))
  {
    return false;
  }

  return boost::geometry::within(point(x, y), m_shape);
}

template
bool Area::contains<float>(float x, float y) const;

int Area::addToSegment(Segment & s) const
{
  if (!checkIntersects(s))
  {
    return -1;
  }
  return s.addArea(this);
}

void Area::updateToSegment(Segment & s) const
{
  if (!checkIntersects(s))
  {
    s.removeArea(this);
    return;
  }
  if (s.updateArea(this) != 0)
  {
    s.addArea(this);
  }
}

void Area::removeFromSegment(Segment & s) const
{
  // We can't do a check here, because the shape of this area has probably
  // been modified (which is why it's being removed), so checkIntersects()
  // tells us nothing about whether this Area used to intersect with
  // a given Segment. Instead we just call removeArea(), which has no effect
  // if this Area never intersected it.
  s.removeArea(this);
}

Area::ring Area::clipToSegment(Segment const & s) const
{
  // box reject
  if (!checkIntersects(s))
  {
    return Area::ring();
  }

  boost::geometry::model::box<point> seg_box = s.getRect();

  std::vector<ring> clipped;
  boost::geometry::intersection(m_shape, seg_box, clipped);

  assert(clipped.size() > 0);
  return clipped[0];
}

bool Area::checkIntersects(Segment const & s) const
{
  boost::geometry::model::box<point> seg_box = s.getRect();

  Area::point const & c = m_shape[0];
  return boost::geometry::intersects(m_shape, seg_box) ||
         boost::geometry::within(c, seg_box);
}

} // of namespace
