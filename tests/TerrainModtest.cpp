// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#include <dymaxion/Terrain.h>
#include <dymaxion/Segment.h>
#include <dymaxion/TerrainMod.h>

#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/ring.hpp>

#include <iostream>

#include <cassert>

using boost_point = boost::geometry::model::d2::point_xy<
  float,
  boost::geometry::cs::cartesian
>;
using boost_ring = boost::geometry::model::ring<boost_point>;

bool operator==(dymaxion::Effector::box const & lhs,
                dymaxion::Effector::box const & rhs)
{
  return boost::geometry::equals(lhs, rhs);
}

int terrain_mod_context_test(dymaxion::Terrain & terrain)
{
  boost_ring mod_shape;
  mod_shape.push_back(boost_point(0.f, 0.f));
  mod_shape.push_back(boost_point(0.f, 1.f));
  mod_shape.push_back(boost_point(1.f, 1.f));
  mod_shape.push_back(boost_point(1.f, 0.f));
  mod_shape.push_back(boost_point(0.f, 0.f));

  dymaxion::TerrainMod * mp = new dymaxion::LevelTerrainMod<boost_ring>(10.0f, mod_shape);
  terrain.addMod(mp);

  mp->setContext(new dymaxion::TerrainMod::Context);
  mp->context()->setId("foo");

  terrain.removeMod(mp);

  delete mp;

  return 0;
}

int main()
{
  dymaxion::Terrain terrain(dymaxion::Terrain::SHADED);

  terrain.setBasePoint(0, 0, 2.8);
  terrain.setBasePoint(1, 0, 7.1);
  terrain.setBasePoint(2, 0, 7.1);
  terrain.setBasePoint(0, 1, 0.2);
  terrain.setBasePoint(1, 1, 0.2);
  terrain.setBasePoint(2, 1, 0.2);
  terrain.setBasePoint(0, 2, 14.7);
  terrain.setBasePoint(1, 2, 14.7);
  terrain.setBasePoint(2, 2, 14.7);

  boost_ring mod_shape;
  mod_shape.push_back(boost_point(0.f, 0.f));
  mod_shape.push_back(boost_point(0.f, 5.f));
  mod_shape.push_back(boost_point(5.f, 5.f));
  mod_shape.push_back(boost_point(5.f, 0.f));
  mod_shape.push_back(boost_point(0.f, 0.f));

  dymaxion::TerrainMod * mp1 = new dymaxion::LevelTerrainMod<boost_ring>(10.0f, mod_shape);
  terrain.addMod(mp1);

  boost_ring crater_shape;
  crater_shape.push_back(boost_point(80.f, 80.f));
  crater_shape.push_back(boost_point(80.f, 85.f));
  crater_shape.push_back(boost_point(85.f, 85.f));
  crater_shape.push_back(boost_point(85.f, 80.f));
  crater_shape.push_back(boost_point(80.f, 80.f));

  dymaxion::CraterTerrainMod<boost_ring> * mp3 =
      new dymaxion::CraterTerrainMod<boost_ring>(-5.f, crater_shape);
  terrain.addMod(mp3);

  dymaxion::Segment * segment = terrain.getSegment(0, 0);

  if (segment == 0) {
    std::cerr << "Segment not created by addition of required basepoints"
              << std::endl << std::flush;
    return 1;
  }

  segment->populate();

  segment = terrain.getSegment(1, 1);

  if (segment == 0) {
    std::cerr << "Segment not created by addition of required basepoints"
              << std::endl << std::flush;
    return 1;
  }

  segment->populate();

  assert(segment->isValid());

  terrain.updateMod(mp3);

  assert(!segment->isValid());

  boost_ring new_shape;
  new_shape.push_back(boost_point(-80.f, 80.f));
  new_shape.push_back(boost_point(-80.f, 85.f));
  new_shape.push_back(boost_point(-75.f, 85.f));
  new_shape.push_back(boost_point(-75.f, 80.f));
  new_shape.push_back(boost_point(-80.f, 80.f));

  boost_ring new_shape2;
  new_shape2.push_back(boost_point(-80.f, -80.f));
  new_shape2.push_back(boost_point(-80.f, -75.f));
  new_shape2.push_back(boost_point(-75.f, -75.f));
  new_shape2.push_back(boost_point(-75.f, -80.f));
  new_shape2.push_back(boost_point(-80.f, -80.f));

  //Check that the stored bbox is correctly updated when calling updateMod().
  auto mp3_rect1 = mp3->bbox();
  mp3->setShape(-5.f, new_shape);
  auto mp3_rect2 = terrain.updateMod(mp3);
  assert(mp3_rect1 == mp3_rect2);
  auto mp3_rect3 = mp3->bbox();
  mp3->setShape(-5.f, new_shape2);
  auto mp3_rect4 = terrain.updateMod(mp3);
  assert(mp3_rect3 == mp3_rect4);

  terrain.removeMod(mp1);

  delete mp1;

  terrain.removeMod(mp3);

  delete mp3;

  return terrain_mod_context_test(terrain);
}
