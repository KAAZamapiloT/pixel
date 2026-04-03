//#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "include/Objects.h"
#include <atomic>
#include <cstdint>
#include <iostream>
#include <memory>
#include<algorithm>
#include "Renderer.h"
#include "include/Math_Utils.h"
#include "include/EventController.h"

void UpdateColor(INV::Vec3<uint8_t>& color,INV::Vec3<uint8_t> u_color)
{
  color=u_color;
}

void UpdateLocation(INV::Vec2<float>& A, float x , float y,float deltatime){
    A.x+=x*deltatime;
    A.y+=y*deltatime;
}
INV::Vec3<uint8_t> Gradient(Vec3f pos)
{
    int x=pos.x;
    int y=pos.y;
    int z=pos.z;
    return INV::Vec3<uint8_t>((12*(x+1))%255, 12*(y+1)%255, 12*(z+1)%255);
}
INV::Vec3<uint8_t> DebugShader(Vec3f pos) {
    return {
        (uint8_t)((pos.x + 1.0f) * 121),
        (uint8_t)((pos.y + 1.0f) * 121),
        (uint8_t)((pos.z + 1.0f) * 121)
    };
}
INV::Vec3<uint8_t> ZDebugShader(Vec3f pos) {
    float z = pos.z;

    // normalize assuming range ~[-r, r]
    float t = (z + 1.0f) * 0.5f; // map [-1,1] → [0,1]

    t = std::clamp(t, 0.0f, 1.0f);

    return {
        (uint8_t)(t * 255),        // red
        0,
        (uint8_t)((1.0f - t) * 255) // blue
    };
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
   // SDL_SetWindowRelativeMouseMode(window, true);
   // SDL_SetWindowMouseGrab(window, true);



    const uint8_t* pixels = r->GetColorBufferBytes();
    int pitch = dims.x * 4;

    bool running = true;
    SDL_Event e;

    INV::Vec2<float> A(145,145);
     INV::Vec2<float> B(500,120);
     INV::Vec2<float> C(20,300);

     INV::Vec3<uint8_t> w_color(1,1,12);
     INV::Vec3<uint8_t> col(178,72,123);
     INV::Vec3<uint8_t> U_Color(123,234,13);

Example exp;

Entity sphere(MeshFactory::CreateSphere(1,60,60));
sphere.transform.position = INV::Vec3<float>(0,0,1);
sphere.transform.scale=Vec3f(3.0f,1.0f,1.0f);
Material Smat;
Smat.color = INV::Vec3<uint8_t>(250,250,250);
Smat.shader = ZDebugShader;

camera camera(ECameraType::Perspective,INV::Vec3<float>(0,0,0),60.f,static_cast<float>(dims.x/dims.y),0.1f,100.f);
EventController CC;
INV::Matrix4<float> projectionViewMatrix = camera.GetProjectionView();
INV::Matrix4<float> viewMatrix = camera.GetViewMatrix();
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
CubeE.transform.position={0,0,0};
CubeE.transform.scale=Vec3f(1.0f,1.0f,3.0f);
CubeE.transform.rotation=quat(90,Vec3f(0,1,0));
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
//INV::Matrix3<float> modelMatrix = Math::ScaleRotateTranslateMatrix2D(1.0000001,0,0,0);
Mat4f modal=Math::ScaleRotateTranslateMatrix3D(1.0000001,quat(0,0,0,0),2,2,0);
INV::Vec4<float> A3=INV::Vec4<float>(A.x,A.y,3,1);
INV::Vec4<float> B3=INV::Vec4<float>(B.x,B.y,3,1);
INV::Vec4<float> C3=INV::Vec4<float>(C.x,C.y,3,1);
//A3=modal.Matrix4_Vec4_mul(modal,A3);
//B3=modal.Matrix4_Vec4_mul(modal,B3);
//C3=modal.Matrix4_Vec4_mul(modal,C3);
INV::Vec2<float>center(100,100);


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


     //  r->DrawTriangle(A, B, C,col);
 //  r->DrawTriangle3D(camera,INV::Vec3<float>(-1, -1, 2),INV::Vec3<float>( 1, -1, 2),INV::Vec3<float>( 1,  1, 2),col,nullptr);
     //   exp.DepthTest1(r, camera);
     //  exp.DepthTest2(r, camera);

    //   exp.CubeTest(r, camera, col);
        CC.ImpactCamera(camera , e , true , deltaTime);
        CC.TranslateCamera(camera, deltaTime, true);
        CC.MouseImpactCamera(camera, deltaTime);
    //   exp.Rotate_Cube(1*deltaTime,INV::Vec3<float>(0,1,0));
    //   r->RenderMesh(camera,sphere.mesh,sphere.transform,Smat);
    r->RenderMesh(camera,CubeE.mesh,CubeE.transform,Smat);
       Smat.color=col;
     //r->DrawCircle(center, 10.0f, col, true);

     //center.x=250+sin(time)*200;
     //center.y=250+cos(time)*200;

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
