#pragma once
#include <locale>
#include <system_error>
#include<vector>
#include<cstdint>
#include"string"
namespace INV{
// collection of 3 vals
template <typename T>
class Vec3{
    public:
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vec3(){

    }
    Vec3(T a){
        x=a;
        y=a;
        z=a;
    }
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
    float magnitude_squared(){
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
    float magnitude_squared(){
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
static Vec4<T> Cross_product(Vec4<T> v1, Vec4<T> v2){
    return Vec4<T>(v1.y*v2.z-v1.z*v2.y,v1.z*v2.x-v1.x*v2.z,v1.x*v2.y-v1.y*v2.x);
}

float magnitude_squared(){
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
constexpr explicit Matrix4(T v) {
      for (int i = 0; i < 4; ++i)
          for (int j = 0; j < 4; ++j)
              Mat[i][j] = v;
  }
    constexpr Matrix4() = default;


    constexpr T* operator[](int r) { return Mat[r]; }
    constexpr const T* operator[](int r) const { return Mat[r]; }

    // Addition
        friend constexpr Matrix4 operator+(const Matrix4& a, const Matrix4& b) {
            Matrix4 r;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    r.Mat[i][j] = a.Mat[i][j] + b.Mat[i][j];
            return r;
        }

        // Multiplication
        friend constexpr Matrix4 operator*(const Matrix4& a, const Matrix4& b) {
            Matrix4 r;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    T sum{};
                    for (int k = 0; k < 4; ++k)
                        sum += a.Mat[i][k] * b.Mat[k][j];
                    r.Mat[i][j] = sum;
                }
            }
            return r;
        }



// Fov must be in radians
static Matrix4 perspective(float fov, float aspect, float near, float far){


        float t=std::tan(fov*0.5f);
        Matrix4 m{}; // zero-initialized

           m[0][0] = 1.0f / (aspect * t);
           m[1][1] = 1.0f / t;

           m[2][2] = -(far + near) / (far - near);
           m[2][3] = -(2.0f * far * near) / (far - near);

           m[3][2] = -1.0f;
           m[3][3] = 0.0f;

           return m;
}
static Matrix4 ortho(
    float left, float right,
    float bottom, float top,
    float near, float far)
{


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

static INV::Vec4<T> Matrix4_Vec4_mul(const Matrix4<T>&mat,const Vec4<T>&v){

    return  INV::Vec4<T>(mat[0][0]*v.x+mat[0][1]*v.y+mat[0][2]*v.z+mat[0][3]*v.w,
                         mat[1][0]*v.x+mat[1][1]*v.y+mat[1][2]*v.z+mat[1][3]*v.w,
                         mat[2][0]*v.x+mat[2][1]*v.y+mat[2][2]*v.z+mat[2][3]*v.w,
                         mat[3][0]*v.x+mat[3][1]*v.y+mat[3][2]*v.z+mat[3][3]*v.w);
}


T Mat[4][4];
};





template<typename T>
class Quat{
public:
Quat(T x,T y,T z,T w):x(x),y(y),z(z),w(w){}
Quat():x(0),y(0),z(0),w(1){}
//
Quat(T angle,Vec3<T> axis){
    T halfAngle=angle/2;
    T sinHalfAngle=sin(halfAngle);
    x=axis.x*sinHalfAngle;
    y=axis.y*sinHalfAngle;
    z=axis.z*sinHalfAngle;
    w=cos(halfAngle);
}

T length_sq()const{
   return x*x+y*y+z*z+w*w;
}

Quat<T> conjugate(){
    return Quat(-x,-y,-z,w);
}
void normalize() {
    T len2 = length_sq();
    if (len2 == T(0)) return;
    T invLen = T(1) / std::sqrt(len2);
    x *= invLen;
    y *= invLen;
    z *= invLen;
    w *= invLen;
}
Quat inverse() const {
    T len2 = this->length_sq()();
    if (len2 == T(0)) return {};
    return this->conjugate() / len2;
}
Vec3<T> rotate(const Vec3<T>& v) const {
    Quat p(v.x, v.y, v.z, 0);
    Quat r = (*this) * p * this->conjugate();
    return { r.x, r.y, r.z };
}
static Quat<T> Multiply(Quat<T> A,Quat<T> B){
    return Quat(A.w*B.x+A.x*B.w+A.y*B.z-A.z*B.y,
        A.w*B.y-A.x*B.z+A.y*B.w+A.z*B.x
        ,A.w*B.z+A.x*B.y-A.y*B.x+A.z*B.w
        ,A.w*B.w-A.x*B.x-A.y*B.y-A.z*B.z);
}
static T Dot(Quat<T> A,Quat<T> B){
    return A.w*B.w+A.x*B.x+A.y*B.y+A.z*B.z;
}

static Quat<T> nlerp(const Quat<T>& A,const Quat<T>& B,T t){
    T dot =Dot(A, B);
    Quat<T> result;
    if(dot <0){
        result=A*(1-t)+(B*-1)*t;
    }else{
        result=A*(1-t)+B*t;
    }
    result.normalize();
    return result;
}

static Quat<T> slerp(const Quat<T>& A,const Quat<T>& B,T t){
    T dot =Dot(A, B);
  Quat bCopy = B;
  if(dot<0){
dot =-dot;
bCopy=-1*bCopy;
  }
  const T EPS = 1e-6;
    if (dot > 1 - EPS) {
        return nlerp(A, bCopy, t);
    }
    T theta = std::acos(dot);
     T sinTheta = std::sin(theta);
     T w1 = std::sin((1 - t) * theta) / sinTheta;
         T w2 = std::sin(t * theta) / sinTheta;

         return (A * w1 + bCopy * w2);
}



T x,y,z,w;


Quat operator*(const Quat& q) const{
    return Multiply(*this,q);
}

Quat operator+(const Quat& q) const{
    return Quat(x+q.x,y+q.y,z+q.z,w+q.w);
}
Quat operator*(T scalar) const{
    return Quat(x*scalar,y*scalar,z*scalar,w*scalar);
}
Quat operator/(T scalar) const{
    return Quat(x/scalar,y/scalar,z/scalar,w/scalar);
}
Quat& operator=(const Quat& q) = default;

};

}
