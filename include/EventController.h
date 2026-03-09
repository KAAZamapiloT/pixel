#pragma once

#include<SDL.h>
#include"Camera.h"
#include<memory>

class MovableCamera:public camera{
    MovableCamera(ECameraType p,Vec3f location_3d,  float fov, float AspectRatio,
    float NearPlane,
    float FarPlane){
        CAM= new camera(p,location_3d,fov,AspectRatio,NearPlane,FarPlane);
    }
    MovableCamera(ECameraType p,Vec3f location_3d,float left,float right,float bottom,
        float top,float NearPlane,float FarPlane){
            CAM=new camera(p,location_3d,left,right,bottom,top,NearPlane,FarPlane);
        }

    void Teleport(Vec3f direction,float units){
           // radial system
    }
    void Teleport(Vec3f position){
          //
    }

    void Movement(Vec3f direction,float speed){

    }

    void Rotation(quat q){

    }
    void RotatingMov(quat axis,float speed){
        //will roatate at a particluar speed
    }
    private:
    std::unique_ptr<camera> CAM;
}
