// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch, Damien McGinnes

#ifndef DYMAXION_TERRAIN_H
#define DYMAXION_TERRAIN_H

#include <dymaxion/dymaxion.h>
#include <dymaxion/BasePoint.h>

#include <wfmath/vector.h>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <map>
#include <set>
#include <list>
#include <cmath>

namespace dymaxion {

class Segment;
class Shader;
class TerrainMod;
class Area;
class Effector;

/// \brief Class storing centrally all data about an instance of some terrain.
///
/// All the data includes:
/// - Base Points which define the terrain.
/// - Segment data which is the actual heightfields.
/// - Shaders which control how the surface appears.
/// - Surfaces which are generated by the Shaders (delegated to Segment).
/// - TerrainMods which modify the terrain data (delegated to Segment).
class Terrain {
  public:
    /// \brief Bounding box

    typedef boost::geometry::model::d2::point_xy<
        float, boost::geometry::cs::cartesian> point;
    typedef boost::geometry::model::box<point> box;

    /// \brief STL map to store sparse array of BasePoints.
    typedef std::map<int, BasePoint> Pointcolumn;
    /// \brief STL map to store sparse array of Segment pointers.
    typedef std::map<int, Segment *> Segmentcolumn;

    /// \brief STL map to store sparse array of BasePoint columns.
    typedef std::map<int, Pointcolumn > Pointstore;
    /// \brief STL map to store sparse array of Segment pointer columns.
    typedef std::map<int, Segmentcolumn > Segmentstore;

    /// \brief STL map to store sparse array of Shader pointers.
    typedef std::map<int, const Shader *> Shaderstore;

    /// \brief STL map to store terrain effectors.
    typedef std::map<const Effector *, box> Effectorstore;

    /// \brief value provided for no flags set.
    static const unsigned int DEFAULT = 0x0000;
    /// \brief set if shaders are going to be used on this terrain.
    static const unsigned int SHADED = 0x0001;
    // More options go here as bit flags, and below should be a private
    // test function
  private:
    /// \brief Bitset of option flags controlling various aspects of terrain.
    const unsigned int m_options;
    /// \brief BasePoint resolution, or distance between adjacent points.
    const int m_res;
    /// \brief BasePoints spacing, same as m_res in float form for efficiency
    const float m_spacing;

    /// \brief 2D spatial container with all BasePoints.
    Pointstore m_basePoints;
    /// \brief 2D spatial container with pointers to all Segments.
    Segmentstore m_segments;
    /// \brief List of shaders to be applied to terrain.
    Shaderstore m_shaders;
  
    /// \brief List of effectors be applied to the terrain.
    Effectorstore m_effectors;
  
    void addSurfaces(Segment &);
    void shadeSurfaces(Segment &);

    void addEffector(Effector const * effector);

    /// \brief Updates the terrain affected by an Effector.
    ///
    /// Call this when an already added terrain effector has changed.
    ///
    /// @param effector The terrain effector which has changed.
    /// @return The area affected by the terrain effector before it was updated.
    box updateEffector(Effector const * effector);
    void removeEffector(Effector const * effector);
    
    /// \brief Determine whether this terrain object has shading enabled.
    ///
    /// @return true if shading is enabled, false otherwise.
    bool isShaded() const {
        return ((m_options & SHADED) == SHADED);
    }
  public:
    /// \brief Height value used when no data is available.
    static constexpr float defaultLevel = 8.f;

    explicit Terrain(unsigned int options = DEFAULT,
                     unsigned int resolution = defaultResolution);
    ~Terrain();

    float get(float x, float y) const;
    bool getHeightAndNormal(float x, float y, float&, WFMath::Vector<3>&) const;

    bool getBasePoint(int x, int y, BasePoint& z) const;
    void setBasePoint(int x, int y, const BasePoint& z);

    /// \brief Set the height of the basepoint at x,y to z.
    void setBasePoint(int x, int y, float z) {
        BasePoint bp(z);
        setBasePoint(x, y, bp);
    }

    /// \brief Get a pointer to the segment which contains the coord x,y
    ///
    /// @return zero if no segment is defined at that location, or a pointer
    /// to a Segment otherwise.
    Segment * getSegment(float x, float y) const {
        int ix = (int)floor(x / m_spacing);
        int iy = (int)floor(y / m_spacing);
        return getSegment(ix, iy);
    }

    Segment * getSegment(int x, int y) const;

    /// \brief Accessor for base point resolution.
    int getResolution() const {
        return m_res;
    }

    /// \brief Accessor for base point spacing.
    float getSpacing() const {
        return m_spacing;
    }

    /// \brief Accessor for 2D sparse array of Segment pointers.
    const Segmentstore & getTerrain() const {
        return m_segments;
    }

    /// \brief Accessor for 2D sparse array of BasePoint objects.
    const Pointstore & getPoints() const {
        return m_basePoints;
    }
    
    /// \brief Accessor for list of Shader pointers.
    const Shaderstore & getShaders() const {
        return m_shaders;
    }

    /// \brief Add a new Shader to the list for this terrain.
    void addShader(Shader const * t, int id);
    void removeShader(Shader const * t, int id);
    
    void addMod(TerrainMod const * mod);

    /// \brief Updates the terrain affected by a mod.
    ///
    /// Call this when an already added terrain mod has changed.
    ///
    /// @param mod The terrain mod which has changed.
    /// @return The area affected by the terrain mod before it was updated.
    box updateMod(TerrainMod const * mod);
    void removeMod(TerrainMod const * mod);
    
    void addArea(Area const * a);

    /// \brief Updates the terrain affected by an area.
    ///
    /// Call this when an already added terrain area has changed.
    ///
    /// @param a The terrain area which has changed.
    /// @return The area affected by the terrain area before it was updated.
    box updateArea(Area const * a);
    void removeArea(Area const * a);
};

} // namespace dymaxion

#endif // DYMAXION_TERRAIN_H
