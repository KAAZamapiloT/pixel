#pragma once
#include <locale>
#include<vector>
#include<cstdint>
#include"string"
namespace INV{
// collection of 3 vals
template <typename T>
class Vec3{
    public:
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(const Vec3& other) const {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }

    Vec3 operator/(const Vec3& other) const {
        return Vec3(x / other.x, y / other.y, z / other.z);
    }

    Vec3 operator%(const Vec3& other) const {
        return Vec3(x % other.x, y % other.y, z % other.z);
    }

    Vec3 Cross(const Vec3& other) const {
        return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    Vec3 Dot(const Vec3& other) const {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }
    double magnitude_squared(){
        return x*x+y*y+z*z;
    }
    T x, y, z;
};

// collection of 2 vals
template <typename T>
class Vec2{
    public:
    Vec2(T x, T y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator*(const Vec2& other) const {
        return Vec2(x * other.x, y * other.y);
    }



    Vec2 operator/(const Vec2& other) const {
        return Vec2(x / other.x, y / other.y);
    }

    Vec2 Cross(const Vec2& other) const {
        return Vec2(y * other.x - x * other.y);
    }

    T Dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }
    double magnitude_squared(){
        return x*x+y*y;
    }
    T x, y;
};

template <typename T>

class Vec4{
public:
Vec4(T x,T y,T z,T w):x(x),y(y),z(z),w(w){

}
Vec4(Vec3<T>s,T sd){
    x=s.x;
    y=s.y;
    z=s.z;
    w=sd;
}

Vec4<T> Dot(Vec4<T> other){return x*other.x+y*other.y+z*other.z+w*other.w;}

Vec4<T> Cross(Vec4<T> other){return Vec4<T>(y*other.z-z*other.y,z*other.x-x*other.z,x*other.y-y*other.x);}

double magnitude_squared(){
    return x*x+y*y+z*z+w*w;
}
  T x,y,z,w;
};

template<typename T>
class Matrix2{
public:
Matrix2(T a,T b,T c,T d):Mat{{a,b},{c,d}}{

}

Matrix2 operator+(const Matrix2& other){
    Matrix2 result;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            result.Mat[i][j]=Mat[i][j]+other.Mat[i][j];
        }
    }
    return result;
}


T Mat[2][2];
};

template<typename T>
class Matrix3{
    public:
    Matrix3(T a,T b,T c,T d,T e,T f,T g,T h,T i):Mat{{a,b,c},{d,e,f},{g,h,i}}{

    }
    Matrix3 operator+(Matrix3&other ){
        Matrix3 result;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                result.Mat[i][j]=Mat[i][j]+other.Mat[i][j];
            }
        }
        return result;
    }

    T Mat[3][3];
};

template<typename T>
class Matrix4{
public:
Matrix4(T a,T b,T c,T d,T e,T f,T g,T h,T i,T j,T k,T l,T m,T n,T o,T p):Mat{{a,b,c,d},{e,f,g,h},{i,j,k,l},{m,n,o,p}}{

}
Matrix4(T x)
        : Mat{
            {x, x, x, x},
            {x, x, x, x},
            {x, x, x, x},
            {x, x, x, x}
          }
    {}
Matrix4 operator+(Matrix4&other ){
    Matrix4 result;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            result.Mat[i][j]=Mat[i][j]+other.Mat[i][j];
        }
    }
    return result;
}

// Fov must be in radians
Matrix4 perspective(float fov, float aspect, float near, float far){
    assert(near > 0.0f);
        assert(far  > near);
        assert(aspect > 0.0f);

        float t=std::tan(fov*0.05f)
        Matrix4 m{}; // zero-initialized

           m[0][0] = 1.0f / (aspect * t);
           m[1][1] = 1.0f / t;

           m[2][2] = -(far + near) / (far - near);
           m[2][3] = -(2.0f * far * near) / (far - near);

           m[3][2] = -1.0f;
           m[3][3] = 0.0f;

           return m;
}
Matrix4 ortho(
    float left, float right,
    float bottom, float top,
    float near, float far)
{
    assert(right != left);
    assert(top   != bottom);
    assert(far   != near);

    Matrix4 m{}; // zero-initialized

    m[0][0] =  2.0f / (right - left);
    m[1][1] =  2.0f / (top - bottom);
    m[2][2] = -2.0f / (far - near);

    m[3][0] = -(right + left)   / (right - left);
    m[3][1] = -(top + bottom)   / (top - bottom);
    m[3][2] = -(far + near)     / (far - near);
    m[3][3] =  1.0f;

    return m;
}
T Mat[4][4];
};
template<typename T>
class Quat{
public:

T x,y,z,w;
};
// now i need a way to represent window
//
//



class Window{
public:
  Window(uint16_t width,uint16_t height,std::string name){
                m_width=width;
                m_height=height;
                m_name=name;
                frame_buffer=std::vector<Vec3<uint8_t>>(width*height,{0,0,0});
                depth_buffer=std::vector<uint8_t>(width*height,{0});


  }
  inline uint16_t GetWidth(){return m_width;}
  inline uint16_t GetHeight(){return m_height;}

  void SetPixelColor(Vec2<uint16_t> cord,Vec3<uint8_t> Color){
    frame_buffer[cord.x + cord.y * m_width]=Color;
  }
  void SetPixelColor(uint32_t index,Vec3<uint8_t> Color){
    frame_buffer[index]=Color;
  }

  Vec3<uint8_t> GetColor(Vec2<uint16_t> cord){
    return frame_buffer[cord.x + cord.y * m_width];
  }

  Vec3<uint8_t> GetColor(uint32_t dex){
      return frame_buffer[dex];
  }


  uint16_t m_width,m_height;
  std::string m_name;
  std::vector<Vec3<uint8_t>> frame_buffer;

  // really useful for ovellaping images
  std::vector<uint8_t> depth_buffer;

};

}
