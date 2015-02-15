// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Damien McGinnes

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <dymaxion/Intersect.h>
#include <dymaxion/Segment.h>
#include <dymaxion/tuple_vector.h>
#include <dymaxion/wfmath_traits.h>

namespace dymaxion {
//floor and ceil functions that return d-1 and d+1
//respectively if d is integral
static inline float gridceil(float d) 
{
    float c = std::ceil(d);
    return (c==d) ? c+1.0f : c;
}

static inline float gridfloor(float d) 
{
    float c = std::floor(d);
    return (c==d) ? c-1.0f : c;
}

//check intersection of an axis-aligned box with the terrain
bool Intersect(const Terrain &t, const WFMath::AxisBox<3> &bbox)
{
    float max, min=bbox.lowCorner()[2];
    auto const res = t.getResolution();
    auto const spacing = t.getSpacing();

    //determine which segments are involved
    //usually will just be one
    int xlow  = std::lrint(std::floor(bbox.lowCorner()[0] / spacing));
    int xhigh = std::lrint(gridceil(bbox.highCorner()[0] / spacing));
    int ylow  = std::lrint(std::floor(bbox.lowCorner()[1] / spacing));
    int yhigh = std::lrint(gridceil(bbox.highCorner()[1] / spacing));

    //loop across all tiles covered by this bbox
    for (int x = xlow; x < xhigh; x++) {
        for (int y = ylow; y < yhigh; y++) {
            //check the bbox against the extent of each tile
            //as an early rejection
            auto *thisSeg=t.getSegment(x,y);

            if (thisSeg)
                max=thisSeg->getMax();
            else
                max=Terrain::defaultLevel;

            if (max > min) {
                //entity bbox overlaps with the extents of this tile
                //now check each tile point covered by the entity bbox
                
                //clip the points to be tested against the bbox
                int min_x = std::lrint(floor(bbox.lowCorner()[0] - (x * spacing)));
                if (min_x < 0) min_x = 0;

                int max_x = std::lrint(gridceil(bbox.highCorner()[0] - (x * spacing)));
                if (max_x > res) min_x = res;
                
                int min_y = std::lrint(std::floor(bbox.lowCorner()[1] - (y * spacing)));
                if (min_y < 0) min_y = 0;

                int max_y = std::lrint(gridceil(bbox.highCorner()[1] - (y * spacing)));
                if (max_y > res) min_y = res;

                //loop over each point and see if it is greater than the minimum
                //of the bbox. If all points are below, the the bbox does NOT
                //intersect. If a single point is above, then the bbox MIGHT 
                //intersect.
                for (int xpt = min_x; xpt <= max_x; xpt++) {
                    for (int ypt = min_y; ypt <= max_y; ypt++) {
                        if (thisSeg) { 
                            if (thisSeg->get(xpt,ypt) > min) return true;
                        }
                        else if (Terrain::defaultLevel > min) return true;
                    }
                }
            }
        }
    }
    return false;
}

static float HOT(const Terrain &t, const WFMath::Point<3> &pt, float & h) 
{
    std::tuple<float,float,float> normal; 
    float terrHeight;
    if (!t.getHeightAndNormal(pt[0], pt[1], terrHeight, normal)) {
        return false;
    }

    h = (pt[2] - terrHeight);
    return true;
}

bool Intersect(const Terrain &t, const WFMath::Point<3> &pt) 
{
    float h;
    return HOT(t, pt, h) && h <= 0.0;
}

//helper function for ray terrain intersection
static bool cellIntersect(float h1, float h2, float h3, float h4,
                          float X, float Y, 
                          const std::tuple<float,float,float> &nDir, float dirLen,
                          const WFMath::Point<3> &sPt,
                          WFMath::Point<3> &intersection,
                          std::tuple<float,float,float> &normal, float &par)
{
    //ray plane intersection roughly using the following:
    //parametric ray eqn:  p=po + par V
    //plane eqn: p dot N + d = 0
    //
    //intersection:
    // -par = (po dot N + d ) / (V dot N)
    // 
    //
    // effectively we calculate the ray parametric variable for the
    // intersection of the plane corresponding to each triangle
    // then clip them by endpints of the ray, and by the sides of the square
    // and by the diagonal
    //
    // if they both still intersect, then we choose the earlier intersection
    
   
    //intersection points for top and bottom triangles
    WFMath::Point<3> topInt, botInt;
    
    //point to use in plane equation for both triangles
    std::tuple<float,float,float> p0 = std::tuple<float,float,float>(X, Y, h1);

    // square is broken into two triangles
    // top triangle |/
    bool topIntersected = false;
    std::tuple<float,float,float> topNormal(h2-h3, h1-h2, 1.0);
    normalise_i(topNormal);
    float t = dot(nDir, topNormal);

    decltype(t) topP=0.0;

    if ((t > 1e-7) || (t < -1e-7)) {
        topP = - (dot(std::tuple<float,float,float>(sPt[0], sPt[1], sPt[2]), topNormal) 
               - dot(topNormal, p0)) / t; 
        topInt = translate(sPt, scale(nDir, topP));
        //check the intersection is inside the triangle, and within the ray extents
        if ((topP <= dirLen) && (topP > 0.0) &&
            (topInt[0] >= X ) && (topInt[1] <= Y + 1 ) &&
            ((topInt[0] - topInt[1]) <= (X - Y)) ) {
                topIntersected=true;
        }
    }

    // bottom triangle /|
    bool botIntersected = false;
    std::tuple<float,float,float> botNormal(h1-h4, h4-h3, 1.0);
    normalise_i(botNormal);
    auto b = dot(nDir, botNormal);
    decltype(b) botP=0.0;

    if ((b > 1e-7) || (b < -1e-7)) {
        botP = - (dot(std::tuple<float,float,float>(sPt[0], sPt[1], sPt[2]), botNormal) 
                  - dot(botNormal, p0)) / b; 
        botInt = translate(sPt, scale(nDir, botP));
        //check the intersection is inside the triangle, and within the ray extents
        if ((botP <= dirLen) && (botP > 0.0) &&
            (botInt[0] <= X + 1 ) && (botInt[1] >= Y ) && 
            ((botInt[0] - botInt[1]) >= (X - Y)) ) {
                botIntersected = true;
        }
    }

    if (topIntersected && botIntersected) { //intersection with both
        if (botP <= topP) {
            intersection = botInt;
            normal = botNormal; 
            par=botP/dirLen;
            if (botP == topP) {
                add_i(normal, topNormal);
                normalise_i(normal);
            }
            return true;    
        }
        else {
            intersection = topInt;
            normal = topNormal; 
            par=topP/dirLen;
            return true;
        }
    }
    else if (topIntersected) { //intersection with top
        intersection = topInt;
        normal = topNormal; 
        par=topP/dirLen;
        return true;
    }
    else if (botIntersected) { //intersection with bot
        intersection = botInt;
        normal = botNormal; 
        par=botP/dirLen;
        return true;
    }

    return false;
}

//Intersection of ray with terrain
//
//returns true on successful intersection
//ray is represented by a start point (sPt)
//and a direction vector (dir). The length of dir is
//used as the length of the ray. (ie not an infinite ray)
//intersection and normal are filled in on a successful result.
//par is the distance along the ray where intersection occurs
//0.0 == start, 1.0 == end.

bool Intersect(const Terrain &t,
               const WFMath::Point<3> &sPt,
               const std::tuple<float,float,float>& dir,
               WFMath::Point<3> &intersection,
               std::tuple<float,float,float> &normal, float &par)
{
    //FIXME early reject using segment max
    //FIXME handle height point getting in a more optimal way
    //FIXME early reject for vertical ray


    // check if startpoint is below ground
    float hot;
    if (HOT(t, sPt, hot) && hot < 0.0) return true;
    
    float paraX=0.0, paraY=0.0; //used to store the parametric gap between grid crossings 
    float pX, pY; //the accumulators for the parametrics as we traverse the ray
    float h1,h2,h3,h4,height;

    WFMath::Point<3> last(sPt), next(sPt);
    std::tuple<float,float,float> nDir(dir);
    normalise_i(nDir);
    auto dirLen = mag(dir);
    
    //work out where the ray first crosses an X grid line
    if (std::get<0>(dir) != 0.0f)
    {
        paraX = 1.0f/std::get<0>(dir);
        float crossX = (std::get<0>(dir) > 0.0f) ?
                        gridceil(last[0]) :
                        gridfloor(last[0]);
        pX = (crossX - last[0]) * paraX;
        pX = std::min(pX, 1.0f);
    }
    else
    { //parallel: never crosses
        pX = 1.0f;
    }

    //work out where the ray first crosses a Y grid line
    if (std::get<1>(dir) != 0.0f) {
        paraY = 1.0f / std::get<1>(dir);
        float crossY = (std::get<1>(dir) > 0.0f) ?
                        gridceil(last[1]) :
                        gridfloor(last[1]);
        pY = (crossY - sPt[1]) * paraY;
        pY = std::min(pY, 1.0f);
    }
    else
    { //parallel: never crosses
        pY = 1.0f;
    } 

    //ensure we traverse the ray forwards 
    paraX = std::abs(paraX);
    paraY = std::abs(paraY);

    bool endpoint = false;
    //check each candidate tile for an intersection
    while (1) {
        last = next;
        if (pX < pY) { // cross x grid line first
            next = translate(sPt, scale(dir, pX));
            pX += paraX; // set x accumulator to current p
        }
        else { //cross y grid line first
            next = translate(sPt, scale(dir, pY));
            if (pX == pY) {
                pX += paraX; //unusual case where ray crosses corner
            }
            pY += paraY; // set y accumulator to current p
        }

        //FIXME these gets could be optimized a bit
        float x= (std::get<0>(dir) > 0) ? std::floor(last[0])
                                        : std::floor(next[0]);
        float y= (std::get<1>(dir) > 0) ? std::floor(last[1])
                                        : std::floor(next[1]);
        h1 = t.get(x, y);
        h2 = t.get(x, y+1);
        h3 = t.get(x+1, y+1);
        h4 = t.get(x+1, y);
        height = std::max( std::max(h1, h2), 
                           std::max(h3, h4)); 
        
        if ( (last[2] < height) || (next[2] < height) ) {
            // possible intersect with this tile
            if (cellIntersect(h1, h2, h3, h4, x, y, nDir, dirLen, sPt,
                              intersection, normal, par)) {
                return true;
            }
        }

        if ((pX >= 1.0f) && (pY >= 1.0f)) {
            if (endpoint) {
                break;
            }
            else endpoint = true;
        }
    }

    return false;
}

} // namespace dymaxion
