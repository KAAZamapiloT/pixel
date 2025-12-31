
#pragma once
#include"Math_Utils.h"


/* A SIMPLE IMPLEMETAION OF CAMERA WHAT IT IS AND WHAT IT CAN DO
 *
 */

 enum class Type{
     Perspective,
     Orthographic
 };


template<typename T>
class camera{
public:
    camera(Type p,INV::Vec3<T> location_3d,  float fov, float AspectRatio,
    double NearPlane,
    double FarPlane){
        camera_type=p;
        m_fov=fov;
        m_AspectRatio=AspectRatio;
        m_NearPlane=NearPlane;
        m_FarPlane=FarPlane;
        Location_3d=location_3d;
        Location_2d=INV::Vec2<T>(location_3d.x,location_3d.y);
        m_ProjectionMatrix=INV::Matrix4<double>::perspective(fov,AspectRatio,NearPlane,FarPlane);
    }

    camera(Type p,INV::Vec3<T> location_3d,float left,float right,float bottom,float top,double NearPlane,double FarPlane){
        camera_type=p;

        Location_3d=location_3d;
        Location_2d=INV::Vec2<T>(location_3d.x,location_3d.y);

        m_OrthoLeft=left;
        m_OrthoRight=right;
        m_OrthoBottom=bottom;
        m_OrthoTop=top;
        m_NearPlane=NearPlane;
        m_FarPlane=FarPlane;
        m_Ortho=INV::Matrix4<double>::ortho(left,right,bottom,top,NearPlane,FarPlane);
    }

    INV::Matrix4<double> GetProjectionView(){
         return m_ProjectionViewMatrix;
    }
    INV::Vec3<T> GetLocation(){ return Location_3d;}
    INV::Vec3<float> GetRoationEuler( ){return INV::Vec3<float>(m_pitch,m_yaw,m_roll);}
    void updateMatrix(){
      if(bViewDirty){
        UpdateViewMatrix();
      }

    }
  private:
  void UpdateProjectionView(){
    m_ProjectionViewMatrix = m_ProjectionMatrix*m_ViewMatrix;
  }
    void UpdateOrientaionVector(){

        INV::Vec3<double> right=INV::Vec3<double>(std::cos(m_yaw),std::sin(m_yaw),0.0);
        INV::Vec3<double> up=INV::Vec3<double>(std::sin(m_pitch)*std::cos(m_yaw),std::sin(m_pitch)*std::sin(m_yaw),std::cos(m_pitch));
        INV::Vec3<double> forward=INV::Vec3<double>(-std::sin(m_yaw),std::cos(m_yaw),0.0);
    }
    void UpdateViewMatrix(){
        m_ViewMatrix[0][0] =right.x ;
           m_ViewMatrix[0][1] = up.x;
           m_ViewMatrix[0][2] = forward.x;
           m_ViewMatrix[0][3] = 0.0f;

           m_ViewMatrix[1][0] = right.y;
           m_ViewMatrix[1][1] = up.y;
           m_ViewMatrix[1][2] = forward.y;
           m_ViewMatrix[1][3] = 0.0f;

           m_ViewMatrix[2][0] = right.z;
           m_ViewMatrix[2][1] = up.z;
           m_ViewMatrix[2][2] = forward.z;
           m_ViewMatrix[2][3] = 0.0f;

           m_ViewMatrix[3][0] = right.Dot(Location_3d);
           m_ViewMatrix[3][1] = up.Dot(Location_3d);
           m_ViewMatrix[3][2] = forward.Dot(Location_3d);
           m_ViewMatrix[3][3] = 1.0f;

    }
    //default camera_type
    Type camera_type=Type::Orthographic;

    INV::Vec3<T> Location_3d;
    INV::Vec2<T> Location_2d; // I dont know if i will use it
    INV::Quat<T> m_Rotation;
    // Projection parameters
    float m_fov=45.0f;
    float m_AspectRatio=16.0f/9.0f;
    double m_NearPlane=0.1f;
    double m_FarPlane=50.f;

    // Euler angles
    float m_yaw=0.0f;
    float m_pitch=0.0f;
    float m_roll=0.0f;
    // matrices projection vs prespective

    float m_OrthoLeft=-1.0f;
    float m_OrthoRight=1.0f;
    float m_OrthoTop=1.0f;
    float m_OrthoBottom=-1.0f;

    // matrices and satate

     INV::Matrix4<double> m_ViewMatrix;
     INV::Matrix4<double> m_ProjectionMatrix;
     INV::Matrix4<double> m_ProjectionViewMatrix;
     INV::Matrix4<double> m_Ortho;
    bool bViewDirty=false;
    bool bProjectionFirty=false;

    // camera specific vector
    INV::Vec3<double> right=INV::Vec3<double>(1.0,0.0,0.0);
    INV::Vec3<double> forward=INV::Vec3<double>(0.0,0.0,1.0);
    INV::Vec3<double> up=INV::Vec3<double>(0.0,1.0,0.0);

};
