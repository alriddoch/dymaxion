// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include "Test.h"

#include <dymaxion/wfmath_traits.h>

class traitstest : public Test::Suite
{
  private:
    template <class P>
    P getPoint();

    template <class P>
    void setPoint(const P &);

    static constexpr float getPoint_x = .23f;
    static constexpr float getPoint_y = 1.7f;

    static constexpr float setPoint_x = .17f;
    static constexpr float setPoint_y = 2.3f;

    float m_x = 0.f;
    float m_y = 0.f;
  public:
    traitstest();

    void setup();
    void teardown();

    void test_access_wfmath_point2_set();
    void test_access_wfmath_point2_get();
};

constexpr float traitstest::getPoint_x;
constexpr float traitstest::getPoint_y;

constexpr float traitstest::setPoint_x;
constexpr float traitstest::setPoint_y;

traitstest::traitstest()
{
    ADD_TEST(traitstest::test_access_wfmath_point2_set);
    ADD_TEST(traitstest::test_access_wfmath_point2_get);
}

void traitstest::setup()
{
    m_x = 0.f;
    m_y = 0.f;
}

void traitstest::teardown()
{
}

template <class P>
P traitstest::getPoint()
{
    P p;
    dymaxion::traits::point_access<P, 0>::set(p, getPoint_x);
    dymaxion::traits::point_access<P, 1>::set(p, getPoint_y);
    return p;
}

template <class P>
void traitstest::setPoint(const P & p)
{
    m_x = dymaxion::traits::point_access<P, 0>::get(p);
    m_y = dymaxion::traits::point_access<P, 1>::get(p);
}

void traitstest::test_access_wfmath_point2_set()
{
    WFMath::Point<2> p;
    p = getPoint<WFMath::Point<2>>();

    ASSERT_EQUAL(p.x(), getPoint_x);
    ASSERT_EQUAL(p.y(), getPoint_y);
}

void traitstest::test_access_wfmath_point2_get()
{
    WFMath::Point<2> p(setPoint_x, setPoint_y);

    setPoint(p);

    ASSERT_EQUAL(m_x, setPoint_x);
    ASSERT_EQUAL(m_y, setPoint_y);
}

int main()
{
    traitstest t;

    return t.run();
}
