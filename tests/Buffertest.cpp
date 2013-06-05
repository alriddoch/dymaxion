// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2009 Alistair Riddoch

#include <dymaxion/Buffer.h>
#include <dymaxion/Segment.h>

int main()
{
    dymaxion::Segment s(0,0,64);
    dymaxion::Buffer<float> b(s);

    return 0;
}

// stubs

namespace dymaxion {

Segment::Segment(int x, int y, unsigned int resolution) :
                 m_res(resolution),
                 m_size(m_res+1),
                 m_xRef(x),
                 m_yRef(y)
{
}

Segment::~Segment()
{
}

constexpr float BasePoint::HEIGHT;
constexpr float BasePoint::ROUGHNESS;
constexpr float BasePoint::FALLOFF;

}
