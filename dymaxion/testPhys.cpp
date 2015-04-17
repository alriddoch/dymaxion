// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Damien McGinnes

#include <dymaxion/Terrain.h>
#include <dymaxion/Segment.h>
#include <dymaxion/Intersect.h>
#include <dymaxion/tuple_vector.h>
#include <dymaxion/wfmath_traits.h>

#include <iostream>

std::ostream & operator<<(std::ostream & os,
                          std::tuple<float, float, float> const & arg)
{
  os << "("
  << std::get<0>(arg) << ","
  << std::get<1>(arg) << ","
  << std::get<2>(arg)
  << ")" << std::endl;
  return os;
}

//test intersection using a rudimentary physics simulation
//this drops a particle onto the terrain and it bounces around a bit
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

  segment->populate();

  WFMath::Point<3> pos(30.0, 30.0, 100.0); //starting position
  std::tuple<float, float, float> vel(0.0, 1.0, 0.0); //starting velocity
  std::tuple<float, float, float> grav(0.0, 0.0, -9.8); //gravity

  WFMath::Point<3> intersection;
  std::tuple<float, float, float> intnormal;

  float timestep = 0.1;
  float e = 0.2;   //elasticity of collision
  float totalT = 20.0;   //time limit
  float par = 0.0;
  float t = timestep;

  while (totalT > timestep)
  {
    dymaxion::add_i(vel, dymaxion::scale(grav, t));
    if (dymaxion::Intersect(terrain, pos, dymaxion::scale(vel, t), intersection, intnormal, par))
    {
      //set pos to collision time,
      //less a small amout to keep objects apart
      pos = dymaxion::translate(intersection,
                                dymaxion::scale(vel, -.01 * t));

      std::tuple<float, float, float> impulse =
        dymaxion::scale(intnormal, dymaxion::dot(vel, intnormal) * -2);
      std::cerr << "HIT" << std::endl;
      //not sure of the impulse equation, but this will do
      vel = dymaxion::scale(dymaxion::add(vel, impulse), e);

      if (dymaxion::sqr_mag(vel) < 0.01)
      {
        //stop if velocities are small
        std::cerr << "friction stop" << std::endl;
        break;
      }
      totalT -= par * t;
      t = (1.0 - par) * t;
    }
    else
    {
      dymaxion::translate_i(pos, dymaxion::scale(vel, t));
      totalT -= t;
      t = timestep;
    }

    std::cerr << "timeLeft:" << totalT << " end pos" << pos << " vel" << vel << std::endl;
  }

  return 0;
}

