// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include "Test.h"

#include <dymaxion/Interp.h>

class LinInterptest : public Test::Suite
{
 public:
  LinInterptest();

  void setup() override;
  void teardown() override;

  void test_LinInterp();
  void test_flat();
  void test_calc();
  void test_calc_nocalc();
};

LinInterptest::LinInterptest()
{
  ADD_TEST(LinInterptest::test_LinInterp);
  ADD_TEST(LinInterptest::test_flat);
  ADD_TEST(LinInterptest::test_calc);
  ADD_TEST(LinInterptest::test_calc_nocalc);
}

void LinInterptest::setup()
{
}

void LinInterptest::teardown()
{
}

void LinInterptest::test_LinInterp()
{
  dymaxion::LinInterp i(4, 0, 4);

  ASSERT_TRUE(!i.noCalc);
  ASSERT_EQUAL(i.m_size, 4);
}

void LinInterptest::test_flat()
{
  dymaxion::LinInterp i(4, 4, 4);

  ASSERT_TRUE(i.noCalc);
}

void LinInterptest::test_calc()
{
  dymaxion::LinInterp i(4, 0, 4);

  ASSERT_TRUE(!i.noCalc);
  ASSERT_EQUAL(i.calc(2), 2);
}

void LinInterptest::test_calc_nocalc()
{
  dymaxion::LinInterp i(4, 2, 2);

  ASSERT_TRUE(i.noCalc);
  ASSERT_EQUAL(i.calc(2), 2);
}

class QuadInterptest : public Test::Suite
{
 public:
  QuadInterptest();

  void setup() override;
  void teardown() override;

  void test_QuadInterp();
  void test_flat();
  void test_calc();
  void test_calc_nocalc();
};

QuadInterptest::QuadInterptest()
{
  ADD_TEST(QuadInterptest::test_QuadInterp);
  ADD_TEST(QuadInterptest::test_flat);
  ADD_TEST(QuadInterptest::test_calc);
  ADD_TEST(QuadInterptest::test_calc_nocalc);
}

void QuadInterptest::setup()
{
}

void QuadInterptest::teardown()
{
}

void QuadInterptest::test_QuadInterp()
{
  dymaxion::QuadInterp qi(4, 2, 4, 6, 8);

  ASSERT_TRUE(!qi.noCalc);
  ASSERT_EQUAL(qi.m_size, 4);
}

void QuadInterptest::test_flat()
{
  dymaxion::QuadInterp qi(4, 2, 2, 2, 2);

  ASSERT_TRUE(qi.noCalc);
  ASSERT_EQUAL(qi.m_size, 4);
}

void QuadInterptest::test_calc()
{
  dymaxion::QuadInterp qi(4, 2, 4, 6, 8);

  ASSERT_TRUE(!qi.noCalc);
  ASSERT_EQUAL(qi.calc(2, 2), 5);
}

void QuadInterptest::test_calc_nocalc()
{
  dymaxion::QuadInterp qi(4, 2, 2, 2, 2);

  ASSERT_TRUE(qi.noCalc);
  ASSERT_EQUAL(qi.calc(2, 2), 2);
}

int main()
{
    LinInterptest t1;
    QuadInterptest t2;

    return t1.run() + t2.run();
}
