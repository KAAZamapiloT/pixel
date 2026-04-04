//Math_utilities
#pragma once
#include<vector>
#include<cstdint>
#include"string"
#define _USE_MATH_DEFINES
#include <cmath>
constexpr float M_PI = 3.14159265358979323846f;
namespace INV{

template <typename T>
class Vec2{
    public:
    Vec2(T x, T y) : x(x), y(y) {}
    Vec2(std::initializer_list<T> list) : x(*list.begin()), y(*(list.begin() + 1)) {}

   constexpr Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    constexpr Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    constexpr Vec2 operator*(const Vec2& other) const {
        return Vec2(x * other.x, y * other.y);
    }

     constexpr   Vec2 operator*(const T scaler) const{
        return Vec2(x*scaler,y*scaler);
    }



    Vec2 operator/(const Vec2& other) const {
        return Vec2(x / other.x, y / other.y);
    }



    T Dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }
    T magnitude_squared(){
        return x*x+y*y;
    }

    void iMul(int i){
       x = x*i;
       y = y*i;
    }
    T x, y;
};

template <typename T>
class Vec3{
    public:
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vec3(){
    x=0;
    y=0;
    z=0;
    }
    Vec3(T a){
        x=a;
        y=a;
        z=a;
    }
    Vec3(class Vec2<T> a,T b){
     x=a.x;
     y=a.y;
     z=b;
    }
    Vec3(std::initializer_list<T> list) : x(*list.begin()), y(*(list.begin() + 1)), z(*(list.begin() + 2)) {}

    constexpr Vec3 operator*(const T scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);  }

    constexpr Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

   constexpr Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

   constexpr Vec3 operator*(const Vec3& other) const {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }

    constexpr Vec3 operator/(const Vec3& other) const {
        return Vec3(x / other.x, y / other.y, z / other.z);
    }

    constexpr Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    constexpr Vec3 operator=(const Vec3& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    constexpr Vec3& operator-=(const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    constexpr Vec3& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    constexpr Vec3& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

   constexpr Vec3 Cross(const Vec3& other) const {
        return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

   constexpr T Dot(const Vec3& other) const {
        return (x * other.x+ y * other.y+ z * other.z);
    }
   constexpr Vec3 operator-() const {
        return Vec3(-x, -y, -z);
    }
    Vec3 Hadamard(const Vec3& other) const {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }
   void normalize(){
    T len2=magnitude_squared();
    if(len2<(1e-8)){
        x=y=z=T(0);
        return;
    }
    T invMag=1/sqrt(len2);
    x*=invMag;
    y*=invMag;
    z*=invMag;
   }
   Vec3 normalized() const
   {
       T len2 = magnitude_squared();

       if (len2 < T(1e-8)) {
           return Vec3(0);
       }

       T invLen = T(1) / std::sqrt(len2);

       return Vec3(x * invLen, y * invLen, z * invLen);
   }
   T magnitude(){
       return std::sqrt(magnitude_squared());
   }
    constexpr T magnitude_squared() const{
        return x*x+y*y+z*z;
    }
    T x, y, z;
};

// collection of 2 vals

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
Vec4(std::initializer_list<T> list) : x(*list.begin()), y(*(list.begin() + 1)), z(*(list.begin() + 2)), w(*(list.begin() + 3)) {}

Vec4& operator=(const Vec4& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }
    return *this;
}
Vec3<T> xyz() const { return Vec3<T>(x, y, z); }

T Dot(Vec4<T> other){return x*other.x+y*other.y+z*other.z+w*other.w;}


T magnitude_squared() const{
    return x*x+y*y+z*z+w*w;
}
  T x,y,z,w;
};

template<typename T>
class Matrix2{
public:
Matrix2(T a,T b,T c,T d):Mat{{a,b},{c,d}}{

}

constexpr Matrix2(){
    Mat[0][0]=1;
    Mat[0][1]=0;
    Mat[1][0]=0;
    Mat[1][1]=1;
}
constexpr Matrix2 operator+(const Matrix2& other)const{
    Matrix2 result;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            result.Mat[i][j]=Mat[i][j]+other.Mat[i][j];
        }
    }
    return result;
}

constexpr Vec2<T> operator*(const Vec2<T>& vec) const
{
    return Vec2<T>(
        Mat[0][0] * vec.x + Mat[0][1] * vec.y,
        Mat[1][0] * vec.x + Mat[1][1] * vec.y
    );
}

T Mat[2][2];
};

template<typename T>
class Matrix3{
    public:
    Matrix3(T a,T b,T c,T d,T e,T f,T g,T h,T i):Mat{{a,b,c},{d,e,f},{g,h,i}}{

    }
   constexpr Matrix3(){
    Mat[0][0]=0;
    Mat[0][1]=0;
    Mat[0][2]=0;
    Mat[1][0]=0;
    Mat[1][1]=0;
    Mat[1][2]=0;
    Mat[2][0]=0;
    Mat[2][1]=0;
    Mat[2][2]=0;
    }
    Matrix3 operator+(const Matrix3&other ) const{
        Matrix3 result;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                result.Mat[i][j]=Mat[i][j]+other.Mat[i][j];
            }
        }
        return result;
    }
    Vec3<T> operator*(const Vec3<T>& vec) const
    {
        return Vec3<T>(
            Mat[0][0] * vec.x + Mat[0][1] * vec.y + Mat[0][2] * vec.z,
            Mat[1][0] * vec.x + Mat[1][1] * vec.y + Mat[1][2] * vec.z,
            Mat[2][0] * vec.x + Mat[2][1] * vec.y + Mat[2][2] * vec.z
        );
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
    constexpr Matrix4(){
        Mat[0][0]=0;
        Mat[0][1]=0;
        Mat[0][2]=0;
        Mat[0][3]=0;
        Mat[1][0]=0;
        Mat[1][1]=0;
        Mat[1][2]=0;
        Mat[1][3]=0;
        Mat[2][0]=0;
        Mat[2][1]=0;
        Mat[2][2]=0;
        Mat[2][3]=0;
        Mat[3][0]=0;
        Mat[3][1]=0;
        Mat[3][2]=0;
        Mat[3][3]=0;
    }

    constexpr Vec4<T> operator*(const Vec4<T>& v) const {
        return Vec4<T>(
            Mat[0][0]*v.x + Mat[0][1]*v.y + Mat[0][2]*v.z + Mat[0][3]*v.w,
            Mat[1][0]*v.x + Mat[1][1]*v.y + Mat[1][2]*v.z + Mat[1][3]*v.w,
            Mat[2][0]*v.x + Mat[2][1]*v.y + Mat[2][2]*v.z + Mat[2][3]*v.w,
            Mat[3][0]*v.x + Mat[3][1]*v.y + Mat[3][2]*v.z + Mat[3][3]*v.w
        );
    }

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

        float rads=fov*3.141592653589793f/180.0f;
        float t=std::tan(rads*0.5f);
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


T Mat[4][4];
};





template<typename T>
class Quat{
public:
Quat(T x,T y,T z,T w):x(x),y(y),z(z),w(w){}
Quat():x(0),y(0),z(0),w(1){}
//
Quat(T angle,Vec3<T> axis){
    axis.normalize();
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

Quat<T> conjugate()const{
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
    T len2 = this->length_sq();
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


static Matrix3<T> GetRotationMatrix(Quat<T> q){

    T xx=q.x*q.x;
    T yy=q.y*q.y;
    T zz=q.z*q.z;
    T xy=q.x*q.y;
    T xz=q.x*q.z;
    T yz=q.y*q.z;
    T wx=q.w*q.x;
    T wy=q.w*q.y;
    T wz=q.w*q.z;
    return Matrix3<T>(1-2*(yy+zz),2*(xy-wz),2*(xz+wy),
        2*(xy+wz),1-2*(xx+zz),2*(yz-wx),
        2*(xz-wy),2*(yz+wx),1-2*(xx+yy));
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
Quat& operator=(const Quat& q){
    x=q.x;
    y=q.y;
    z=q.z;
    w=q.w;
    return *this;
};

INV::Vec3<float> QuatToEuler(const Quat& q){
    INV::Vec3<float> euler;

        // Pitch (X-axis rotation)
        float sinp = 2.0f * (q.w * q.x + q.y * q.z);
        float cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
        euler.x = std::atan2(sinp, cosp);

        // Yaw (Y-axis rotation)
        float siny = 2.0f * (q.w * q.y - q.z * q.x);

        if (std::abs(siny) >= 1.0f)
            euler.y = std::copysign(M_PI / 2.0f, siny); // clamp (gimbal lock)
        else
            euler.y = std::asin(siny);

        // Roll (Z-axis rotation)
        float sinr = 2.0f * (q.w * q.z + q.x * q.y);
        float cosr = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
        euler.z = std::atan2(sinr, cosr);

        return euler;
}
};

}

// ALIAS FOR HELP
using Mat4f= INV::Matrix4<float>;
using Mat4i= INV::Matrix4<int>;

using Mat3f= INV::Matrix3<float>;
using Mat3i= INV::Matrix3<int>;

using Mat2f= INV::Matrix2<float>;
using Mat2i= INV::Matrix2<int>;

using Vec4f= INV::Vec4<float>;
using Vec4i= INV::Vec4<int>;
using Vec4ui16= INV::Vec4<uint16_t>;
using Vec4ui8= INV::Vec4<uint8_t>;

using Vec3f= INV::Vec3<float>;
using Vec3ui16= INV::Vec3<uint16_t>;
using Vec3i= INV::Vec3<int>;
using Vec3ui8= INV::Vec3<uint8_t>;

using Vec2f= INV::Vec2<float>;
using Vec2i= INV::Vec2<int>;
using Vec2ui16= INV::Vec2<uint16_t>;
using Vec2ui8= INV::Vec2<uint8_t>;

using quat= INV::Quat<float>;

// will implement math function here
class Math{
public:
static Mat3f QuaternionToMatrix(const quat& q) {
    float x = q.x, y = q.y, z = q.z, w = q.w;

    return Mat3f(
        1 - 2*y*y - 2*z*z,  2*x*y - 2*z*w,      2*x*z + 2*y*w,
        2*x*y + 2*z*w,      1 - 2*x*x - 2*z*z,  2*y*z - 2*x*w,
        2*x*z - 2*y*w,      2*y*z + 2*x*w,      1 - 2*x*x - 2*y*y
    );
}
static Mat2f ScaleMatrix2D(float scale){
    return INV::Matrix2<float>(scale,0,0,scale);
}
static Mat3f TranslateMatrix2D(float x,float y){
    return INV::Matrix3<float>(
           1, 0, x,
           0, 1, y,
           0, 0, 1
       );
}

static Mat2f RotateMatrix2D(float angle){
    float c = std::cos(angle);
    float s = std::sin(angle);
    return INV::Matrix2<float>(c,-s,s,c);
}

// point is stored in form of 3 vals so using vec3f is fine here
static void E_Rotation(INV::Vec3<float>& A,float angle,INV::Vec3<float> pivot){

    INV::Vec3<float> direction = A - pivot;
    float c = std::cos(angle);
    float s = std::sin(angle);
    INV::Matrix3<float> rotationMatrix(c,-s,0,s,c,0,0,0,1);
    A = rotationMatrix * direction + pivot;
}


static INV::Matrix3<float> ScaleRotateTranslateMatrix2D(
    float scale,
    float rotate_angle,
    float translateX,
    float translateY
) {
    float c = std::cos(rotate_angle);
    float s = std::sin(rotate_angle);

    return INV::Matrix3<float>(
        scale * c, -scale * s, translateX,
        scale * s,  scale * c, translateY,
        0.0f,       0.0f,      1.0f
    );
}

static Mat4f ScaleRoatateTranslateMatrix3d(float scale,quat q,Vec3f Translate){
Mat3f Rot=q.GetRotationMatrix(q);
return Mat4f(
    scale * Rot.Mat[0][0], scale * Rot.Mat[0][1], scale * Rot.Mat[0][2], Translate.x,
    scale * Rot.Mat[1][0], scale * Rot.Mat[1][1], scale * Rot.Mat[1][2], Translate.y,
    scale * Rot.Mat[2][0], scale * Rot.Mat[2][1], scale * Rot.Mat[2][2], Translate.z,
    0.0f,              0.0f,              0.0f,              1.0f
);

};
static Mat3f Rotation3D(float t,Vec3f a){
    float c = cos(t);
    float s = sin(t);
    float d = 1.0F - c;
    float x = a.x * d;
    float y = a.y * d;
    float z = a.z * d;
    float axay = x * a.y;
    float axaz = x * a.z;
    float ayaz = y * a.z;
    return Mat3f(c + x * a.x, axay - s * a.z, axaz + s * a.y,
    axay + s * a.z, c + y * a.y, ayaz - s * a.x,
    axaz - s * a.y, ayaz + s * a.x, c + z * a.z);

}
static INV::Matrix4<float> ScaleRotateTranslateMatrix3D(
    float scale,
    INV::Quat<float> rot,
    float translateX,
    float translateY,
    float translateZ
){

return INV::Matrix4<float>(
        scale * rot.x, -scale * rot.y, scale * rot.z, translateX,
        scale * rot.y,  scale * rot.x, -scale * rot.w, translateY,
        scale * rot.z,  scale * rot.w, -scale * rot.x, translateZ,
        0.0f,       0.0f,      0.0f,      1.0f
    );
}
static Mat4f ScaleRotateTranslateMatrix3D(
    Vec3f scale,
    quat rot,
    Vec3f t
){
    rot.normalize();
    Mat3f R = quat::GetRotationMatrix(rot);

    Mat4f M;

    // ROW 0
    M[0][0] = R.Mat[0][0] * scale.x;
    M[0][1] = R.Mat[0][1] * scale.y;
    M[0][2] = R.Mat[0][2] * scale.z;
    M[0][3] = t.x;

    // ROW 1
    M[1][0] = R.Mat[1][0] * scale.x;
    M[1][1] = R.Mat[1][1] * scale.y;
    M[1][2] = R.Mat[1][2] * scale.z;
    M[1][3] = t.y;

    // ROW 2
    M[2][0] = R.Mat[2][0] * scale.x;
    M[2][1] = R.Mat[2][1] * scale.y;
    M[2][2] = R.Mat[2][2] * scale.z;
    M[2][3] = t.z;

    // ROW 3
    M[3][0] = 0;
    M[3][1] = 0;
    M[3][2] = 0;
    M[3][3] = 1;

    return M;
}
template<typename T>
static bool IsFacingSameDirection(INV::Vec3<T> A,INV::Vec3<T> B){
    return A.Dot(B) > 0;
}

static void MakeRoation(Vec3f&v,quat rotation){
Vec3f x=Vec3f(rotation.x,rotation.y,rotation.z);
float b=rotation.x*rotation.x+rotation.y*rotation.y+rotation.z*rotation.z;
v=v*(rotation.w*rotation.w-b)+x*(v.Dot(x)*2.0f)+x.Cross(v)*(rotation.w*2.0f);
}

static Vec3f GetReflection(Vec3f normal, Vec3f incident){
    return normal * 2.0f * normal.Dot(incident) - incident;
}

};
