
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
     virtual void DrawLine(INV::Vec2<uint16_t> start,INV::Vec2<uint16_t> end,INV::Vec3<uint8_t> Color){
     INV::Vec2<uint16_t> dim=GetDimensions();
     if(start.x>end.x){
         std::cerr<<"invalid arguments"<<std::endl;
         return;
     }
      float slope=(float)(end.y-start.y)/(end.x-start.x);

      float constant=start.y-slope*start.x;
            for(uint16_t i=start.x;i<=end.x;++i){
                uint16_t y=round(slope*i+constant);
                SetPixelColor(INV::Vec2<uint16_t>{i,y},Color);
            }

     }

     //virtual void DrawPlane()=0;
     virtual void DrawTriangle(INV::Vec2<uint16_t> p1,INV::Vec2<uint16_t> p2,INV::Vec2<uint16_t> p3,INV::Vec3<uint8_t> colors  ){
       INV::Vec2<uint16_t> dims=GetDimensions();
       for(int i=0;i<dims.y;++i){
         for(int j=0;j<dims.x;++j){

           if(InsideTrig(INV::Vec2<uint16_t>(j,i),p1,p2,p3)){
             SetPixelColor(INV::Vec2<uint16_t>(j,i),colors);
           }

         }
       }
     }
     void SetPixelColor(INV::Vec2<uint16_t> cord,INV::Vec3<uint8_t> Color){
         m_Window->SetPixelColor(cord,Color);
     }
     void SetPixelColor(uint32_t index,INV::Vec3<uint8_t> Color){
         m_Window->SetPixelColor(index,Color);
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


         for(uint16_t i=0;i<dim.y;++i){
           for(uint16_t j=0;j<dim.x;++j){

            // INV::Vec3<uint8_t> Col={i,j,128};
            INV::Vec3<uint8_t> Color=m_Window->GetColor(INV::Vec2<uint16_t>{j,i});
            outFile << static_cast<int>((Color.x)) << " "
                                << static_cast<int>((Color.y)) << " "
                                << static_cast<int>((Color.z)) << " ";

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

    bool InsideTrig(INV::Vec2<uint16_t> Point,INV::Vec2<uint16_t> a,INV::Vec2<uint16_t> b,INV::Vec2<uint16_t> c){


      INV::Vec2<float> ab=INV::Vec2<float>(b.x,b.y)-INV::Vec2<float>(a.x,a.y);
      INV::Vec2<float> ac=INV::Vec2<float>(c.x,c.y)-INV::Vec2<float>(a.x,a.y);

      INV::Vec2<float> ap=INV::Vec2<float>(Point.x,Point.y)-INV::Vec2<float>(a.x,a.y);

    INV::Vec2<float> v0=ab;
    INV::Vec2<float> v1=ac;
    INV::Vec2<float> v2=ap;

    float d00=v0.Dot(v0);
    float d01=v0.Dot(v1);
    float d11=v1.Dot(v1);
    float d20=v2.Dot(v0);
    float d21=v2.Dot(v1);

    float denominator=d00*d11-d01*d01;
    float u=(d11*d20-d01*d21)/denominator;
    float v=(d00*d21-d01*d20)/denominator;
    float w=1-u-v;
    return(u>=0&&v>=0&&w>=0);


    }
};
