// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2015 Alistair Riddoch

#include "vector.h"

#include <iostream>

int main()
{
  float a[] = { 1, 0},
        b[] = { 0, 1};

  float c = vector2_dot(a, b);

  std::cout << c << std::endl;
}
