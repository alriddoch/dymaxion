// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include <dymaxion/wfmath_traits.h>

#include <wfmath/point.h>

#include <cmath>
#include <functional>
#include <type_traits>

#include <cassert>

using WFMath::CoordType;

class TopCliptest;
class BottomCliptest;
class LeftCliptest;
class RightCliptest;

namespace dymaxion
{

typedef WFMath::Point<2> Point2;

#ifndef NDEBUG
static inline bool isZero(CoordType d)
{
  return (std::fabs(d) < WFMath::numeric_constants<CoordType>::epsilon());
}
#endif

template<int axis, template <typename> class comparison>
class Clip
{
 public:
  /// Constructor
  ///
  /// @param t top of y range
  Clip(CoordType t) : threshold(t) { }

  /// \brief Check a point is outside this clip.
  ///
  /// @param p point to be checked.
  /// @return true if p is outside the clip.
  template <class P>
  bool inside(const P & p) const
  {
    typedef traits::point_access<P, axis> access;
    return comparison<CoordType>()(access::get(p), threshold);
  }

  /// \brief Determine the point where a line crosses this clip.
  ///
  /// @param u one of of a line that crosses this clip
  /// @param v one of of a line that crosses this clip
  /// @return a point where the line cross this clip.
  Point2 clip(const Point2& u, const Point2& v) const
  {
    constexpr unsigned oaxis = axis ^ 1;

    typedef traits::point_access<
        std::remove_const<std::remove_reference<decltype(u)>::type>::type,
        0> xaccess;

    typedef traits::point_access<
        std::remove_const<std::remove_reference<decltype(u)>::type>::type,
        1> yaccess;

    typedef traits::point_access<
        std::remove_const<std::remove_reference<decltype(u)>::type>::type,
        axis> access;

    typedef traits::point_access<
        std::remove_const<std::remove_reference<decltype(u)>::type>::type,
        oaxis> oaccess;

    std::tuple<float, float> delta{xaccess::get(v) - xaccess::get(u),
                                   yaccess::get(v) - yaccess::get(u)};

    // shouldn't every happen - if dy iz zero, the line is horizontal,
    // so either both points should be inside, or both points should be
    // outside. In either case, we should not call clip()
    assert(!isZero(std::get<axis>(delta)));

    auto t = (threshold - access::get(u)) / std::get<axis>(delta);
    Point2 p;
    access::set(p, threshold);
    oaccess::set(p, oaccess::get(u) + t * std::get<oaxis>(delta));
    return p;
  }
 private:
  /// \brief Top of y range.
  CoordType threshold;

  friend class ::TopCliptest;
  friend class ::BottomCliptest;
  friend class ::LeftCliptest;
  friend class ::RightCliptest;
};

typedef Clip<1, std::less> TopClip;
typedef Clip<1, std::greater_equal> BottomClip;
typedef Clip<0, std::greater_equal> LeftClip;
typedef Clip<0, std::less> RightClip;

} // of namespace
