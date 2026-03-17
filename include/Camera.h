//camera
#pragma once
#include"Math_Utils.h"
#include "iostream"
#include <cmath>


/* A SIMPLE IMPLEMETAION OF CAMERA WHAT IT IS AND WHAT IT CAN DO
 *
 */

 enum class ECameraType{
     Perspective,
     Orthographic
 };



class camera{
public:
    camera(ECameraType p,Vec3f location_3d,  float fov, float AspectRatio,
    float NearPlane,
    float FarPlane){
        camera_type=p;
        m_fov=fov;
        m_AspectRatio=AspectRatio;
        m_NearPlane=NearPlane;
        m_FarPlane=FarPlane;
        Location_3d=location_3d;
        m_ProjectionMatrix=Mat4f::perspective(fov,AspectRatio,NearPlane,FarPlane);
        Init();
    }

    camera(ECameraType p,Vec3f location_3d,float left,float right,float bottom,
        float top,float NearPlane,float FarPlane){
        camera_type=p;

        Location_3d=location_3d;

        m_OrthoLeft=left;
        m_OrthoRight=right;
        m_OrthoBottom=bottom;
        m_OrthoTop=top;
        m_NearPlane=NearPlane;
        m_FarPlane=FarPlane;
        m_Ortho=Mat4f::ortho(left,right,bottom,top,NearPlane,FarPlane);
        UpdateViewMatrix();
        UpdateOrientaionVector();
        UpdateProjectionView();
    }

    void UpdateSpeed(float speed,float translate){
        speed=speed;
        translateSpeed=translate;
    }


    std::pair<float,float> GetSpeed(){ return std::pair<float,float>(speed,translateSpeed);}
    Mat4f GetProjectionView(){
         return m_ProjectionViewMatrix;
    }
    Mat4f GetViewMatrix(){
         return m_ViewMatrix;
    }
    Vec3f GetLocation(){ return Location_3d;}

    Vec3f GetRoationEuler( ){return Vec3f(m_pitch,m_yaw,m_roll);}
    void updateMatrix(){
      if(bViewDirty){
        UpdateViewMatrix();
      }
    }

    void Rotation(quat q){
        m_Rotation = m_Rotation*q;
        INV::Vec3<float> euler = m_Rotation.QuatToEuler(m_Rotation);
        m_pitch = euler.x;
        m_yaw=euler.y;
        m_roll=euler.z;
        UpdateOrientaionVector();
        bViewDirty = true;
        updateMatrix();
    }

    void SpeedRoation(quat q,float speed){
     //   q.w*=speed;
        m_Rotation = q*m_Rotation;
        INV::Vec3<float> euler = m_Rotation.QuatToEuler(m_Rotation);
        m_pitch = euler.x;
        m_yaw = euler.y;
        m_roll = euler.z;
        UpdateOrientaionVector();
        bViewDirty = true;
        updateMatrix();
    }

    void AxisRotation(Vec3f axis, float angle){
        quat q = quat( std::cos(angle/2.0f),axis);
        m_Rotation = m_Rotation*q;
        m_Rotation.normalize();
        INV::Vec3<float> euler = m_Rotation.QuatToEuler(m_Rotation);
        m_pitch = euler.x;
        m_yaw = euler.y;
        m_roll = euler.z;
        UpdateOrientaionVector();
        bViewDirty = true;
        updateMatrix();
    }
  private:

  void Init(){
      UpdateViewMatrix();
      UpdateOrientaionVector();
      UpdateProjectionMatrix();
  }
  void UpdateProjectionView(){
    m_ProjectionViewMatrix = m_ProjectionMatrix*m_ViewMatrix;
  }

  void UpdateProjectionMatrix(){
    m_ProjectionMatrix=Mat4f::perspective(m_fov,m_AspectRatio,m_NearPlane,m_FarPlane);
    UpdateProjectionView();
  }
    void UpdateOrientaionVector(){

        forward.x=std::cos(m_pitch)*std::sin(m_yaw);
        forward.y=std::sin(m_pitch);
        forward.z=-std::cos(m_pitch)*std::cos(m_yaw);

        forward.normalize();

        Vec3f WorldUp(0.0f,1.0f,0.0f);

        right=forward.Cross(WorldUp);
        right.normalize();

        up=forward.Cross(right);
        up.normalize();


    }
    void UpdateViewMatrix()
    {
        m_ViewMatrix[0][0] = right.x;
        m_ViewMatrix[1][0] = right.y;
        m_ViewMatrix[2][0] = right.z;
        m_ViewMatrix[3][0] = 0.0f;

        m_ViewMatrix[0][1] = up.x;
        m_ViewMatrix[1][1] = up.y;
        m_ViewMatrix[2][1] = up.z;
        m_ViewMatrix[3][1] = 0.0f;

        m_ViewMatrix[0][2] = forward.x;
        m_ViewMatrix[1][2] = forward.y;
        m_ViewMatrix[2][2] = forward.z;
        m_ViewMatrix[3][2] = 0.0f;

        m_ViewMatrix[0][3] = -right.Dot(Location_3d);
        m_ViewMatrix[1][3] = -up.Dot(Location_3d);
        m_ViewMatrix[2][3] = -forward.Dot(Location_3d);
        m_ViewMatrix[3][3] = 1.0f;

        UpdateProjectionView();
    }

    //default camera_type
    ECameraType camera_type=ECameraType::Orthographic;

    Vec3f Location_3d;
    INV::Quat<float> m_Rotation;
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

     Mat4f m_ViewMatrix;
     Mat4f m_ProjectionMatrix;
     Mat4f m_ProjectionViewMatrix;
     Mat4f m_Ortho;
    bool bViewDirty=false;
    bool bProjectionFirty=false;

    // camera specific vector
    Vec3f right=Vec3f(1.0,0.0,0.0);
    Vec3f forward=Vec3f(0.0,0.0,-1.0);
    Vec3f up=Vec3f(0.0,1.0,0.0);



    // motion realted values
    //
    float speed =1.0f;
    float translateSpeed=1.0f;
};
