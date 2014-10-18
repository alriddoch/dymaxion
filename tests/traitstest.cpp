// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include "Test.h"

#include <dymaxion/wfmath_traits.h>

using dymaxion::traits::axisbox_access;
using dymaxion::traits::point_access;
using dymaxion::traits::point_construct;

class WFMath_AxisBox_traitstest : public Test::Suite
{
  public:
    WFMath_AxisBox_traitstest();

    void setup() override;
    void teardown() override;

};

WFMath_AxisBox_traitstest::WFMath_AxisBox_traitstest()
{
}

void WFMath_AxisBox_traitstest::setup()
{
}

void WFMath_AxisBox_traitstest::teardown()
{
}

class WFMath_Point_traitstest : public Test::Suite
{
  private:
    template <class P>
    P getPoint2();

    template <class P>
    P getPoint3();

    template <class P>
    void setPoint2(const P &);

    template <class P>
    void setPoint3(const P &);

    static constexpr float getPoint_x = .23f;
    static constexpr float getPoint_y = 1.7f;
    static constexpr float getPoint_z = 5.9f;

    static constexpr float setPoint_x = .17f;
    static constexpr float setPoint_y = 2.3f;
    static constexpr float setPoint_z = 9.5f;

    float m_x = 0.f;
    float m_y = 0.f;
    float m_z = 0.f;
  public:
    WFMath_Point_traitstest();

    void setup() override;
    void teardown() override;

    void test_access_wfmath_point2_set();
    void test_access_wfmath_point2_get();
    void test_access_wfmath_point3_set();
    void test_access_wfmath_point3_get();
    void test_construct_point2();
    void test_construct_point3();
};

constexpr float WFMath_Point_traitstest::getPoint_x;
constexpr float WFMath_Point_traitstest::getPoint_y;
constexpr float WFMath_Point_traitstest::getPoint_z;

constexpr float WFMath_Point_traitstest::setPoint_x;
constexpr float WFMath_Point_traitstest::setPoint_y;
constexpr float WFMath_Point_traitstest::setPoint_z;

WFMath_Point_traitstest::WFMath_Point_traitstest()
{
    ADD_TEST(WFMath_Point_traitstest::test_access_wfmath_point2_set);
    ADD_TEST(WFMath_Point_traitstest::test_access_wfmath_point2_get);
    ADD_TEST(WFMath_Point_traitstest::test_access_wfmath_point3_set);
    ADD_TEST(WFMath_Point_traitstest::test_access_wfmath_point3_get);
    ADD_TEST(WFMath_Point_traitstest::test_construct_point2);
    ADD_TEST(WFMath_Point_traitstest::test_construct_point3);
}

void WFMath_Point_traitstest::setup()
{
    m_x = 0.f;
    m_y = 0.f;
    m_z = 0.f;
}

void WFMath_Point_traitstest::teardown()
{
}

template <class P>
P WFMath_Point_traitstest::getPoint2()
{
    P p;
    point_access<P, 0>::set(p, getPoint_x);
    point_access<P, 1>::set(p, getPoint_y);
    return p;
}

template <class P>
void WFMath_Point_traitstest::setPoint2(const P & p)
{
    m_x = point_access<P, 0>::get(p);
    m_y = point_access<P, 1>::get(p);
}

template <class P>
P WFMath_Point_traitstest::getPoint3()
{
    P p;
    point_access<P, 0>::set(p, getPoint_x);
    point_access<P, 1>::set(p, getPoint_y);
    point_access<P, 2>::set(p, getPoint_z);
    return p;
}

template <class P>
void WFMath_Point_traitstest::setPoint3(const P & p)
{
    m_x = point_access<P, 0>::get(p);
    m_y = point_access<P, 1>::get(p);
    m_z = point_access<P, 2>::get(p);
}

void WFMath_Point_traitstest::test_access_wfmath_point2_set()
{
    WFMath::Point<2> p;
    p = getPoint2<WFMath::Point<2>>();

    ASSERT_EQUAL(p.x(), getPoint_x);
    ASSERT_EQUAL(p.y(), getPoint_y);
}

void WFMath_Point_traitstest::test_access_wfmath_point2_get()
{
    WFMath::Point<2> p(setPoint_x, setPoint_y);

    setPoint2(p);

    ASSERT_EQUAL(m_x, setPoint_x);
    ASSERT_EQUAL(m_y, setPoint_y);
}

void WFMath_Point_traitstest::test_access_wfmath_point3_set()
{
    WFMath::Point<3> p;
    p = getPoint3<WFMath::Point<3>>();

    ASSERT_EQUAL(p.x(), getPoint_x);
    ASSERT_EQUAL(p.y(), getPoint_y);
    ASSERT_EQUAL(p.z(), getPoint_z);
}

void WFMath_Point_traitstest::test_access_wfmath_point3_get()
{
    WFMath::Point<3> p(setPoint_x, setPoint_y, setPoint_z);

    setPoint3(p);

    ASSERT_EQUAL(m_x, setPoint_x);
    ASSERT_EQUAL(m_y, setPoint_y);
    ASSERT_EQUAL(m_z, setPoint_z);
}

void WFMath_Point_traitstest::test_construct_point2()
{
    WFMath::Point<2> p = point_construct<WFMath::Point<2>>::make(setPoint_x, setPoint_y);

    ASSERT_EQUAL(p.x(), setPoint_x);
    ASSERT_EQUAL(p.y(), setPoint_y);
}

void WFMath_Point_traitstest::test_construct_point3()
{
    WFMath::Point<3> p = point_construct<WFMath::Point<3>>::make(setPoint_x, setPoint_y, setPoint_z);

    ASSERT_EQUAL(p.x(), setPoint_x);
    ASSERT_EQUAL(p.y(), setPoint_y);
    ASSERT_EQUAL(p.z(), setPoint_z);
}

int main()
{
    WFMath_Point_traitstest t1;
    WFMath_AxisBox_traitstest t2;

    return t1.run() + t2.run();
}
