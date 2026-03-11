#pragma once
#include"SDL3/SDL.h"

// controlling camera movements using this class
class EventController{
  public:


  void ImpactCamera(class camera&camera,SDL_Event e,bool bActive=true){
      if(!bActive) return;

      switch(e.type){
          case SDL_KEYDOWN:
              camera.SpeedRotation(quat(1,0,0,1),1.0f);
              break;
          case SDL_KEYUP:
              camera.SpeedRotation(quat(1,0,0,1),-1.0f);
              break;
          case SDL_KEYLEFT:
              camera.SpeedRotation(quat(0,1,0,0),1.0f);
              break;
          case SDL_EVENT_KEYRIGHT:
              camera.SpeedRotation(quat(0,1,0,0),-1.0f);
              break;

      }
  }

};
