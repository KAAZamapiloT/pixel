//#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>
#include <memory>
#include "Renderer.h"

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

    auto dims = r->GetDimensions();

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
     INV::Vec2<double> B(100,100);
     INV::Vec2<double> C(150,150);
INV::Vec3<uint8_t> w_color(1,1,1);
INV::Vec3<uint8_t> col=(78,72,159);
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }

        r->ClearColor(INV::Vec4<uint8_t>(w_color, 255));
        r->DrawTriangle(A, B, C, col);

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
