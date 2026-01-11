//#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>
#include <memory>
#include<algorithm>
#include "Renderer.h"


void UpdateColor(INV::Vec3<uint8_t>& color,float deltatime)
{
  color.x=255*std::sin(std::sin(deltatime)*color.x+1*std::sin(deltatime));
  color.y=255*std::cos(std::cos(deltatime)*color.y)+1*std::sin(deltatime);
  color.z=255*std::cos(std::sin(deltatime+1)*color.z+1*std::sin(deltatime));
}

void UpdateLocation(INV::Vec2<double>& A, float x , float y,float deltatime){
    A.x+=x*deltatime;
    A.y+=y*deltatime;
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
     INV::Vec3<uint8_t> col=(178,72,123);
     while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }
        float time = SDL_GetTicks() / 1000.0f;

        r->ClearColor(INV::Vec4<uint8_t>(w_color, 255));
        r->DrawTriangle(A, B, C, col);
        UpdateColor(col,time);
        float y = std::sin(time);
        float z = std::cos(time);
        UpdateLocation(A,y,z,time);
       // UpdateLocation(B,10*abs(std::sin(SDL_GetTicks()/1000.0)),std::sin(SDL_GetTicks()/1000.0),(SDL_GetTicks()/1000.0));
       // UpdateLocation(C,10*abs(std::sin(SDL_GetTicks()/1000.0)),0,std::cos(SDL_GetTicks()/1000.0));
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
