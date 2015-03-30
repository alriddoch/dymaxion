// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#include <dymaxion/Segment.h>
#include <dymaxion/Surface.h>
#include <dymaxion/FillShader.h>
#include <dymaxion/ThresholdShader.h>
#include <dymaxion/DepthShader.h>
#include <dymaxion/GrassShader.h>

template <class ShaderType>
int shadeTest(dymaxion::Segment & segment)
{
  ShaderType shader;
  dymaxion::Surface surface(segment, shader);

  if (surface.getChannels() != 4)
  {
    std::cerr << "Surface does not have 4 channels."
              << std::endl << std::flush;
    return 1;
  }

  if (shader.checkIntersect(segment))
  {
    surface.populate();
  }
  return 0;
}

int main()
{
  dymaxion::Segment segment(0, 0, dymaxion::defaultResolution);
  segment.populate();

  int errorCount = 0;
  errorCount += shadeTest<dymaxion::FillShader>(segment);
  errorCount += shadeTest<dymaxion::HighShader>(segment);
  errorCount += shadeTest<dymaxion::LowShader>(segment);
  errorCount += shadeTest<dymaxion::BandShader>(segment);
  errorCount += shadeTest<dymaxion::DepthShader>(segment);
  errorCount += shadeTest<dymaxion::GrassShader>(segment);

  return (errorCount ? 1 : 0);
}

