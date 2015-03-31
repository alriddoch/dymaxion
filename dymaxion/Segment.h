// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch, Damien McGinnes

#ifndef DYMAXION_SEGMENT_H
#define DYMAXION_SEGMENT_H

#include <dymaxion/dymaxion.h>
#include <dymaxion/Matrix.h>
#include <dymaxion/BasePoint.h>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <set>
#include <map>

namespace WFMath {
class MTRand;
}

namespace dymaxion {

class Terrain;
class Surface;
class TerrainMod;
typedef std::set<TerrainMod const *> ModList;
class Area;

// This class will need to be reference counted if we want the code to
// be able to hold onto it, as currently they get deleted internally
// whenever height points are asserted.

/// \brief Class storing heightfield and other data for a single fixed size
/// square area of terrain defined by four adjacent BasePoint objects.
class Segment {
 public:
  typedef boost::geometry::model::d2::point_xy<
    float, boost::geometry::cs::cartesian> point_type;
  typedef boost::geometry::model::box<point_type> rect_type;

  typedef boost::geometry::model::point<
    float, 3, boost::geometry::cs::cartesian> point3_type;
  typedef boost::geometry::model::box<point3_type> box_type;

  /// STL map of pointers to Surface objects.
  typedef std::map<int, Surface *> Surfacestore;

  /// STL multimap of pointers to Area objects affecting this segment.
  typedef std::multimap<int, Area const *> Areastore;
 private:
  /// Distance between segments
  const unsigned int m_res;
  /// Size of segment, m_res + 1
  const unsigned int m_size;
  /// Global x reference of this segment
  const int m_xRef;
  /// Global y reference of this segment
  const int m_yRef;
  /// 2x2 matrix of points which control this segment
  Matrix<2, 2, BasePoint> m_controlPoints;
  /// Pointer to buffer containing height points
  float * m_points = 0;
  /// Pointer to buffer containing normals for height points
  float * m_normals = 0;
  /// Maximum height of any point in this segment
  float m_max = -1000000.f;
  /// Minimum height of any point in this segment
  float m_min = 1000000.0f;

  /// Store of surfaces which can be rendered on this terrain
  Surfacestore m_surfaces;

  /// Areas which intersect this segment
  Areastore m_areas;

  /// \brief List of TerrainMod objects that are applied to this Segment.
  ModList m_modList;
 public:
  explicit Segment(int x, int y, unsigned int resolution);
  ~Segment();

  /// \brief Accessor for resolution of this segment.
  unsigned int getResolution() const
  {
    return m_res;
  }

  /// \brief Accessor for array size of this segment.
  unsigned int getSize() const
  {
    return m_size;
  }

  /// \brief Accessor for Global x reference of this segment
  int getXRef() const
  {
    return m_xRef;
  }

  /// \brief Accessor for Global y reference of this segment
  int getYRef() const
  {
    return m_yRef;
  }

  /// \brief Check whether this Segment contains valid point data.
  ///
  /// @return true if this Segment is valid, false otherwise.
  bool isValid() const
  {
    return (m_points != 0);
  }

  /// \brief Set min and max height values for this Segment.
  ///
  /// This is used after construction to set the initial values, and
  /// should not be used after populate has been called.
  void setMinMax(float min, float max)
  {
    m_min = min;
    m_max = max;
  }

  void invalidate(bool points = true);

  /// \brief Set the BasePoint data for one of the four that define this
  /// Segment.
  ///
  /// @param x relative x coord of base point. Must be 0 or 1.
  /// @param y relative y coord of base point. Must be 0 or 1.
  /// @param bp BasePoint data to be used.
  void setCornerPoint(unsigned int x, unsigned int y, BasePoint const & bp)
  {
    m_controlPoints(x, y) = bp;
    invalidate();
  }

  /// \brief Accessor for 2D matrix of base points.
  const Matrix<2, 2, BasePoint> & getControlPoints() const
  {
    return m_controlPoints;
  }

  /// \brief Accessor for modifying 2D matrix of base points.
  Matrix<2, 2, BasePoint> & getControlPoints()
  {
    return m_controlPoints;
  }

  /// \brief Accessor for list of attached Surface objects.
  Surfacestore const & getSurfaces() const
  {
    return m_surfaces;
  }

  /// \brief Accessor for modifying list of attached Surface objects.
  Surfacestore & getSurfaces()
  {
    return m_surfaces;
  }

  /// \brief Accessor for buffer containing height points.
  float const * getPoints() const
  {
    return m_points;
  }

  /// \brief Accessor for write access to buffer containing height points.
  float * getPoints()
  {
    return m_points;
  }

  /// \brief Accessor for buffer containing surface normals.
  float const * getNormals() const
  {
    return m_normals;
  }

  /// \brief Accessor for write access to buffer containing surface normals.
  float * getNormals()
  {
    return m_normals;
  }

  /// \brief Get the height at a relative integer position in the Segment.
  float get(int x, int y) const
  {
    return m_points[y * (m_res + 1) + x];
  }

  void getHeightAndNormal(float x, float y, float &h,
                          std::tuple<float, float, float> & normal) const;
  bool clipToSegment(rect_type const & bbox,
                     unsigned int &lx,
                     unsigned int &hx,
                     unsigned int &ly,
                     unsigned int &hy) const;


  void populate();
  void populateNormals();
  void populateSurfaces();

  /// \brief Accessor for the maximum height value in this Segment.
  float getMax() const
  {
    return m_max;
  }

  /// \brief Accessor for the minimum height value in this Segment.
  float getMin() const
  {
    return m_min;
  }

  /// \brief The 2d area covered by this segment
  rect_type getRect() const;

  /// \brief The 3d box covered by this segment
  box_type getBox() const;

  int addMod(TerrainMod const *t);
  int updateMod(TerrainMod const *t);
  int removeMod(TerrainMod const *t);
  void clearMods();

  /// \brief Accessor for multimap of Area objects.
  Areastore const & getAreas() const
  {
    return m_areas;
  }

  ModList const & getMods() const
  {
    return m_modList;
  }

  int addArea(Area const * a);
  int updateArea(Area const * a);
  int removeArea(Area const * a);

 private:
  void checkMaxMin(float h);

  void fill1d(BasePoint const & l, BasePoint const &h, float *array) const;

  void fill2d(BasePoint const & p1, BasePoint const & p2,
              BasePoint const & p3, BasePoint const & p4);

  float qRMD(WFMath::MTRand & rng, float nn, float fn, float ff, float nf,
             float roughness, float falloff, float depth) const;

  void applyMod(TerrainMod const *t);

  void invalidateSurfaces();

};

} // namespace dymaxion

#endif // DYMAXION_SEGMENT_H
