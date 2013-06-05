// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2009 Alistair Riddoch

#include <dymaxion/Matrix.h>

int main()
{
    dymaxion::Matrix<2,2> m;
    dymaxion::Matrix<4,4> n;

    m(0,0) = 1.f;

    return 0;
}
