// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2010 Alistair Riddoch

#ifndef DYMAXION_EFFECTOR_H
#define DYMAXION_EFFECTOR_H

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <string>

namespace dymaxion
{

class Segment;
class Shader;

/// \brief Device which effects a change in the terrain
///
/// Classes which inherit from this interface change the terrain in
/// some way within the region given by the box member. The exact
/// shape of the area affected and the nature of the change depends
/// on the subclass.
class Effector
{
 public:

  typedef boost::geometry::model::d2::point_xy<
    float, boost::geometry::cs::cartesian> point;
  typedef boost::geometry::model::box<point> box;

  class Context {
   public:
    Context();

    virtual ~Context();

    std::string const & id()
    {
      return m_id;
    }

    void setId(std::string const &);

   protected:
    std::string m_id;
  };

  Context * context() const
  {
    return m_context;
  }

  void setContext(Context *);

  /// Accessor for the bounding box of the geometric shape.
  box const & bbox() const
  {
    return m_box;
  }

  virtual ~Effector() = 0;

  virtual bool checkIntersects(const Segment& s) const = 0;

  virtual int addToSegment(Segment &) const = 0;
  virtual void updateToSegment(Segment &) const = 0;
  virtual void removeFromSegment(Segment &) const = 0;

 protected:
  /// \brief Constructor
  Effector();

  /// \brief Copy constructor
  Effector(Effector const &);

  /// \brief Assignment
  Effector & operator=(Effector const &);

  /// The bounding box of the geometric shape.
  box m_box;

  /// The application context of this effector
  Context * m_context = 0;
};

/// \brief Function used to apply an effector to an existing height point
typedef float (*effector_func)(float height, float mod);

float set(float, float);
float max(float, float);
float min(float, float);
float sum(float, float);
float dif(float, float);

}

#endif // of DYMAXION_EFFECTOR_H
