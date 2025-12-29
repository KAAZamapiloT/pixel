#include"storage.h"


/* A SIMPLE IMPLEMETAION OF CAMERA WHAT IT IS AND WHAT IT CAN DO
 *
 */

 enum class Type{
     Perspective,
     Orthographic
 };


template<typename T>
class camera{

    camera(Type p,INV::Vec3<T> location_3d){
        camera_type=p;
        Location_3d=location_3d;
        Location_2d=INV::Vec2<T>(location_3d.x,location_3d.y);
    }

    private:

    void UpdateViewMatrix()
    //default camera_type
    Type camera_type=Type::Orthographic;

    INV::Vec3<T> Location_3d;
    INV::Vec2<T> Location_2d; // I dont know if i will use it
    INV::Quat<T> m_Rotation;
    // Projection parameters
    float m_fov=45.0f;
    float m_AspectRation=16.0f/9.0f;
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

    mutable INV::Matrix4<double> m_ViewMatrix;
    mutable INV::Matrix4<double> m_ProjectionMatrix;
    mutable INV::Matrix4<double> m_ViewProjectionMatrix;
    bool bViewDirty=false;
    bool bProjectionFirty=false;

};
