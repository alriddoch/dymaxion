// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#ifndef DYMAXION_SURFACE_H
#define DYMAXION_SURFACE_H

#include <dymaxion/Buffer.h>

#include <climits>

namespace dymaxion {

class Shader;

typedef unsigned char ColorT;

static const ColorT colorMax = UCHAR_MAX;
static const ColorT colorMin = 0;

/// \brief Data store for terrain surface data.
class Surface : public Buffer<ColorT> {
  public:
    /// \brief The shader that populates this surface.
    const Shader & m_shader;

    explicit Surface(const Segment & segment, const Shader & shader,
                     bool colors = true, bool alpha = true);
    virtual ~Surface();

    void populate();
    // Do we need an accessor presenting the array in colour form?
};

} // namespace dymaxion

#endif // DYMAXION_SURFACE_H
