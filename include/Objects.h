
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

class Example{
public:
    void Draw(){
    // r-> submit Data()
    // r->Draw Data()
    }

    TriangleArray CreateTestTriangle() {
        TriangleArray obj;

        Triangle t;
        t.vertices = {
            Vec3f(-0.5f, -0.5f, -2.0f),
                Vec3f( 0.5f, -0.5f, -2.0f),
                Vec3f( 0.0f,  0.5f, -2.0f)
        };

        obj.triangles.push_back(t);
        obj.colors.push_back({255, 0, 0}); // red

        Transform tr;
        tr.position = {0,0,0};
        tr.scale    = {1,1,1};
        tr.rotation = {0,0,0};

        obj.Transforms.push_back(tr);

        return obj;
    }

  private:
std::vector<TriangleArray> Tarray;
};
