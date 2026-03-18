#pragma once
#include"SDL3/SDL.h"
#include"camera.h"
#include"logger.h"
#include"Math_Utils.h"
// controlling camera movements using this class
class EventController{
  public:
  void UpdateSpeed(float f){
      this->RotSpeed = f;
  }
  void ImpactCamera(camera&cam,SDL_Event& e, bool bActive,float dt){
      if(!bActive) return;

      const bool* keys = SDL_GetKeyboardState(NULL);
float yaw=0;
float pitch=0;

          if (keys[SDL_SCANCODE_LEFT]){
              yaw+=RotSpeed * dt;
              PDEBUG("left Imapact Camera");
          }
          if (keys[SDL_SCANCODE_RIGHT]){
              yaw+=-RotSpeed * dt;
              PDEBUG("right Imapact Camera");
          }
          if (keys[SDL_SCANCODE_UP]){
              pitch+=RotSpeed * dt;
              PDEBUG("up Imapact Camera");
          }
          if (keys[SDL_SCANCODE_DOWN]){
              pitch+=-RotSpeed * dt;
              PDEBUG("down Imapact Camera");
          }
          cam.Rotate(pitch,yaw,0);
  }
private:
float RotSpeed = 2.0f;

Vec3f y_axis=INV::Vec3<float>(0,1,0);
Vec3f x_axis=INV::Vec3<float>(1,0,0);
Vec3f z_axis=INV::Vec3<float>(0,0,1);
};
