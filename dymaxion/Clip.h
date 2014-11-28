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
  Point2 clip(const Point2& u, const Point2& v) const;
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

template<>
Point2 Clip<1, std::greater_equal>::clip(const Point2 & u,
                                         const Point2 & v) const
{
  auto dy = v.y() - u.y();
  auto dx = v.x() - u.x();
  
  // shouldn't every happen - if dy iz zero, the line is horizontal,
  // so either both points should be inside, or both points should be
  // outside. In either case, we should not call clip()
  assert(!isZero(dy));
  
  auto t = (threshold - u.y()) / dy;
  return Point2(u.x() + t * dx, threshold);
}

template<>
Point2 Clip<1, std::less>::clip(const Point2 & u,
                                const Point2 & v) const
{
    auto dy = v.y() - u.y();
    auto dx = v.x() - u.x();
    assert(!isZero(dy));
    
    auto t = (threshold - u.y()) / dy;
    return Point2(u.x() + t * dx, threshold);
}

template<>
Point2 Clip<0, std::less>::clip(const Point2 & u,
                                const Point2 & v) const
{
    auto dy = v.y() - u.y();
    auto dx = v.x() - u.x();
    
    // shouldn't every happen
    assert(!isZero(dx));
    
    auto t = (threshold - u.x()) / dx;
    return Point2(threshold, u.y() + t * dy);
}

template<>
Point2 Clip<0, std::greater_equal>::clip(const Point2 & u,
                                         const Point2 & v) const
{
    auto dy = v.y() - u.y();
    auto dx = v.x() - u.x();
    
    // shouldn't every happen
    assert(!isZero(dx));
    
    auto t = (threshold - u.x()) / dx;
    return Point2(threshold, u.y() + t * dy);
}

} // of namespace
