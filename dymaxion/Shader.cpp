// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#include <dymaxion/Shader.h>

#include <dymaxion/Segment.h>
#include <dymaxion/Surface.h>

namespace dymaxion {

/// \brief Protected constructor for classes which inherit from this
/// one.
///
/// Permanently sents the color and alpha flags.
Shader::Shader(bool color, bool alpha) : m_color(color), m_alpha(alpha)
{
}

/// \brief Destructor does nothing interesting.
Shader::~Shader()
{
}

/// \brief Create a new Surface which matches the requirements of this shader.
///
/// Called by terrain when creating a new Segment to add the necessary
/// Surface objects to that Segment.
Surface * Shader::newSurface(Segment const & segment) const
{
  return new Surface(segment, *this, m_color, m_alpha);
}

} // namespace dymaxion
