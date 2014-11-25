// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#include <wfmath/point.h>

#include <cmath>

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

/// \brief Helper to clip points to a given range.
class TopClip
{
 public:
  /// Constructor
  ///
  /// @param t top of y range
  TopClip(CoordType t) : threshold(t) { }
  
  /// \brief Check a point is outside this clip.
  ///
  /// @param p point to be checked.
  /// @return true if p is outside the clip.
  bool inside(const Point2& p) const
  {
    return p.y() >= threshold;
  }

  /// \brief Determine the point where a line crosses this clip.
  ///
  /// @param u one of of a line that crosses this clip
  /// @param v one of of a line that crosses this clip
  /// @return a point where the line cross this clip.
  Point2 clip(const Point2& u, const Point2& v) const
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
 private:
  /// \brief Top of y range.
  CoordType threshold;

  friend class ::TopCliptest;
};

/// \brief Helper to clip points to a given range.
class BottomClip
{
 public:
  /// Constructor
  ///
  /// @param t bottom of y range
  BottomClip(CoordType t) : threshold(t) { }
  
  /// \brief Check a point is outside this clip.
  ///
  /// @param p point to be checked.
  /// @return true if p is outside the clip.
  bool inside(const Point2& p) const
  {
    return p.y() < threshold;
  }

  /// \brief Determine the point where a line crosses this clip.
  ///
  /// @param u one of of a line that crosses this clip
  /// @param v one of of a line that crosses this clip
  /// @return a point where the line cross this clip.
  Point2 clip(const Point2& u, const Point2& v) const
  {
    auto dy = v.y() - u.y();
    auto dx = v.x() - u.x();
    assert(!isZero(dy));
    
    auto t = (u.y() - threshold) / -dy;
    return Point2(u.x() + t * dx, threshold);
  }
 private:
  /// \brief Bottom of y range.
  CoordType threshold;

  friend class ::BottomCliptest;
};

/// \brief Helper to clip points to a given range.
class LeftClip
{
 public:
  /// Constructor
  ///
  /// @param t left of x range.
  LeftClip(CoordType t) : threshold(t) { }
  
  /// \brief Check a point is outside this clip.
  ///
  /// @param p point to be checked.
  /// @return true if p is outside the clip.
  bool inside(const Point2& p) const
  {
    return p.x() >= threshold;
  }

  /// \brief Determine the point where a line crosses this clip.
  ///
  /// @param u one of of a line that crosses this clip
  /// @param v one of of a line that crosses this clip
  /// @return a point where the line cross this clip.
  Point2 clip(const Point2& u, const Point2& v) const
  {
    auto dy = v.y() - u.y();
    auto dx = v.x() - u.x();
    
    // shouldn't every happen
    assert(!isZero(dx));
    
    auto t = (threshold - u.x()) / dx;
    return Point2(threshold, u.y() + t * dy);
  }
 private:
  /// \brief Left of x range.
  CoordType threshold;

  friend class ::LeftCliptest;
};

/// \brief Helper to clip points to a given range.
class RightClip
{
 public:
  /// Constructor
  ///
  /// @param t right of x range.
  RightClip(CoordType t) : threshold(t) { }
    
  /// \brief Check a point is outside this clip.
  ///
  /// @param p point to be checked.
  /// @return true if p is outside the clip.
  bool inside(const Point2& p) const
  {
    return p.x() < threshold;
  }

  /// \brief Determine the point where a line crosses this clip.
  ///
  /// @param u one of of a line that crosses this clip
  /// @param v one of of a line that crosses this clip
  /// @return a point where the line cross this clip.
  Point2 clip(const Point2& u, const Point2& v) const
  {
    auto dy = v.y() - u.y();
    auto dx = v.x() - u.x();
    
    // shouldn't every happen
    assert(!isZero(dx));
    
    auto t = (u.x() - threshold) / -dx;
    return Point2(threshold, u.y() + t * dy);
  }
 private:
  /// \brief Right of x range.
  CoordType threshold;

  friend class ::RightCliptest;
};

} // of namespace
