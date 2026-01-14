//#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <cstdint>
#include <iostream>
#include <memory>
#include<algorithm>
#include "Renderer.h"


void UpdateColor(INV::Vec3<uint8_t>& color,INV::Vec3<uint8_t> u_color)
{
  color=u_color;
}

void UpdateLocation(INV::Vec2<double>& A, float x , float y,float deltatime){
    A.x+=x;
    A.y+=y;
}
int main(int argc, char* argv[])
{
   // SDL_SetMainReady();

    if (!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS)) {
           SDL_Log("SDL_Init Error: %s", SDL_GetError());
           return -1;
       }

    auto r = std::make_unique<renderer>(
        1, std::make_unique<INV::Window>(512, 512, "Main_Window")
    );

    INV::Vec2<uint16_t> dims = r->GetDimensions();

    SDL_Window* window = SDL_CreateWindow(
        "SDL3 + MSVC",
        dims.x, dims.y,
        SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, nullptr);

    SDL_Texture* texture = SDL_CreateTexture(
        sdlRenderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        dims.x, dims.y
    );

    const uint8_t* pixels = r->GetColorBufferBytes();
    int pitch = dims.x * 3;

    bool running = true;
    SDL_Event e;

    INV::Vec2<double> A(45,45);
     INV::Vec2<double> B(200,0);
     INV::Vec2<double> C(0,200);

     INV::Vec3<uint8_t> w_color(1,1,121);
     INV::Vec3<uint8_t> col(178,72,123);
     INV::Vec3<uint8_t> U_Color(123,234,13);
     uint64_t counter=0;
     uint16_t switcher=0;
     bool switchb=false;


     while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }
        static float lastTime = 0.0f;
        float time = SDL_GetTicks() / 1000.0f;
        float deltaTime = time - lastTime;
        lastTime = time;

        r->ClearColor(INV::Vec4<uint8_t>(w_color, 255));
        r->DrawTriangle(A, B, C, col);
        UpdateColor(col,U_Color);
       counter=(counter+time)/dims.x-std::sin(time);
       counter=std::clamp((float)counter,0.0f,(float)dims.x-1);
        float y = std::sin(time);
        float z = std::cos(time);

        U_Color.x=abs(sin(time/2))*255;
        U_Color.y=abs(cos(time/2))*255;
        U_Color.z=abs(sin(time))*255;

        UpdateLocation(A,y,z,deltaTime);
        UpdateLocation(B,y,z,deltaTime);
        UpdateLocation(C,y,z,deltaTime);

       A.x=std::clamp((float)A.x,0.0f,(float)dims.x-1);
       B.x=std::clamp((float)B.x,0.0f,(float)dims.x-1);
       C.x=std::clamp((float)C.x,0.0f,(float)dims.x-1);

       A.y=std::clamp((float)A.y,0.0f,(float)dims.y-1);
       B.y=std::clamp((float)B.y,0.0f,(float)dims.y-1);
       C.y=std::clamp((float)C.y,0.0f,(float)dims.y-1);

        SDL_UpdateTexture(texture, nullptr, pixels, pitch);
        SDL_RenderClear(sdlRenderer);


        SDL_RenderTexture(sdlRenderer, texture, nullptr, nullptr);
        SDL_RenderPresent(sdlRenderer);
        }


    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
