#pragma once
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


    Vec2 Cross(const Vec2& other) const {
        return Vec2(y * other.x - x * other.y);
    }

    Vec2 Dot(const Vec2& other) const {
        return Vec2(x * other.x, y * other.y);
    }

    T x, y;
};

template <typename T>

class Vec4{

Vec4(T x,T y,T z,T a):x(x),y(y),z(z),a(a){

}

  T x,y,z,a;
};


// now i need a way to represent window
//
//



class Window{
public:
  Window(uint8_t width,uint8_t height,std::string name){
                m_width=width;
                m_height=height;
                m_name=name;
                frame_buffer=std::vector<Vec3<uint8_t>>(width*height,{0,0,0});
  }
  inline uint8_t GetWidth(){return m_width;}
  inline uint8_t GetHeight(){return m_height;}



private:
  uint8_t m_width,m_height;
  std::string m_name;
  std::vector<Vec3<uint8_t>> frame_buffer;


};

}
