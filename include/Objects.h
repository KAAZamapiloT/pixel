
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

// creatng a triangle class giving power to traingle indvidualy
class Trig{
public:
    void Rotate(float value, const Vec3f& axis){
        Mat3f rotationMatrix = Math::Rotation3D( value,axis);
        MultiplyEachPointWithMatrix3(rotationMatrix);
    }
    void Translate(const Vec3f& translation){
        Mat4f translationMatrix = Math::ScaleRotateTranslateMatrix3D(0,INV::Quat<float>(1,0,0,0),
            translation.x,translation.y,translation.z);
        MultiplyEachPointWithMatrix4(translationMatrix);
    }
    void MultiplyEachPointWithMatrix3(const Mat3f& matrix){
        for (auto& vertex : k.vertices) {
            vertex = matrix * vertex;
        }
    }
    void MultiplyEachPointWithMatrix4(const Mat4f& matrix){
       Vec4f moodle=Vec4f(k.vertices[0],1);
       Vec4f moodle1=Vec4f(k.vertices[1],1);
       Vec4f moodle2=Vec4f(k.vertices[2],1);
       moodle = matrix * moodle;
       moodle1=matrix * moodle1;
       moodle2=matrix * moodle2;
       k.vertices[0]=moodle.xyz()/moodle.w;
       k.vertices[1]=moodle1.xyz()/moodle1.w;
       k.vertices[2]=moodle2.xyz()/moodle2.w;
    }
private:
struct Triangle k;
struct Transform Cords;
};


class Cube{
public:
Cube(Vec3f p1 , Vec3f p2,Vec3f p3,Vec3f p4,Vec3f p5,Vec3f p6,Vec3f p7,Vec3f p8){
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    vertices[3] = p4;
    vertices[4] = p5;
    vertices[5] = p6;
    vertices[6] = p7;
    vertices[7] = p8;
}
Cube(std::initializer_list<Vec3f> points) {
    if(points.size()!=8){
        std::cerr << "Cube must have exactly 8 vertices.\n";
        return;
    }
    std::copy(points.begin(), points.end(), vertices.begin());
}
std::array<Vec3f,8> GetVertices(){
    return vertices;
}


private:
std::array<Vec3f,8> vertices;
};
