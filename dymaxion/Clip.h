// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include <dymaxion/traits.h>

#include <cmath>
#include <functional>
#include <limits>
#include <type_traits>

#include <cassert>

class TopCliptest;
class BottomCliptest;
class LeftCliptest;
class RightCliptest;

namespace dymaxion
{

#ifndef NDEBUG
template <typename FloatT>
static inline bool isZero(FloatT d)
{
  return (std::fabs(d) < std::numeric_limits<FloatT>::epsilon());
}

#endif

template <int axis, template <typename> class comparison>
class Clip
{
 public:
  /// Constructor
  ///
  /// @param t top of y range
  Clip(float t) : threshold(t)
  {
  }

  /// \brief Check a point is outside this clip.
  ///
  /// @param p point to be checked.
  /// @return true if p is outside the clip.
  template <class P>
  bool inside(P const & p) const
  {
    typedef traits::point_access<P, axis> access;
    return comparison<float>() (access::get(p), threshold);
  }

  /// \brief Determine the point where a line crosses this clip.
  ///
  /// @param u one of of a line that crosses this clip
  /// @param v one of of a line that crosses this clip
  /// @return a point where the line cross this clip.
  template <class P>
  P clip(P const & u, P const & v) const
  {
    constexpr unsigned oaxis = axis ^ 1;

    typedef traits::point_access<P, axis> access;
    typedef traits::point_access<P, oaxis> oaccess;

    std::tuple<float, float> delta {
      traits::point_access<P, 0>::get(v) - traits::point_access<P, 0>::get(u),
      traits::point_access<P, 1>::get(v) - traits::point_access<P, 1>::get(u)
    };

    // shouldn't every happen - if dy iz zero, the line is horizontal,
    // so either both points should be inside, or both points should be
    // outside. In either case, we should not call clip()
    assert(!isZero(std::get<axis>(delta)));

    auto t = (threshold - access::get(u)) / std::get<axis>(delta);
    P p;
    access::set(p, threshold);
    oaccess::set(p, oaccess::get(u) + t * std::get<oaxis>(delta));
    return p;
  }

 private:
  /// \brief Top of y range.
  float threshold;

  friend class::TopCliptest;
  friend class::BottomCliptest;
  friend class::LeftCliptest;
  friend class::RightCliptest;
};

typedef Clip<1, std::less> TopClip;
typedef Clip<1, std::greater_equal> BottomClip;
typedef Clip<0, std::greater_equal> LeftClip;
typedef Clip<0, std::less> RightClip;

} // of namespace
