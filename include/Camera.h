
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
    float NearPlane,
    float FarPlane){
        camera_type=p;
        m_fov=fov;
        m_AspectRatio=AspectRatio;
        m_NearPlane=NearPlane;
        m_FarPlane=FarPlane;
        Location_3d=location_3d;
        m_ProjectionMatrix=INV::Matrix4<float>::perspective(fov,AspectRatio,NearPlane,FarPlane);
    }

    camera(Type p,INV::Vec3<T> location_3d,float left,float right,float bottom,float top,float NearPlane,float FarPlane){
        camera_type=p;

        Location_3d=location_3d;

        m_OrthoLeft=left;
        m_OrthoRight=right;
        m_OrthoBottom=bottom;
        m_OrthoTop=top;
        m_NearPlane=NearPlane;
        m_FarPlane=FarPlane;
        m_Ortho=INV::Matrix4<float>::ortho(left,right,bottom,top,NearPlane,FarPlane);
    }

    INV::Matrix4<float> GetProjectionView(){
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

        INV::Vec3<float> right=INV::Vec3<float>(std::cos(m_yaw),std::sin(m_yaw),0.0);
        INV::Vec3<float> up=INV::Vec3<float>(std::sin(m_pitch)*std::cos(m_yaw),std::sin(m_pitch)*std::sin(m_yaw),std::cos(m_pitch));
        INV::Vec3<float> forward=INV::Vec3<float>(-std::sin(m_yaw),std::cos(m_yaw),0.0);
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
    INV::Quat<T> m_Rotation;
    // Projection parameters
    float m_fov=45.0f;
    float m_AspectRatio=16.0f/9.0f;
    float m_NearPlane=0.1f;
    float m_FarPlane=50.f;

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

     INV::Matrix4<float> m_ViewMatrix;
     INV::Matrix4<float> m_ProjectionMatrix;
     INV::Matrix4<float> m_ProjectionViewMatrix;
     INV::Matrix4<float> m_Ortho;
    bool bViewDirty=false;
    bool bProjectionFirty=false;

    // camera specific vector
    INV::Vec3<float> right=INV::Vec3<float>(1.0,0.0,0.0);
    INV::Vec3<float> forward=INV::Vec3<float>(0.0,0.0,1.0);
    INV::Vec3<float> up=INV::Vec3<float>(0.0,1.0,0.0);

};
