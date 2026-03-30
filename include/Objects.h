
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
};
