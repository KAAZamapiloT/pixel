#pragma once
#include"SDL3/SDL.h"
#include"camera.h"
#include"Math_Utils.h"
// controlling camera movements using this class
class EventController{
  public:
  void ImpactCamera(camera&cam,SDL_Event& e, bool bActive,float dt){
      if(!bActive) return;

      const bool* keys = SDL_GetKeyboardState(NULL);

          float speed = 0.0000001f; // radians/sec

          if (keys[SDL_SCANCODE_LEFT])
              cam.AxisRotation(y_axis, +speed * dt);

          if (keys[SDL_SCANCODE_RIGHT])
              cam.AxisRotation(y_axis, -speed * dt);

          if (keys[SDL_SCANCODE_UP])
              cam.AxisRotation(x_axis, +speed * dt);

          if (keys[SDL_SCANCODE_DOWN])
              cam.AxisRotation(x_axis, -speed * dt);
  }
private:
float RotSpeed = 0.0001f;

Vec3f y_axis=INV::Vec3<float>(0,1,0);
Vec3f x_axis=INV::Vec3<float>(1,0,0);
Vec3f z_axis=INV::Vec3<float>(0,0,1);
};
