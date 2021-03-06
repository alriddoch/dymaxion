// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#ifndef DYMAXION_FILL_SHADER_H
#define DYMAXION_FILL_SHADER_H

#include <dymaxion/Shader.h>

namespace dymaxion {

/// \brief Shader that fills the surface.
///
/// This shader is typically only used for the lowest possible layer,
/// which is usually bed rock.
class FillShader : public Shader {
 public:
  /// \brief Constructor
  explicit FillShader();
  /// \brief Constructor
  ///
  /// @param params a map of parameters for the shader.
  explicit FillShader(Parameters const & params);
  virtual ~FillShader();

  virtual bool checkIntersect(Segment const &) const;
  virtual void shade(Surface &) const;

};

} // namespace dymaxion

#endif // DYMAXION_FILL_SHADER_H
