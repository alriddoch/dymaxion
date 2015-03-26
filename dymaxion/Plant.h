// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2004 Alistair Riddoch

#ifndef DYMAXION_PLANT_H
#define DYMAXION_PLANT_H

#include <dymaxion/traits.h>

#include <wfmath/quaternion.h>

#include <string>

namespace dymaxion {

/// \brief This is the simple class for representing instances of vegetation.
///
/// It is used in instances of class Forest to represent each instance
/// of vegetation created when the Forest is populated.
class Plant {
 private:
  /// Position of the vegetation relative to its grid point.
  float m_displacement[2];
  /// Orientation of the vegetation.
  WFMath::Quaternion m_orientation;
  /// Height of the vegetation.
  float m_height = 0.f;
 public:
  /// Height is initialised explicitly to zero.
  Plant();
  /// Nothing special in the destructor.
  ~Plant();

  /// Accessor for displacement from grid point.
  template <class P>
  P getDisplacement() const
  {
    return traits::point_construct<P>::make(m_displacement[0],
                                            m_displacement[1]);
  }

  /// Set the displacement to a new value.
  template <class P>
  void setDisplacement(const P & d)
  {
    m_displacement[0] = traits::point_access<P, 0>::get(d);
    m_displacement[1] = traits::point_access<P, 1>::get(d);
  }

  /// Set the displacement to a new raw value.
  void setDisplacement(float x, float y)
  {
    m_displacement[0] = x;
    m_displacement[1] = y;
  }

  /// Accessor for orientation.
  const WFMath::Quaternion & getOrientation() const
  {
    return m_orientation;
  }

  /// Set the orientation to a new value.
  void setOrientation(const WFMath::Quaternion & o)
  {
    m_orientation = o;
  }

  /// Accessor for height.
  const float getHeight() const
  {
    return m_height;
  }

  /// Set the height to a new value.
  void setHeight(float h)
  {
    m_height = h;
  }

  /// Set a named parameter value for this plant.
  void setParameter(const std::string &, float)
  {
  }

};

}

#endif // DYMAXION_PLANT_H
