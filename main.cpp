//#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "include/Objects.h"
#include <atomic>
#include <cstdint>
#include <exception>
#include <iostream>
#include <locale>
#include <memory>
#include<chrono>
#include<algorithm>
#include "Renderer.h"
#include "include/Math_Utils.h"
#include "include/EventController.h"
#include "include/Renderer.h"
#include "include/logger.h"
#include "include/TEST.h"
#include "include/tools/benchmark.h"
#include <tracy/Tracy.hpp>
void UpdateColor(Vec3ui8& color,Vec3ui8& u_color)
{
  color=u_color;
}

void UpdateLocation(Vec2f& A, float x , float y,float deltatime){
    A.x+=x*deltatime;
    A.y+=y*deltatime;
}
Vec3ui8 Gradient(Vec3f pos)
{
    int x=pos.x;
    int y=pos.y;
    int z=pos.z;
    return Vec3ui8((12*(x+1))%255, 12*(y+1)%255, 12*(z+1)%255);
}
Vec3ui8 DebugShader(Vec3f pos) {
    return {
        (uint8_t)((pos.x + 1.0f) * 121),
        (uint8_t)((pos.y + 1.0f) * 121),
        (uint8_t)((pos.z + 1.0f) * 121)
    };
}
Vec3ui8 ZDebugShader(Vec3f pos) {
    float near = 0.1f;
    float far  = 10.0f;

    float z = pos.z;

    float t = (z - near) / (far - near);
    t = std::clamp(t, 0.0f, 1.0f);

    float r = std::clamp(2.0f * t - 1.0f, 0.0f, 1.0f);
    float g = 1.0f - std::abs(2.0f * t - 1.0f);
    float b = std::clamp(1.0f - 2.0f * t, 0.0f, 1.0f);

    return {
        (uint8_t)(r+1 * 255),
        (uint8_t)(g * 255),
        (uint8_t)(b * 255)
    };
}
int main(int argc, char* argv[])
{

  std::cout << "TracyIsConnected = " << TracyIsConnected << std::endl;

  std::cout.flush();

    if (!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS)) {
           SDL_Log("SDL_Init Error: %s", SDL_GetError());
           return -1;
       }

    auto r = std::make_unique<renderer>(
        1, std::make_unique<INV::Window>(512, 512, "Main_Window")
    );

    Vec2ui16 dims = r->GetDimensions();

    TEST test;
    test.P();
    TEST test2;
    test2.S();
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


     Example exp;

    const uint8_t* pixels = r->GetColorBufferBytes();
    int pitch = dims.x * 4;

    bool running = true;
    SDL_Event e;

     Vec2f  A(145,145);
     Vec2f B(500,120);
     Vec2f C(20,300);

     Vec3ui8 w_color(1,1,12);
     Vec3ui8 col(178,72,123);
     Vec3ui8 U_Color(123,234,13);



Entity sphere(MeshFactory::CreateSphere(1,60,60));
sphere.transform.position = Vec3f(0,0,1);
sphere.transform.scale=Vec3f(1.0f,1.0f,1.0f);
Material Smat;
Smat.color = Vec3ui8(250,250,250);
Smat.shader = DebugShader;

camera camera(ECameraType::Perspective,Vec3f(0,0,0),60.f,static_cast<float>(dims.x/dims.y),0.1f,100.f);
EventController CC;
Mat4f projectionViewMatrix = camera.GetProjectionView();
Mat4f viewMatrix = camera.GetViewMatrix();
//////////////////
std::vector<Vec3f> cube1 = {
    Vec3f(-0.5f, -0.5f, 1.5f), // 0
    Vec3f( 0.5f, -0.5f, 1.5f), // 1
    Vec3f( 0.5f,  0.5f, 1.5f), // 2
    Vec3f(-0.5f,  0.5f, 1.5f), // 3

    Vec3f(-0.5f, -0.5f, 2.5f), // 4
    Vec3f( 0.5f, -0.5f, 2.5f), // 5
    Vec3f( 0.5f,  0.5f, 2.5f), // 6
    Vec3f(-0.5f,  0.5f, 2.5f)  // 7
};

std::vector<Vec3f> cube2 = {
    Vec3f(-0.3f, -0.3f, 2.8f), // 0
    Vec3f( 0.7f, -0.3f, 2.8f), // 1
    Vec3f( 0.7f,  0.7f, 2.8f), // 2
    Vec3f(-0.3f,  0.7f, 2.8f), // 3

    Vec3f(-0.3f, -0.3f, 3.8f), // 4
    Vec3f( 0.7f, -0.3f, 3.8f), // 5
    Vec3f( 0.7f,  0.7f, 3.8f), // 6
    Vec3f(-0.3f,  0.7f, 3.8f)  // 7
};

Entity CubeE(MeshFactory::CreateCube(0.5f));
CubeE.transform.position={1,1,0};
CubeE.transform.scale=Vec3f(1.0f,1.0f,1.0f);
CubeE.transform.rotation=quat(1.6,Vec3f(1,1,0));


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

TriangleArray obj = exp.CreateTestTriangle();
float scale_cnt=1.0000001f;
Mat4f modal=Math::ScaleRotateTranslateMatrix3D(1.0000001,quat(0,0,0,0),2,2,0);
Vec4f A3=Vec4f(A.x,A.y,3,1);
Vec4f B3=Vec4f(B.x,B.y,3,1);
Vec4f C3=Vec4f(C.x,C.y,3,1);
Vec2f center(100,100);



r->init();



while (running) {

  

     

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }

        if (e.type == SDL_EVENT_WINDOW_RESIZED) {
            center.x = e.window.data1;
            center.y = e.window.data2;
            r->OnResize(e.window.data1, e.window.data2);

            SDL_DestroyTexture(texture);

            texture = SDL_CreateTexture(
                sdlRenderer,
                SDL_PIXELFORMAT_RGBA32,
                SDL_TEXTUREACCESS_STREAMING,
                center.x, center.y
            );

            pitch = center.x * 4;
            camera.SetAspectRatio(static_cast<float>(center.x), static_cast<float>(center.y));
        }

        static float lastTime = 0.0f;
        float time = SDL_GetTicks() / 1000.0f;
        float deltaTime = time - lastTime;
        lastTime = time;

        r->ClearColor(Vec4ui8(w_color, 255));

        UpdateColor(col,U_Color);

        float y = std::sin(time);
        float z = std::cos(time);

        U_Color.x=abs(sin(time/2))*255;
        U_Color.y=abs(cos(time/2))*255;
        U_Color.z=abs(sin(time))*255;
        CC.ImpactCamera(camera , e , true , deltaTime);
        CC.TranslateCamera(camera, deltaTime, true);
        CC.MouseImpactCamera(camera, deltaTime);
        
        Smat.color=col;
        for(int i=0;i<test.entities.size();i++){
            r->RenderMesh(camera,test.entities[i].mesh,test.entities[i].transform,Smat);
        }
       
        quat orbit = quat(deltaTime, Vec3f(0,1,0));
        for(auto& entity : test.entities) {
            entity.transform.position = orbit.rotate(entity.transform.position);
            entity.transform.rotation = entity.transform.rotation * 0.1*deltaTime;
        }


            TracyPlot("Pixels Tested",
              static_cast<int64_t>(r->PixelsTested));

    TracyPlot("Pixels Inside",
              static_cast<int64_t>(r->PixelsInside));

    TracyPlot("Depth Passed",
              static_cast<int64_t>(r->PixelsDepthPassed));

    TracyPlot("BBox Pixels",
              static_cast<int64_t>(r->BBoxPixels));

          
     
     FrameMark;

         r->PixelsTested = 0;
        r->PixelsInside = 0;
    r->PixelsDepthPassed = 0;
    r->BBoxPixels = 0;
        SDL_UpdateTexture(texture, nullptr, pixels, pitch);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderTexture(sdlRenderer, texture, nullptr, nullptr);
        SDL_RenderPresent(sdlRenderer);

        }

     

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    r->PrintResults();
    return 0;
}
