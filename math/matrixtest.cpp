// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2015 Alistair Riddoch

#include "test/Test.h"

#include "matrix.h"

class matrixtest : public Test::Suite
{
 public:
  matrixtest();

  void setup() override;
  void teardown() override;

  void test_foo();
};

matrixtest::matrixtest()
{
  ADD_TEST(matrixtest::test_foo);
}

void matrixtest::setup()
{
}

void matrixtest::teardown()
{
}

void matrixtest::test_foo()
{
}

int main()
{
  matrixtest t;

  return t.run();
}
