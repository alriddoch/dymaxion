// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2010 Alistair Riddoch

#include <dymaxion/Terrain.h>

#include <dymaxion/Area.h>
#include <dymaxion/Segment.h>
#include <dymaxion/Shader.h>
#include <dymaxion/Surface.h>

#include <wfmath/point.h>

#include <cassert>

// This is a relatively specific tests which ensures Terrain::addArea
// behaves as defined with respect to invalidating surfaces, to verify
// a refactoring. Previous cases where std::map::count() was used followed
// by [] are inefficient, and I wanted to verify consistent bahviour before
// checking to use std::map::find()

class TestShader : public dymaxion::Shader {
 public:
  virtual bool checkIntersect(dymaxion::Segment const &) const
  {
    return true;
  }

  /// \brief Populate a Surface with data.
  virtual void shade(dymaxion::Surface &) const
  {
  }

};

int main()
{
  dymaxion::Terrain t;

  // Add a null test shader to the terrain
  dymaxion::Shader * shader = new TestShader;
  t.addShader(shader, 0);

  // Create a test area with a shape which intersects
  // the Segment at 0,0
  dymaxion::Area* a1 = new dymaxion::Area(0, false);

  dymaxion::Area::ring p;
  p.push_back(dymaxion::Area::point(3, 4));
  p.push_back(dymaxion::Area::point(3, 10));
  p.push_back(dymaxion::Area::point(14, 12));
  p.push_back(dymaxion::Area::point(18, 4));
  p.push_back(dymaxion::Area::point(17, 2));
  p.push_back(dymaxion::Area::point(6, -2));
  p.push_back(dymaxion::Area::point(3, 4));

  a1->setShape(p);

  // Add enough base points to force the creation of the Segment at 0,0
  t.setBasePoint(0, 0, -1);
  t.setBasePoint(0, 1, 8);
  t.setBasePoint(1, 0, 2);
  t.setBasePoint(1, 1, 11);

  // Get the Segment at 0,0
  dymaxion::Segment * seg = t.getSegment(0, 0);

  assert(seg != 0);

  // Get the surfaces, and add one corresponding to the shader we added.
  // We need to do this as the functions that would normally make it happen
  // have been stubbed out.
  dymaxion::Segment::Surfacestore & sss = seg->getSurfaces();

  dymaxion::Surface * sfce = new dymaxion::Surface(*seg, *shader);

  // Force allocation of the surface buffer so we can check later that it
  // gets destroyed when the area is added to the terrain.
  sfce->allocate();
  assert(sfce->isValid());

  // Add the surface to the store for this segment
  sss[0] = sfce;

  // Add the area which should cause relevant surface date to be invalidated
  t.addArea(a1);

  // We assert this to ensure that the buffer has been de-allocated
  // by a call to Surface::invalidate caused by adding the Area.
  assert(!sfce->isValid());

  // force the surface to re-allocate
  sfce->allocate();
  assert(sfce->isValid());

  // Modify the areas shape
  p[5] = dymaxion::Area::point(-9, -2);
  a1->setShape(p);

  // and cause an area update
  t.updateArea(a1);

  // Check the surface has been invalidated again
  assert(!sfce->isValid());

  // force the surface to re-allocate
  sfce->allocate();
  assert(sfce->isValid());

  t.removeArea(a1);

  // Check the surface has been invalidated again
  assert(!sfce->isValid());
}

// stubs

#include <dymaxion/Area.h>
#include <dymaxion/Buffer_impl.h>
#include <dymaxion/Shader.h>
#include <dymaxion/TerrainMod.h>

namespace dymaxion {

Shader::Shader(bool color, bool alpha) : m_color(color), m_alpha(alpha)
{
}

Shader::~Shader()
{
}

Surface * Shader::newSurface(Segment const &) const
{
  return 0;
}

Surface::Surface(Segment const & seg, Shader const & sh, bool color, bool alpha)
  : Buffer<ColorT>(seg, (color ? 3 : 0) + (alpha ? 1 : 0)), m_shader(sh)
{
}

Surface::~Surface()
{
}

void Surface::populate()
{
}

int TerrainMod::addToSegment(Segment & s) const
{
  return -1;
}

void TerrainMod::removeFromSegment(Segment & s) const
{
}

constexpr float BasePoint::HEIGHT;
constexpr float BasePoint::ROUGHNESS;
constexpr float BasePoint::FALLOFF;

Effector::Effector()
{
}

Effector::~Effector()
{
}

}
