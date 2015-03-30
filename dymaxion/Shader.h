// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#ifndef DYMAXION_SHADER_H
#define DYMAXION_SHADER_H

#include <string>
#include <map>

namespace dymaxion {

class Surface;
class Segment;

// FIXME - PLACEHOLDER
// This class itereates over the buffer in a segment using the data it contains
// to populate a RGBA colour buffer based on the terrain height data. ie it is
// used to define the texture blending for a given surface

/// \brief Base class for Shader objects which create surface data for use
/// when rendering terrain.
///
/// Shader objects take heightfield data for a terrain Segment, and use it
/// to populate a Surface with data that can then be used to define the
/// appearance of the terrain when rendering. The Shader is used both to
/// create the Surface object of the right type, and to populate the
/// Surface with data once the Segment heightfield has been generated.
class Shader {
 private:
  /// \brief Flag to control whether this Shader produces color data.
  const bool m_color;
  /// \brief Flag to control whether this Shader produces alpha data.
  const bool m_alpha;
 protected:
  explicit Shader(bool color = false, bool alpha = true);
 public:
  virtual ~Shader();

  /// \brief Accessor for color flag.
  bool getColor() const
  {
    return m_color;
  }

  /// \brief Accessor for alpha flag.
  bool getAlpha() const
  {
    return m_alpha;
  }

  Surface * newSurface(Segment const &) const;

  /// \brief Check whether this Shader has any effect on the given Segment.
  ///
  /// @return true if the given Segment height range is within the range
  /// that this Shader uses. e.g. A high altitude snow shader will have
  /// no effect on low level terrain.
  virtual bool checkIntersect(Segment const &) const = 0;

  /// \brief Populate a Surface with data.
  virtual void shade(Surface &) const = 0;

  /// STL map of parameter values for a shader constructor.
  typedef std::map<std::string, float> Parameters;
};

} // namespace dymaxion

#endif // DYMAXION_SHADER_H
