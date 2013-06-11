// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#include <dymaxion/DepthShader.h>

#include <dymaxion/Segment.h>
#include <dymaxion/Surface.h>

#include <cmath>

#include <cassert>

namespace dymaxion {

const std::string DepthShader::key_waterLevel("waterLevel");
const std::string DepthShader::key_murkyDepth("murkyDepth");

const float DepthShader::default_waterLevel = 0.f;
const float DepthShader::default_murkyDepth = -64.f;


DepthShader::DepthShader(float waterLevel, float murkyDepth) : 
             m_waterLevel(waterLevel), m_murkyDepth(murkyDepth)
{
}

DepthShader::DepthShader(const Parameters & params) :
             m_waterLevel(default_waterLevel), m_murkyDepth(default_murkyDepth)
{
    Parameters::const_iterator I = params.find(key_waterLevel);
    Parameters::const_iterator Iend = params.end();
    if (I != Iend) {
        m_waterLevel = I->second;
    }
    I = params.find(key_murkyDepth);
    if (I != Iend) {
        m_murkyDepth = I->second;
    }
}

DepthShader::~DepthShader()
{
}

bool DepthShader::checkIntersect(const Segment & s) const
{
    if (s.getMin() < m_waterLevel) {
        return true;
    } else {
        return false;
    }
}

void DepthShader::shade(Surface & s) const
{
    auto channels = s.getChannels();
    assert(channels > 0);
    auto colors = channels - 1;
    auto * data = s.getData();
    auto const * height_data = s.getSegment().getPoints();
    if (height_data == 0) {
        std::cerr << "WARNING: Mercator: Attempting to shade empty segment."
                  << std::endl << std::flush;
        return;
    }
    auto size = s.getSegment().getSize();

    auto count = size * size;
    int j = -1;
    for (unsigned int i = 0; i < count; ++i) {
        for (unsigned int k = 0; k < colors; ++k) {
            data[++j] = std::numeric_limits<ColorT>::max();
        }
        auto depth = height_data[i];
        if (depth > m_waterLevel) {
            data[++j] = std::numeric_limits<ColorT>::min();
        } else if (depth < m_murkyDepth) {
            data[++j] = std::numeric_limits<ColorT>::max();
        } else {
            data[++j] = std::numeric_limits<ColorT>::max() -
                        std::lrint(std::numeric_limits<ColorT>::max() *
                                   ((depth - m_murkyDepth) /
                                    (m_waterLevel - m_murkyDepth)));
        }
    }
}

} // namespace dymaxion
