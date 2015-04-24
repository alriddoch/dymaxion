// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2015 Alistair Riddoch

#include "test/Test.h"

#include "vector.h"

class vectortest : public Test::Suite
{
 public:
  vectortest();

  void setup() override;
  void teardown() override;

  void test_dot();
};

vectortest::vectortest()
{
  ADD_TEST(vectortest::test_dot);
}

void vectortest::setup()
{
}

void vectortest::teardown()
{
}

void vectortest::test_dot()
{
  float a[] = { 1, 0},
        b[] = { 0, 1};

  float c = vector2_dot(a, b);

  ASSERT_EQUAL(c, 0);
}

int main()
{
  vectortest t;

  return t.run();
}
