
#include"storage.h"
#include <cstdint>
#include <iostream>
#include<string>
#include<fstream>

class renderer{

  public:

    renderer(uint8_t id,std::unique_ptr<INV::Window> wind)
    {
   m_id=id;
   m_Window=std::move(wind);
    }

   //---------------------Mods-----------------------------//
    // virtual void DrawLine()=0;
     //virtual void DrawPlane()=0;
     //virtual void DrawTriangle()=0;
     void SetPixelColor(INV::Vec2<uint16_t> cord,INV::Vec3<uint8_t> Color){
         m_Window->SetPixelColor(cord,Color);
     }

        //---------------------Result-----------------------------//
     void Create_PPM_File(std::string filename){
         INV::Vec2<uint16_t> dim=GetDimensions();
         std::ofstream outFile(filename);
         if(!outFile){
           std::cerr<<"Failed In Creating a File"<<std::endl;
           return;
         }

         outFile<<"P3\n";
         outFile<<dim.x<<" "<<dim.y<<"\n";
         outFile<<"255\n";

         // here is writing pizel data
         //

        float f=255.0/static_cast<float>(dim.y);
         for(uint16_t i=0;i<dim.y;++i){
           for(uint16_t j=0;j<dim.x;++j){

            // INV::Vec3<uint8_t> Col={i,j,128};
            INV::Vec3<uint8_t> Color=m_Window->GetColor(static_cast<uint32_t>(j+i*dim.y));
            printf("\n dexes %d",j+i*dim.y);
            outFile << static_cast<int>(((float)Color.x)*f) << " "
                                << static_cast<int>(((float)Color.y)*f) << " "
                                << static_cast<int>(((float)Color.z)*f) << "  ";
           }
           outFile<<"\n";
         }
         outFile.close();
         std::cout<<"PPM File Created"<<std::endl;

     }



     //---------------------Getters-----------------------------//
     INV::Vec3<uint8_t> GetColor(INV::Vec2<uint16_t> cord){
         return m_Window->GetColor(cord);
     }

     INV::Vec2<uint16_t> GetDimensions(){
         return {m_Window->GetWidth(),m_Window->GetHeight()};
     }


  private:
    uint8_t m_id;
    std::unique_ptr<INV::Window> m_Window;
};
