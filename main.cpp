#include <cstdio>
#include<iostream>
#include<cstdint>
#include <memory>
#include "Renderer.h"
#include "SDL3/SDL.h"


int main(int argc,char* argv){

    std::unique_ptr<renderer> r=std::make_unique<renderer>
    (1,std::make_unique<INV::Window>(512,512,"Main_Window"));

    INV::Vec2<uint16_t> dims=r->GetDimensions();

    // modification loop
      float f=255.0/static_cast<float>(dims.x);
      float g=255.0/static_cast<float>(dims.y);

      if(SDL_Init(SDL_INIT_VIDEO)!=0){
          return -1;
      }
      SDL_Window* window = SDL_CreateWindow(
           "SDL3 + MSVC",
           dims.x, dims.y,
           SDL_WINDOW_RESIZABLE
       );
       bool running = true;
          SDL_Event e;

          while (running) {
              while (SDL_PollEvent(&e)) {
                  if (e.type == SDL_EVENT_QUIT)
                      running = false;
              }
          }

          SDL_DestroyWindow(window);
          SDL_Quit();
/*
    for(uint16_t i=0;i<dims.y;i++){
        for(uint16_t j=0;j<dims.x;j++){

         r->SetPixelColor(INV::Vec2<uint16_t>{j,i},INV::Vec3<uint8_t>(j*i*g,i*f*g,128*i*g));

        }
    }


*/
    INV::Vec2<uint16_t> S(0,0);
    INV::Vec2<uint16_t> U(500,500);
    INV::Vec3<uint8_t> C(255,255,255);

   //r->DrawLine(S,U,C);
   // diaganol -> mirror points color
//    r->DrawPlane(S,U,INV::Vec2<uint16_t>(U.x,0),INV::Vec2<uint16_t>(0,U.y),C);

   //r->DrawPolynomial([](float s){return std::log(s*s)*std::log(s*s*s);},S,U,C);
  //  r->DrawTriangle(S,U,INV::Vec2<uint16_t>(U.x,0),C,[](INV::Vec2<uint16_t> o,float norm){
      //         return INV::Vec3<uint8_t>(o.x*norm,o.y*norm,128);});
    //camera<float> cam(Type::Perspective,INV::Vec3<float>(0.0,0.0,0.0),60.0,dims.y/dims.x,0.001,50.0);
   // r->Draw_Tiangle_3d(cam,INV::Vec3<float>(S.x,S.y,3),INV::Vec3<float>(U.x,U.y,3),INV::Vec3<float>(0,U.y,3),C,nullptr);
 //   r->Create_PPM_File("output.ppm");


    std::cout << "Hello World!" << std::endl;
    return 0;
}

/*
4. Build and Run again
Now that you have modified the code, follow the same two steps:

Compile: cmake --build build

Run: ./build/Debug/pixel_ppm.exe

*/
