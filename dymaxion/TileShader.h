// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_TILE_SHADER_H
#define DYMAXION_TILE_SHADER_H

#include <dymaxion/Shader.h>

#include <map>

namespace dymaxion {

/// \brief Shader agregating surface data.
///
/// Some applications require the terrain surface data be stored in a
/// single buffer so specific locations can be queried to determine the type.
/// Typically this is used on a server, where lots of surface data optimised
/// for rendering is not required, but fast cheap queries about the surface
/// at a specific point are required.
class TileShader : public Shader {
 public:
  /// \brief STL map to store sparse array of Shader pointers.
  typedef std::map<int, Shader *> Shaderstore;
 private:
  /// \brief Store of shaders which are agregated by this shader.
  Shaderstore m_subShaders;
 public:
  explicit TileShader();
  virtual ~TileShader();

  /// \brief Add a shader to those agregated by the tile shader.
  void addShader(Shader * t, int id)
  {
    m_subShaders[id] = t;
  }

  virtual bool checkIntersect(Segment const &) const;
  virtual void shade(Surface &) const;

};

} // namespace dymaxion

#endif // DYMAXION_TILE_SHADER_H
