// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#include <dymaxion/FillShader.h>

#include <dymaxion/Segment.h>
#include <dymaxion/Surface.h>

namespace dymaxion {

FillShader::FillShader()
{
}

FillShader::FillShader(const Parameters & params)
{
}

FillShader::~FillShader()
{
}

bool FillShader::checkIntersect(const Segment &) const
{
    return true;
}

void FillShader::shade(Surface & s) const
{
    auto channels = s.getChannels();
    ColorT * data = s.getData();
    auto size = s.getSegment().getSize();

    auto buflen = size * size * channels;
    for (unsigned int i = 0; i < buflen; ++i) {
        data[i] = colorMax;
    }
}

} // namespace dymaxion
