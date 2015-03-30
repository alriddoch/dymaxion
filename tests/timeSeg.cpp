// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Damien McGinnes

#include <dymaxion/Terrain.h>
#include <dymaxion/Segment.h>
#include <dymaxion/Intersect.h>
#include <dymaxion/Forest.h>
#include <dymaxion/Area.h>
#include "util_timer.h"
#include <iostream>

typedef WFMath::Point<2> Point2;

int main()
{
  dymaxion::Terrain terrain;

  terrain.setBasePoint(0, 0, 2.8);
  terrain.setBasePoint(1, 0, 7.1);
  terrain.setBasePoint(0, 1, 0.2);
  terrain.setBasePoint(1, 1, 14.7);

  dymaxion::Segment * segment = terrain.getSegment(0, 0);

  if (segment == 0)
  {
    std::cerr << "Segment not created by addition of required basepoints"
              << std::endl << std::flush;
    return 1;
  }

  Util::Timer time;
  time.start();

  for (int q = 0; q < 1000; q++)
  {
    segment->populate();
  }

  time.stop();
  std::cout << "time per segment = " << (time.interval() / 1.0) << " ms" << std::endl;


  dymaxion::Forest forest(4249162ul);
  dymaxion::Area::ring p;
  p.push_back(dymaxion::Area::point(-50, -50));
  p.push_back(dymaxion::Area::point(50, -50));
  p.push_back(dymaxion::Area::point(50, 50));
  p.push_back(dymaxion::Area::point(-50, 50));
  p.push_back(dymaxion::Area::point(-50, 50));
  p.push_back(dymaxion::Area::point(-50, -50));

  dymaxion::Area* ar = new dymaxion::Area(1, false);
  ar->setShape(p);
  forest.setArea(ar);

  time.start();
  for (int q = 0; q < 10; q++)
  {
    forest.populate();
  }
  time.stop();

  std::cout << "time per 100x100 forest = " << (time.interval() * 100.0) << " ms" << std::endl;

  p.clear();
  p.push_back(dymaxion::Area::point(-100, -100));
  p.push_back(dymaxion::Area::point(100, -100));
  p.push_back(dymaxion::Area::point(100, 100));
  p.push_back(dymaxion::Area::point(-100, 100));

  ar = new dymaxion::Area(1, false);
  ar->setShape(p);
  forest.setArea(ar);

  time.start();
  for (int q = 0; q < 10; q++)
  {
    forest.populate();
  }
  time.stop();


  std::cout << "time per 200x200 forest = " << (time.interval() * 100.0) << " ms" << std::endl;



  return 0;
}

