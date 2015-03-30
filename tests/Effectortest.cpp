// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2015 Alistair Riddoch

#include "Test.h"

#include <dymaxion/Effector.h>

class Effectortest : public Test::Suite
{
 public:
  Effectortest();

  void setup() override;
  void teardown() override;

  void test_Effector();

};

Effectortest::Effectortest()
{
  ADD_TEST(Effectortest::test_Effector);
}

void Effectortest::setup()
{
}

void Effectortest::teardown()
{
}

void Effectortest::test_Effector()
{
}

int main()
{
  Effectortest t;

  return t.run();
}

