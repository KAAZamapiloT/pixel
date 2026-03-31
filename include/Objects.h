
/**
 * @file Objects.h
 * @brief Defines Basic component for holding data for arendering a scene
 */

#pragma once

#include"Math_Utils.h"
#include<array>
#include <cstdint>
#include <initializer_list>
#include <vector>
#include <memory>
#include<iostream>

/// Defines data for a object in a spcae///
/**
 * @struct Transform
 * @brief Define Data about peresence of a objecct in space
 */
struct Transform{
   Vec3f position;
   Vec3f scale;
   quat rotation;

    Vec3f pivot;
    Mat4f GetTRSMatrix() const {
      return Math::ScaleRotateTranslateMatrix3D(scale,rotation,
          position);
    }

};

/**
 * @struct Mesh
 * @brief Defines how a object is stored
 */
struct Mesh {
    std::vector<Vec3f> vertices;
    std::vector<uint32_t> indices;
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


namespace MeshFactory {

Mesh CreateCube(float h) {
    Mesh Kube;
    Kube.vertices = {
        {-h,-h,-h}, { h,-h,-h}, { h, h,-h}, {-h, h,-h},
        {-h,-h, h}, { h,-h, h}, { h, h, h}, {-h, h, h}
    };
    Kube.indices = {
        0,1,2,0,2,3,
        4,6,5,4,7,6,
        0,3,7,0,7,4,
        1,5,6,1,6,2,
        3,2,6,3,6,7,
        0,4,5,0,5,1
    };
    return Kube;
}

Mesh CreateSphere(float radius, int slices, int stacks) {
    Mesh sphere;
    for (int i = 0; i <= stacks; i++) {
           float phi = M_PI * i / stacks;

           for (int j = 0; j <= slices; j++) {
               float theta = 2 * M_PI * j / slices;

               float x = radius * sin(phi) * cos(theta);
               float y = radius * cos(phi);
               float z = radius * sin(phi) * sin(theta);

               sphere.vertices.push_back({x, y, z});
           }
       }

       // indices
       for (int i = 0; i < stacks; i++) {
           for (int j = 0; j < slices; j++) {

               int first  = i * (slices + 1) + j;
               int second = first + slices + 1;

               // triangle 1
               sphere.indices.push_back(first);
               sphere.indices.push_back(second);
               sphere.indices.push_back(first + 1);

               // triangle 2
               sphere.indices.push_back(second);
               sphere.indices.push_back(second + 1);
               sphere.indices.push_back(first + 1);
           }
       }

       return sphere;
}

}

struct Material {
    INV::Vec3<uint8_t> color;
    INV::Vec3<uint8_t>(*shader)(INV::Vec3<float>)=nullptr;

}typedef Material;

class Entity {
public:
    Mesh mesh;
    Transform transform;

    Entity(const Mesh& m) : mesh(m) {}


};
