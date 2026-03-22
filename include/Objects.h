
/**
 * @file Objects.h
 * @brief Defines Basic component for holding data for arendering a scene
 */

#pragma once

#include"Math_Utils.h"
#include<array>
#include <cstdint>


/// Defines data for a object in a spcae///
/**
 * @struct Transform
 * @brief Define Data about peresence of a objecct in space
 */
struct Transform{
   Vec3f position;
   Vec3f scale;
   Vec3f rotation;

    Vec3f pivot;//optional thing

};

/**
 * @struct Triangle
 * @brief Define  a triangle in space
 */
struct Triangle{
     std::array<Vec3f, 3> vertices;
};
/**
 * @class TriangleArray
 * @breif Define a Array of Traingles and Transforms
 */
class TriangleArray{
public:
    std::vector<Triangle> triangles;
    std::vector<INV::Vec3<uint8_t>> colors;
    std::vector<struct Transform> Transforms;
};
//triangles will store locations locally and Trabnsoforms will be a worlld scale varient of them
