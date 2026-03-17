#pragma once
#include"SDL3/SDL.h"
#include"camera.h"
// controlling camera movements using this class
class EventController{
  public:


  void ImpactCamera(camera&cam,SDL_Event& e, bool bActive=true){
      if(!bActive) return;

      if (e.type == SDL_EVENT_KEY_DOWN)
          {
              switch (e.key.keysym.sym)
              {
                  case SDLK_LEFT:  cam.AxisRoation(y_axis,RotSpeed); break;
                  case SDLK_RIGHT: cam.AxisRoation(y_axis,RotSpeed); break;
                  case SDLK_UP:    cam.AxisRoation(x_axis,RotSpeed); break;
                  case SDLK_DOWN:  cam.AxisRoation(x_axis,RotSpeed); break;
              }
          }
  }
private:
quat  LeftRotation = quat(0,1,0,1).normalize();
quat  RightRotation = quat(0,1,0,-1).normalize();
quat  UpRotation = quat(1,0,0,1).normalize();
quat  DownRotation = quat(1,0,0,-1).normalize();
float RotSpeed = 1.0f;

Vec3f y_axis(0,1,0);
Vec3f x_axis(1,0,0);
Vec3f z_axis(0,0,1);
};
