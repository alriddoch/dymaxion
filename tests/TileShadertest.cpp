// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#include <dymaxion/Segment.h>
#include <dymaxion/Surface.h>
#include <dymaxion/FillShader.h>
#include <dymaxion/ThresholdShader.h>
#include <dymaxion/DepthShader.h>
#include <dymaxion/GrassShader.h>
#include <dymaxion/TileShader.h>

int main()
{
    dymaxion::Segment segment(0,0,dymaxion::defaultResolution);
    segment.populate();

    dymaxion::TileShader tileShader;
    tileShader.addShader(new dymaxion::FillShader(), 0);
    tileShader.addShader(new dymaxion::BandShader(-2.f, 1.5f), 1);
    tileShader.addShader(new dymaxion::GrassShader(1.f, 80.f, .5f, 1.f), 2);
    tileShader.addShader(new dymaxion::DepthShader(0.f, -10.f), 3);
    tileShader.addShader(new dymaxion::HighShader(110.f), 4);
    dymaxion::Surface * surface = tileShader.newSurface(segment);
    surface->populate();
}
