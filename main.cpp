#include<iostream>
#include<cstdint>
#include <memory>
#include "Renderer.h"



int main(){

    std::unique_ptr<renderer> r=std::make_unique<renderer>
    (1,std::make_unique<INV::Window>(512,512,"Main_Window"));

    INV::Vec2<uint16_t> dims=r->GetDimensions();
    printf("/n %d %d \n",dims.x,dims.y);
    // modification loop
    for(uint16_t i=0;i<dims.x;i++){
        for(uint16_t j=0;j<dims.y;j++){
          r->SetPixelColor(INV::Vec2<uint16_t>(j,i),INV::Vec3<uint8_t>(j,i,128));
        }
    }
    //creation loop
    r->Create_PPM_File("output.ppm");

    std::cout << "Hello World!" << std::endl;
    return 0;
}
/*
4. Build and Run again
Now that you have modified the code, follow the same two steps:

Compile: cmake --build build

Run: ./build/Debug/pixel_ppm.exe

*/
