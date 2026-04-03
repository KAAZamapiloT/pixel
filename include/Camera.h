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
        UpdateOrientaionVector();
           UpdateViewMatrix();
           UpdateProjectionView();
    }

    void UpdateSpeed(float speed,float translate){
        this->speed=speed;
        this->translateSpeed=translate;
    }


    std::pair<float,float> GetSpeed(){ return std::pair<float,float>(speed,translateSpeed);}
    Mat4f GetProjectionView(){
         return m_ProjectionViewMatrix;
    }
    Mat4f GetViewMatrix(){
         return m_ViewMatrix;
    }
    void SetAspectRatio(float x,float y) {
        m_AspectRatio = x/y;
        bViewDirty = true;
        UpdateProjectionMatrix();
        updateMatrix();
        UpdateProjectionView();
    }
    Vec3f GetLocation(){ return Location_3d;}
    Vec3f GetForwardVector(){return forward;}
    Vec3f GetRoationEuler( ){return Vec3f(m_pitch,m_yaw,m_roll);}
    void updateMatrix(){
      if(bViewDirty){
        UpdateViewMatrix();
        bViewDirty = false;
      }
    }

    void Rotation(quat q){
        m_Rotation = m_Rotation*q;
        bViewDirty = true;
        UpdateOrientaionVector();

        updateMatrix();
    }



    void AxisRotation(Vec3f axis, float angle){
        quat q = quat(angle,axis);
        m_Rotation = m_Rotation*q;
        m_Rotation.normalize();
         bViewDirty = true;
        UpdateOrientaionVector();

        updateMatrix();
    }

    void Rotate(float pitch,float yaw,float roll) {
        Vec3f WorldUp(0,1,0);

        // -> Yaw Rotation
        quat qYaw(yaw, WorldUp);
        m_Rotation = qYaw*m_Rotation;


        // -> Pitch Rotation
        Vec3f LocalRight=m_Rotation.rotate(Vec3f(1,0,0));
        quat qPitch(pitch,LocalRight);
        m_Rotation = qPitch*m_Rotation;

        // -> Roll Rotation
        Vec3f LocalUp=m_Rotation.rotate(Vec3f(0,1,0));
        quat qRoll(roll, LocalUp);
        m_Rotation = qRoll*m_Rotation;

        m_Rotation.normalize();
        UpdateOrientaionVector();
        bViewDirty = true;
        updateMatrix();
    }

    void Translate(const Vec3f& translation) {
        Location_3d += translation;
        bViewDirty = true;
        updateMatrix();
    }
  private:

  void Init(){
      UpdateOrientaionVector();
         UpdateViewMatrix();
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

      m_Rotation.normalize();

        Mat3f R = quat::GetRotationMatrix(m_Rotation);

        right   = Vec3f(R.Mat[0][0], R.Mat[0][1], R.Mat[0][2]);
        up      = Vec3f(R.Mat[1][0], R.Mat[1][1], R.Mat[1][2]);
        forward = Vec3f(R.Mat[2][0], R.Mat[2][1], R.Mat[2][2]);

    }

    // TODO: ERROR HERE
    void UpdateViewMatrix()
    {
        // ROW 0 → right axis
            m_ViewMatrix[0][0] = right.x;
            m_ViewMatrix[0][1] = right.y;
            m_ViewMatrix[0][2] = right.z;
            m_ViewMatrix[0][3] = -right.Dot(Location_3d);

            // ROW 1 → up axis
            m_ViewMatrix[1][0] = up.x;
            m_ViewMatrix[1][1] = up.y;
            m_ViewMatrix[1][2] = up.z;
            m_ViewMatrix[1][3] = -up.Dot(Location_3d);


            m_ViewMatrix[2][0] = -forward.x;
            m_ViewMatrix[2][1] = -forward.y;
            m_ViewMatrix[2][2] = -forward.z;
            m_ViewMatrix[2][3] =  forward.Dot(Location_3d);

            // ROW 3
            m_ViewMatrix[3][0] = 0.0f;
            m_ViewMatrix[3][1] = 0.0f;
            m_ViewMatrix[3][2] = 0.0f;
            m_ViewMatrix[3][3] = 1.0f;


            UpdateProjectionView();
    }


    //default camera_type
    ECameraType camera_type=ECameraType::Orthographic;

    INV::Quat<float> m_Rotation=quat(0,0,0,1);
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




    // motion realted values
    //
    float speed =1.0f;
    float translateSpeed=1.0f;

    public:
    Vec3f right=Vec3f(1.0,0.0,0.0);
    Vec3f forward=Vec3f(0.0,0.0,-1.0);
    Vec3f up=Vec3f(0.0,1.0,0.0);


    Vec3f Location_3d;
};
