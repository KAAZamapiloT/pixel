
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
     template<typename p>
    void DrawTriangle(INV::Vec2<p> p1,INV::Vec2<p> p2,INV::Vec2<p> p3,INV::Vec3<uint8_t> colors ){


       uint16_t mix=std::min({p1.x,p2.x,p3.x});
       uint16_t max=std::max({p1.x,p2.x,p3.x});

       uint16_t may=std::max({p1.y,p2.y,p3.y});
       uint16_t miy=std::min({p1.y,p2.y,p3.y});

       for(int i=miy;i<=may;++i){
         for(int j=mix;j<=max;++j){

           if(InsideTrig(INV::Vec2<p>(j,i),p1,p2,p3)){
             SetPixelColor(INV::Vec2<uint16_t>(j,i),colors);
           }

         }
       }
     }

     // drawing with a color function
      template<typename F>
     void DrawTriangle(INV::Vec2<F> p1,INV::Vec2<F>p2,INV::Vec2<F>p3,INV::Vec3<uint8_t> basecolor

         ,INV::Vec3<uint8_t>(*X)(INV::Vec2<uint16_t>,float)){


             uint16_t mix=std::min({p1.x,p2.x,p3.x});
             uint16_t max=std::max({p1.x,p2.x,p3.x});

             uint16_t may=std::max({p1.y,p2.y,p3.y});
             uint16_t miy=std::min({p1.y,p2.y,p3.y});


float p=256.0/static_cast<float>(may-miy);
             for(uint16_t i=miy;i<=may;++i){
               for(uint16_t j=mix;j<=max;++j){
                  if(InsideTrig(INV::Vec2<uint16_t>(j,i),p1,p2,p3)){
                    SetPixelColor(INV::Vec2<uint16_t>(j,i),X(INV::Vec2<uint16_t>(j,i),p));

                  }
                }
              }

     }
     template<typename p>
     void DrawPlane(INV::Vec2<p> p1,INV::Vec2<p>p2,INV::Vec2<p>p3,INV::Vec2<p> p4,INV::Vec3<uint8_t> color){

       DrawTriangle(p1,p2,p4,color);
       DrawTriangle(p1,p2,p3,color);

     }

     void DrawPolynomial(float(*px)(float) ,INV::Vec2<uint16_t>start,INV::Vec2<uint16_t>end,INV::Vec3<uint8_t> Color){

       int xs=start.x;
       int xe=end.x;
       if(xe<xs){
         std::cerr<<"INVALID FORMAT END SHOULD BE GREATER THAN START\n"<<std::endl;
         return;
       }
       INV::Vec2<uint16_t> dims=GetDimensions();
       for(int i=start.x;i<end.x;++i){
          int y=static_cast<int>(px(i));
          if(y>=dims.y||y<0) continue;
           SetPixelColor(INV::Vec2<uint16_t>(i,y),Color);
           if(i==0) continue;
           linear_interpolation(INV::Vec2<uint16_t>(i-1,px(i)),INV::Vec2<uint16_t>(i,y),Color);
           printf("inter");
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


     void Draw_Cube(INV::Vec3<uint16_t> p1,INV::Vec3<uint16_t>p2,INV::Vec3<uint16_t>p3,INV::Vec2<uint16_t>p4
         ,INV::Vec3<uint16_t> p5,INV::Vec3<uint16_t>p6,INV::Vec3<uint16_t> p7,INV::Vec3<uint16_t> p8,INV::Vec3<uint16_t> Color){



     }


  private:
    uint8_t m_id;
    std::unique_ptr<INV::Window> m_Window;
template<typename T>
    bool InsideTrig(INV::Vec2<T> Point,INV::Vec2<T> a,INV::Vec2<T> b,INV::Vec2<T> c){


      INV::Vec2<double> ab=INV::Vec2<double>(b.x,b.y)-INV::Vec2<double>(a.x,a.y);
      INV::Vec2<double> ac=INV::Vec2<double>(c.x,c.y)-INV::Vec2<double>(a.x,a.y);

      INV::Vec2<double> ap=INV::Vec2<double>(Point.x,Point.y)-INV::Vec2<double>(a.x,a.y);

    INV::Vec2<double> v0=ab;
    INV::Vec2<double> v1=ac;
    INV::Vec2<double> v2=ap;

    double d00=v0.Dot(v0);
    double d01=v0.Dot(v1);
    double d11=v1.Dot(v1);
    double d20=v2.Dot(v0);
    double d21=v2.Dot(v1);

    double denominator=d00*d11-d01*d01;
    double u=(d11*d20-d01*d21)/denominator;
    double v=(d00*d21-d01*d20)/denominator;
    double w=1-u-v;

    return(u>=0&&v>=0&&w>=0);
    }
   void linear_interpolation(INV::Vec2<uint16_t> p1,INV::Vec2<uint16_t>p2,INV::Vec3<uint8_t> color){

     DrawLine(p1,p2,color);


   }
};
