#include <dymaxion/Area.h>
#include <dymaxion/Terrain.h>
#include <dymaxion/Segment.h>
#include <dymaxion/Surface.h>
#include <dymaxion/AreaShader.h>
#include <dymaxion/FillShader.h>

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <fstream>

void writePGMForSurface(std::string const & fileName, int sz, dymaxion::Surface * s)
{
  assert(s);

  std::ofstream file(fileName.c_str());
  file << "P5" << std::endl;
  file << sz << ' ' << sz << " 255" << std::endl;

  // now just blast out the binary
  file.write((const char *) s->getData(), sz * sz);
  file.close();
}

void testAreaShader()
{
  dymaxion::Area * a1 = new dymaxion::Area(1, false);

  dymaxion::Area::ring p;
  p.push_back(dymaxion::Area::point(3, 4));
  p.push_back(dymaxion::Area::point(3, 10));
  p.push_back(dymaxion::Area::point(14, 12));
  p.push_back(dymaxion::Area::point(18, 4));
  p.push_back(dymaxion::Area::point(17, 2));
  p.push_back(dymaxion::Area::point(6, -2));
  p.push_back(dymaxion::Area::point(3, 4));

  a1->setShape(p);

  dymaxion::Area * a2 = new dymaxion::Area(1, false);

  dymaxion::Area::ring p2;
  p2.push_back(dymaxion::Area::point(-2, 2));
  p2.push_back(dymaxion::Area::point(2, 18));
  p2.push_back(dymaxion::Area::point(72, 22));
  p2.push_back(dymaxion::Area::point(60, 30));
  p2.push_back(dymaxion::Area::point(67, 2));
  p2.push_back(dymaxion::Area::point(25, 4));
  p2.push_back(dymaxion::Area::point(3, 4));
  p2.push_back(dymaxion::Area::point(2, 8));
  p2.push_back(dymaxion::Area::point(-2, 2));
  a2->setShape(p2);

  dymaxion::Terrain terrain(dymaxion::Terrain::SHADED, 16);

  dymaxion::Shader * base_shader =
    new dymaxion::FillShader(dymaxion::Shader::Parameters());
  terrain.addShader(base_shader, 0);

  dymaxion::AreaShader * ashade = new dymaxion::AreaShader(1);
  terrain.addShader(ashade, 1);

  terrain.setBasePoint(0, 0, -1);
  terrain.setBasePoint(0, 1, 8);
  terrain.setBasePoint(1, 0, 2);
  terrain.setBasePoint(1, 1, 11);
  terrain.setBasePoint(2, 0, 2);
  terrain.setBasePoint(2, 1, 11);

  terrain.addArea(a1);
  // terrain.addArea(a2);

  dymaxion::Segment * seg = terrain.getSegment(0, 0);
  assert(a1->checkIntersects(*seg));

  seg->populateSurfaces();
  writePGMForSurface("test1.pgm", seg->getSize(), seg->getSurfaces()[1]);


  seg = terrain.getSegment(1, 0);
  seg->populateSurfaces();
  writePGMForSurface("test2.pgm", seg->getSize(), seg->getSurfaces()[1]);
}

static const unsigned int seg_size = 8;

void testAddToSegment()
{
  dymaxion::Area * a1 = new dymaxion::Area(1, false);

  dymaxion::Area::ring p;
  p.push_back(dymaxion::Area::point(1, 1));
  p.push_back(dymaxion::Area::point(1, 6));
  p.push_back(dymaxion::Area::point(6, 6));
  p.push_back(dymaxion::Area::point(6, 1));
  p.push_back(dymaxion::Area::point(1, 1));

  a1->setShape(p);

  dymaxion::Segment * seg1 = new dymaxion::Segment(0, 0, seg_size);

  int success = a1->addToSegment(*seg1);
  assert(success == 0);

  dymaxion::Segment * seg2 = new dymaxion::Segment(1 * seg_size, 0, seg_size);

  success = a1->addToSegment(*seg2);
  assert(success != 0);
}

int main(int argc, char * argv[])
{
  dymaxion::Area * a1 = new dymaxion::Area(1, false);

  dymaxion::Area::ring p;
  p.push_back(dymaxion::Area::point(-3, 4));
  p.push_back(dymaxion::Area::point(3, 5));
  p.push_back(dymaxion::Area::point(4, 10));
  p.push_back(dymaxion::Area::point(6, 18));
  p.push_back(dymaxion::Area::point(7, 1));
  p.push_back(dymaxion::Area::point(-2, 1));
  p.push_back(dymaxion::Area::point(-3, 4));

  a1->setShape(p);

  dymaxion::Terrain terrain(dymaxion::Terrain::SHADED, seg_size);

  dymaxion::AreaShader * ashade = new dymaxion::AreaShader(1);
  terrain.addShader(ashade, 0);

  terrain.setBasePoint(-2, -1, 5);
  terrain.setBasePoint(-2, 0, 2);
  terrain.setBasePoint(-2, 1, 19);

  terrain.setBasePoint(-1, -1, 4);
  terrain.setBasePoint(-1, 0, 6);
  terrain.setBasePoint(-1, 1, 10);
  terrain.setBasePoint(-1, 2, 10);

  terrain.setBasePoint(0, -1, 2);
  terrain.setBasePoint(0, 0, -1);
  terrain.setBasePoint(0, 1, 8);
  terrain.setBasePoint(0, 2, 11);

  terrain.setBasePoint(1, -1, 7);
  terrain.setBasePoint(1, 0, 2);
  terrain.setBasePoint(1, 1, 11);
  terrain.setBasePoint(1, 2, 9);

  terrain.setBasePoint(2, -1, 3);
  terrain.setBasePoint(2, 0, 8);
  terrain.setBasePoint(2, 1, 2);
  terrain.setBasePoint(2, 2, 2);

  terrain.setBasePoint(3, -1, 6);
  terrain.setBasePoint(3, 0, 7);
  terrain.setBasePoint(3, 1, 9);
  terrain.setBasePoint(3, 2, 9);

  terrain.addArea(a1);

  dymaxion::Segment * seg = terrain.getSegment(0, 0);
  assert(seg->getAreas().size() == 1);
  assert(seg->getAreas().count(1) == 1);
  assert(a1->checkIntersects(*seg));

  seg = terrain.getSegment(1, 0);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);
  assert(a1->checkIntersects(*seg) == false);

  auto clipped = a1->clipToSegment(*seg);
  assert(clipped.empty());

  seg = terrain.getSegment(-1, 0);
  assert(seg->getAreas().size() == 1);
  assert(seg->getAreas().count(1) == 1);
  assert(a1->checkIntersects(*seg));

  clipped = a1->clipToSegment(*seg);
  assert(!clipped.empty());

  seg = terrain.getSegment(-1, -1);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);
  assert(a1->checkIntersects(*seg) == false);

  seg = terrain.getSegment(-1, 1);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);
  assert(a1->checkIntersects(*seg) == false);

  seg = terrain.getSegment(0, 1);
  assert(seg->getAreas().size() == 1);
  assert(seg->getAreas().count(1) == 1);
  assert(a1->checkIntersects(*seg));

  clipped = a1->clipToSegment(*seg);
  assert(!clipped.empty());

  seg = terrain.getSegment(1, 1);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);
  assert(a1->checkIntersects(*seg) == false);

  seg = terrain.getSegment(2, 0);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);
  assert(a1->checkIntersects(*seg) == false);

  seg = terrain.getSegment(2, 1);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);
  assert(a1->checkIntersects(*seg) == false);

  p.clear();
  p.push_back(dymaxion::Area::point(-3 + seg_size, 4));
  p.push_back(dymaxion::Area::point(3 + seg_size, 5));
  p.push_back(dymaxion::Area::point(4 + seg_size, 10));
  p.push_back(dymaxion::Area::point(6 + seg_size, 18));
  p.push_back(dymaxion::Area::point(7 + seg_size, 1));
  p.push_back(dymaxion::Area::point(-2 + seg_size, 1));
  p.push_back(dymaxion::Area::point(-3 + seg_size, 4));

  a1->setShape(p);

  terrain.updateArea(a1);

  seg = terrain.getSegment(0, 0);
  assert(seg->getAreas().size() == 1);
  assert(seg->getAreas().count(1) == 1);
  assert(a1->checkIntersects(*seg));

  clipped = a1->clipToSegment(*seg);
  assert(!clipped.empty());

  seg = terrain.getSegment(1, 0);
  assert(seg->getAreas().size() == 1);
  assert(seg->getAreas().count(1) == 1);
  assert(a1->checkIntersects(*seg));

  clipped = a1->clipToSegment(*seg);
  assert(!clipped.empty());

  seg = terrain.getSegment(-1, 0);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);
  assert(a1->checkIntersects(*seg) == false);

  seg = terrain.getSegment(0, 1);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);
  assert(a1->checkIntersects(*seg) == false);

  seg = terrain.getSegment(2, 0);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);
  assert(a1->checkIntersects(*seg) == false);

  clipped = a1->clipToSegment(*seg);
  assert(clipped.empty());

  terrain.removeArea(a1);

  seg = terrain.getSegment(0, 0);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);

  seg = terrain.getSegment(1, 0);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);

  seg = terrain.getSegment(-1, 0);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);

  seg = terrain.getSegment(0, 1);
  assert(seg->getAreas().size() == 0);
  assert(seg->getAreas().count(1) == 0);

  testAreaShader();

  testAddToSegment();

  return EXIT_SUCCESS;
}

