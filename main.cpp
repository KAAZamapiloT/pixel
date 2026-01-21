//#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <atomic>
#include <cstdint>
#include <iostream>
#include <memory>
#include<algorithm>
#include "Renderer.h"


void UpdateColor(INV::Vec3<uint8_t>& color,INV::Vec3<uint8_t> u_color)
{
  color=u_color;
}

void UpdateLocation(INV::Vec2<float>& A, float x , float y,float deltatime){
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
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        dims.x, dims.y
    );

    const uint8_t* pixels = r->GetColorBufferBytes();
    int pitch = dims.x * 4;

    bool running = true;
    SDL_Event e;

    INV::Vec2<float> A(45,45);
     INV::Vec2<float> B(200,0);
     INV::Vec2<float> C(0,200);

     INV::Vec3<uint8_t> w_color(1,1,121);
     INV::Vec3<uint8_t> col(178,72,123);
     INV::Vec3<uint8_t> U_Color(123,234,13);


camera camera(ECameraType::Perspective,INV::Vec3<float>(0,0,0),60.f,static_cast<float>(dims.x/dims.y),0.1f,1.f);
INV::Matrix4<float> projectionViewMatrix = camera.GetProjectionView();
INV::Matrix4<float> viewMatrix = camera.GetViewMatrix();
for(int i=0;i<4;++i){
    for(int j=0;j<4;++j){
        printf("ProjectionView Matrix Element %d %d: %f\n", i,j, projectionViewMatrix[i][j]);
    }
}
for(int i=0;i<4;++i){
    for(int j=0;j<4;++j){
        printf("View Matrix Element %d %d: %f\n", i,j, viewMatrix[i][j]);
    }
}

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

        UpdateColor(col,U_Color);

        float y = std::sin(time);
        float z = std::cos(time);

        U_Color.x=abs(sin(time/2))*255;
        U_Color.y=abs(cos(time/2))*255;
        U_Color.z=abs(sin(time))*255;

     //   r->DrawTriangle(A, B, C, col);
r->DrawLine(A,B,col);
       // r->DrawLine(A,B+B,col);
     //  r->Draw_Triangle_3d(camera,INV::Vec3<float>(C,12),INV::Vec3<float>(A,12),INV::Vec3<float>(B,12),col,nullptr);
      //  A.x=A.x+sin(time)*deltaTime*100;
      //  B.x=B.x+cos(time)*deltaTime*100;
      //  C.x=C.x+sin(time)*deltaTime*100;

        float x=1;
        x=std::clamp(x,0.8f,1.2f);
      //  A = Math::ScaleMatrix2D(x+abs(std::sin(time))) * A;
      //  B = Math::ScaleMatrix2D(x+abs(std::sin(time))) * B;
      //  C = Math::ScaleMatrix2D(x+abs(std::sin(time))) * C;
        x+=time;
        SDL_UpdateTexture(texture, nullptr, pixels, pitch);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderTexture(sdlRenderer, texture, nullptr, nullptr);
        SDL_RenderPresent(sdlRenderer);
        }


    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
