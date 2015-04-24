// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2015 Alistair Riddoch

#include "test/Test.h"

#include "quaternion.h"

class quaterniontest : public Test::Suite
{
 public:
  quaterniontest();

  void setup() override;
  void teardown() override;

  void test_foo();
};

quaterniontest::quaterniontest()
{
  ADD_TEST(quaterniontest::test_foo);
}

void quaterniontest::setup()
{
}

void quaterniontest::teardown()
{
}

void quaterniontest::test_foo()
{
}

int main()
{
  quaterniontest t;

  return t.run();
}
