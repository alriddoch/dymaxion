// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch, Damien McGinnes

#ifndef DYMAXION_INTERP_H
#define DYMAXION_INTERP_H

class LinInterptest;
class QuadInterptest;

namespace dymaxion {

/// \brief Helper to interpolate on a line.
///
/// The line specified is of integer length, and the position specified
/// as an integer. A check is included to avoid calculation if the value
/// at each end is the same.
class LinInterp {
 private:
  /// The length of the line.
  float m_size;
  /// Flag indicating that both points have the same value.
  bool noCalc = false;
 public:
  /// Values at the two ends.
  float ep1, ep2;
  /// \brief Determine the interpolated value along the line.
  inline float calc(float loc)
  {
    return ((noCalc) ? ep1 :
            ((m_size-loc) * ep1 + loc * ep2));
  }
  /// \brief Constructor
  ///
  /// @param size length of the line.
  /// @param l value at one end of the line.
  /// @param h value at one end of the line.
  LinInterp(float size,float l, float h) : m_size(size),
            ep1(l/size), ep2(h/size)
  {
    if (l==h) {
      ep1 = l;
      noCalc=true;
    }
  }

  friend class ::LinInterptest;
};

/// \brief Helper to interpolate in a quad.
///
/// The quad specified is assumed to be square of integer size, and
/// the position specified for interpolation is specified in integer
/// form. A check is included to avoid calculation if the value of each
/// corner is the same.
class QuadInterp {
 private:
  /// The length of one side of the square quad.
  float m_size;
  /// Flag indicating that all points have the same value.
  bool noCalc = false;
 public:
  /// Values at the four corners.
  float ep1, ep2, ep3, ep4;
  /// \brief Determine the interpolated value within the quad.
  inline float calc(float locX, float locY)
  {
    return  ((noCalc) ? ep1 :
             (( ep1*(m_size-locX) + ep2 * locX) * (m_size-locY) +
              ( ep4*(m_size-locX) + ep3 * locX) * (locY) ) / m_size );
  }
  /// \brief Constructor
  ///
  /// @param size length of one side of the square quad.
  /// @param e1 value at one corner of the square quad.
  /// @param e2 value at one corner of the square quad.
  /// @param e3 value at one corner of the square quad.
  /// @param e4 value at one corner of the square quad.
  QuadInterp(float size,float e1, float e2, float e3, float e4)
      : m_size(size), ep1(e1/size), ep2(e2/size), ep3(e3/size), ep4(e4/size)
  {
    if ((e1==e2) && (e3==e4) && (e2==e3)) {
      ep1 = e1;
      noCalc=true;
    }
  }

  friend class ::QuadInterptest;
};

} // namespace dymaxion

#endif // DYMAXION_INTERP_H
