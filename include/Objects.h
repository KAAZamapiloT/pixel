
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

//triangles will store locations locally and Trabnsoforms will be a worlld scale varient of them
// creatng a triangle class giving power to traingle indvidualy
class Cube{
public:
Cube(Vec3f p1 , Vec3f p2,Vec3f p3,Vec3f p4,Vec3f p5,Vec3f p6,Vec3f p7,Vec3f p8){
    CubeMesh.vertices[0] = p1;
    CubeMesh.vertices[1] = p2;
    CubeMesh.vertices[2] = p3;
    CubeMesh.vertices[3] = p4;
    CubeMesh.vertices[4] = p5;
    CubeMesh.vertices[5] = p6;
    CubeMesh.vertices[6] = p7;
    CubeMesh.vertices[7] = p8;
}

Cube(float size){
    CubeMesh = CreateCube(size);
}
Cube(std::initializer_list<Vec3f> points) {
    if(points.size()!=8){
        std::cerr << "Cube must have exactly 8 vertices.\n";
        return;
    }
    std::copy(points.begin(), points.end(), CubeMesh.vertices.begin());
}
Cube(std::vector<Vec3f> points) {
    if(points.size()!=8){
        std::cerr << "Cube must have exactly 8 vertices.\n";
        return;
    }
    std::copy(points.begin(), points.end(), CubeMesh.vertices.begin());
}

std::vector<Vec3f> GetVertices(){
    return CubeMesh.vertices;
}
void Rotate(const quat & rotation) {
    for (auto& vertex : CubeMesh.vertices) {
        vertex = rotation.rotate(vertex);
    }
}
void Rotate(float yaw,float pitch,float roll) {
    quat rotation = quat(pitch, Vec3f(1, 0, 0)) * quat(yaw, Vec3f(0, 1, 0)) * quat(roll, Vec3f(0, 0, 1));
    for (auto& vertex : CubeMesh.vertices) {
        vertex = rotation.rotate(vertex);
    }
}
void Translate(const Vec3f& translation) {
    for (auto& vertex : CubeMesh.vertices) {
        vertex += translation;
    }
}

void MultiplyEachPointWithMatrix4(const Mat4f& matrix){
    for (auto& vertex : CubeMesh.vertices) {
        Vec4f moodle = Vec4f(vertex, 1);
        moodle = matrix * moodle;
        vertex = moodle.xyz() / moodle.w;
    }
}
void MultiplyEachPointWithMatrix3(const Mat3f& matrix){
    for (auto& vertex : CubeMesh.vertices) {
        Vec3f moodle = matrix * vertex;
        vertex = moodle;
    }
}
Mesh CreateCube(float h){
    struct Mesh Kube;
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
private:
struct Mesh CubeMesh;
};
