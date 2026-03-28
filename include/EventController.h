#pragma once
#include"SDL3/SDL.h"
#include"camera.h"
#include"logger.h"
#include"Math_Utils.h"
// controlling camera movements using this class
struct MouseState {
    float lastX = 0.0f;
    float lastY = 0.0f;
    bool first = true;
};


class EventController{
    MouseState mouse;
  public:

  void UpdateSpeed(float f){
      this->RotSpeed = f;
  }

  void MouseImpactCamera(camera& cam, float dt) {


      float mx, my;

      Uint32 state = SDL_GetMouseState(&mx, &my);

        // 👉 check right mouse button
        if (!(state & SDL_BUTTON_RMASK)) {
            mouse.first = true; // reset to avoid jump when re-clicking
            return;
        }

      SDL_GetMouseState(&mx, &my);

      if (mouse.first) {
          mouse.lastX = mx;
          mouse.lastY = my;
          mouse.first = false;
          return;
      }

      float dx = mx - mouse.lastX;
      float dy = my - mouse.lastY;

      mouse.lastX = mx;
      mouse.lastY = my;

      float yaw   = dx * RotSpeed;
      float pitch = dy * RotSpeed;

      cam.Rotate(-pitch/1000.f, yaw/1000.f, 0.0f);
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
  void TranslateCamera(camera&e,float dt,bool isActive){
   if(!isActive) return;
   const bool* keys = SDL_GetKeyboardState(NULL);
   if (keys[SDL_SCANCODE_W]){
       PDEBUG("w Translate Camera");
       e.Translate(-e.forward * dt*TranslateSpeed);
   }
   if (keys[SDL_SCANCODE_S]){
       PDEBUG("s Translate Camera");
       e.Translate(e.forward * dt*TranslateSpeed);
   }
   if (keys[SDL_SCANCODE_A]){
       PDEBUG("a Translate Camera");
       e.Translate(e.right * dt*TranslateSpeed);
   }
   if (keys[SDL_SCANCODE_D]){
       PDEBUG("d Translate Camera");
       e.Translate(-e.right * dt*TranslateSpeed);
   }
   if (keys[SDL_SCANCODE_SPACE]){
       PDEBUG("space Translate Camera");
       e.Translate(-e.up * dt*TranslateSpeed);
   }
   if (keys[SDL_SCANCODE_LSHIFT]){
       PDEBUG("lshift Translate Camera");
       e.Translate(e.up * dt*TranslateSpeed);
   }

  }
private:
bool bMouseActive = false;
float RotSpeed = 2.0f;
float TranslateSpeed = 2.0f;
Vec3f y_axis=INV::Vec3<float>(0,1,0);
Vec3f x_axis=INV::Vec3<float>(1,0,0);
Vec3f z_axis=INV::Vec3<float>(0,0,1);
};
