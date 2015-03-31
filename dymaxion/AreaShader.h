// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_AREASHADER_H
#define DYMAXION_AREASHADER_H

#include <dymaxion/Shader.h>

namespace dymaxion
{

class Area;

/// \brief Shader for handling areas.
class AreaShader : public Shader
{
  friend class AreaShadertest;
 public:
  /// \brief Constructor
  ///
  /// @param layer layer number.
  AreaShader(int layer);

  virtual void shade(Surface &s) const;

  virtual bool checkIntersect(Segment const &) const;

 private:
  /// helper to shader a single area into the surface
  void shadeArea(Surface & s, Area const * const ar) const;

  /// The layer number.
  int m_layer;
};

}

#endif // of DYMAXION_AREASHADER_H
