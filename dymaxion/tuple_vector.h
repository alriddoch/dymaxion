// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2015 Alistair Riddoch

#ifndef DYMAXION_TUPLE_VECTOR_H
#define DYMAXION_TUPLE_VECTOR_H

namespace dymaxion {

static inline void shift_i(std::tuple<float, float, float> & vec,
                           float x, float y, float z)
{
  std::get<0>(vec) += x;
  std::get<1>(vec) += y;
  std::get<2>(vec) += z;
}

static inline float sqr(float val)
{
  return val * val;
}

static inline float mag(std::tuple<float, float, float> const & vec)
{
  return std::sqrt(sqr(std::get<0>(vec)) +
                   sqr(std::get<1>(vec)) +
                   sqr(std::get<2>(vec)));
}

static inline float sqr_mag(std::tuple<float, float, float> const & vec)
{
  return sqr(std::get<0>(vec)) +
         sqr(std::get<1>(vec)) +
         sqr(std::get<2>(vec));
}

static inline void normalise_i(std::tuple<float, float, float> & vec)
{
  float m = mag(vec);
  std::get<0>(vec) /= m;
  std::get<1>(vec) /= m;
  std::get<2>(vec) /= m;
}

static inline float scale_epsilon(float lhs, float rhs, float epsilon)
{
  int exp;
  std::frexp(std::fabs(lhs) < std::fabs(rhs) ? lhs : rhs, &exp);

  return std::ldexp(epsilon, exp);
}

static inline float scale_epsilon(std::tuple<float, float, float> const & lhs,
                                  std::tuple<float, float, float> const & rhs)
{
  float const epsilon = 30 * std::numeric_limits<float>::epsilon();

  float max1 = 0,
        max2 = 0;

  max1 = std::max(std::fabs(std::get<0>(lhs)), max1);
  max2 = std::max(std::fabs(std::get<0>(rhs)), max2);
  max1 = std::max(std::fabs(std::get<1>(lhs)), max1);
  max2 = std::max(std::fabs(std::get<1>(rhs)), max2);
  max1 = std::max(std::fabs(std::get<2>(lhs)), max1);
  max2 = std::max(std::fabs(std::get<2>(rhs)), max2);

  return scale_epsilon(max1, max2, epsilon);
}

static inline float dot(std::tuple<float, float, float> const & lhs,
                        std::tuple<float, float, float> const & rhs)
{
  float delta = scale_epsilon(lhs, rhs);

  float ans = std::get<0>(lhs) * std::get<0>(rhs) +
              std::get<1>(lhs) * std::get<1>(rhs) +
              std::get<2>(lhs) * std::get<2>(rhs);

  return (std::fabs(ans) >= delta) ? ans : 0;
}

static inline std::tuple<float, float, float> scale(
  std::tuple<float, float, float> const & vec,
  float scale_factor)
{
  return std::tuple<float, float, float>(
           std::get<0>(vec) * scale_factor,
           std::get<1>(vec) * scale_factor,
           std::get<2>(vec) * scale_factor
           );
}

template <class Point>
inline Point translate(Point const & p,
                       std::tuple<float, float, float> const & v)
{
  return Point(
           boost::geometry::traits::access<Point, 0>::get(p) + std::get<0>(v),
           boost::geometry::traits::access<Point, 1>::get(p) + std::get<1>(v),
           boost::geometry::traits::access<Point, 2>::get(p) + std::get<2>(v)
           );
}

template <class Point>
inline void translate_i(Point & p,
                        std::tuple<float, float, float> const & v)
{
  boost::geometry::traits::access<Point, 0>::set(p,
                                                 boost::geometry::traits::access<Point, 0>::get(p) + std::get<0>(v));
  boost::geometry::traits::access<Point, 1>::set(p,
                                                 boost::geometry::traits::access<Point, 1>::get(p) + std::get<1>(v));
  boost::geometry::traits::access<Point, 2>::set(p,
                                                 boost::geometry::traits::access<Point, 2>::get(p) + std::get<2>(v));
}

inline void add_i(std::tuple<float, float, float> & lhs,
                  std::tuple<float, float, float> const & rhs)
{
  std::get<0>(lhs) += std::get<0>(rhs);
  std::get<1>(lhs) += std::get<1>(rhs);
  std::get<2>(lhs) += std::get<2>(rhs);
}

inline std::tuple<float, float, float> add(
  std::tuple<float, float, float> const & lhs,
  std::tuple<float, float, float> const & rhs
  )
{
  return std::tuple<float, float, float>(
           std::get<0>(lhs) + std::get<0>(rhs),
           std::get<1>(lhs) + std::get<1>(rhs),
           std::get<2>(lhs) + std::get<2>(rhs)
           );
}

} // namespace dymaxion

#endif // DYMAXION_TUPLE_VECTOR_H
