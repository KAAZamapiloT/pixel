#pragma once
#include "Camera.h"
#include"Math_Utils.h"
#include <cstdint>
#include <cstdio>
#include <iostream>
#include<string>
#include<fstream>


namespace INV{
    class Window{
    public:
      Window(uint16_t width,uint16_t height,std::string name){
                    m_width=width;
                    m_height=height;
                    m_name=name;
                    frame_buffer=std::vector<Vec4<uint8_t>>(width*height,{0,0,0,0});
                    depth_buffer=std::vector<uint8_t>(width*height,{0});


      }
      inline uint16_t GetWidth(){return m_width;}
      inline uint16_t GetHeight(){return m_height;}

      void SetPixelColor(Vec2<uint16_t> cord,Vec3<uint8_t> Color){
        frame_buffer[cord.x + cord.y * m_width].x=Color.x;
        frame_buffer[cord.x + cord.y * m_width].y=Color.y;
        frame_buffer[cord.x + cord.y * m_width].z=Color.z;
      }
      void SetPixelColor(Vec2<uint16_t> cord,Vec4<uint8_t> Color){

          int c = cord.x + cord.y * m_width;
              float srcA = Color.w / 255.0f;
              float srcR = Color.x / 255.0f;
              float srcG = Color.y / 255.0f;
              float srcB = Color.z / 255.0f;

              float dstR = frame_buffer[c].x / 255.0f;
              float dstG = frame_buffer[c].y / 255.0f;
              float dstB = frame_buffer[c].z / 255.0f;

              float outR = srcR * srcA + dstR * (1.0f - srcA);
              float outG = srcG * srcA + dstG * (1.0f - srcA);
              float outB = srcB * srcA + dstB * (1.0f - srcA);

              frame_buffer[c].x = (uint8_t)(outR * 255.0f);
              frame_buffer[c].y = (uint8_t)(outG * 255.0f);
              frame_buffer[c].z = (uint8_t)(outB * 255.0f);
              frame_buffer[c].w = 255;
      }
      void SetPixelColor(uint32_t index,Vec3<uint8_t> Color){

        frame_buffer[index].x=Color.x;
         frame_buffer[index].y=Color.y;
          frame_buffer[index].z=Color.z;
      }
      void SetPixelColor(uint32_t index,Vec4<uint8_t> Color){
              int c = index;
              float srcA = Color.w / 255.0f;
              float srcR = Color.x / 255.0f;
              float srcG = Color.y / 255.0f;
              float srcB = Color.z / 255.0f;

              float dstR = frame_buffer[c].x / 255.0f;
              float dstG = frame_buffer[c].y / 255.0f;
              float dstB = frame_buffer[c].z / 255.0f;

              float outR = srcR * srcA + dstR * (1.0f - srcA);
              float outG = srcG * srcA + dstG * (1.0f - srcA);
              float outB = srcB * srcA + dstB * (1.0f - srcA);

              frame_buffer[c].x = (uint8_t)(outR * 255.0f);
              frame_buffer[c].y = (uint8_t)(outG * 255.0f);
              frame_buffer[c].z = (uint8_t)(outB * 255.0f);
              frame_buffer[c].w = 255;
      }
      Vec3<uint8_t> GetColor(Vec2<uint16_t> cord){
          int c=cord.x + cord.y * m_width;
        return INV::Vec3<uint8_t>(frame_buffer[c].x,frame_buffer[c].y,frame_buffer[c].z);
      }

      Vec3<uint8_t> GetColor(uint32_t dex){
          return INV::Vec3<uint8_t>(frame_buffer[dex].x,frame_buffer[dex].y,
              frame_buffer[dex].z);
      }

      Vec4<uint8_t> GetColor_A(Vec2<uint16_t> cord){
          int c=cord.x + cord.y * m_width;
        return frame_buffer[c];
      }

      Vec4<uint8_t> GetColor_A(uint32_t dex){
          return frame_buffer[dex];
      }


      uint16_t m_width,m_height;
      std::string m_name;
      std::vector<Vec4<uint8_t>> frame_buffer;

      // really useful for ovellaping images
      std::vector<uint8_t> depth_buffer;

    };
}


class renderer{

  public:

    renderer(uint8_t id,std::unique_ptr<INV::Window> wind)
    {
    m_id=id;
    m_Window=std::move(wind);
    }

   //---------------------Mods-----------------------------//
void DrawLine(INV::Vec2<float> start,INV::Vec2<float> end,INV::Vec3<uint8_t> Color){

     INV::Vec2<uint16_t> dim=GetDimensions();
     if (start.x > end.x)
        std::swap(start, end);
     float dx=end.x-start.x;
     float dy=end.y-start.y;
     uint16_t steps=static_cast<uint16_t>(std::max(std::abs(dx),std::abs(dy)));
     if(steps==0) return;

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x=start.x;
    float y=start.y;

     for(uint16_t i=start.x;i<=end.x;++i){
         SetPixelColor(INV::Vec2<uint16_t>(i,y),Color);

         // FCG impl
         if(-dy*i+dx*y+(start.x*end.y-start.x*end.y)<0){
            y+=yInc;
         }
     }

}
void DrawLine(INV::Vec2<float> start,INV::Vec2<float> end,INV::Vec3<uint8_t> Color,
    INV::Vec3<uint8_t>(*F)(INV::Vec2<uint16_t>,float) )
{
 float p=256.0/static_cast<float>(end.x-start.x);
 float slope=(float)(end.y-start.y)/(end.x-start.x);

 float constant=start.y-slope*start.x;
       for(int i=start.x;i<=end.x;++i){
           int y=round(slope*i+constant);
          if(y<0) continue;
           SetPixelColor(INV::Vec2<uint16_t>(i,y),F(INV::Vec2<uint16_t>(i,y),1));
       }

}


    void DrawTriangle(INV::Vec2<float> p1,INV::Vec2<float> p2,INV::Vec2<float> p3,INV::Vec3<uint8_t> colors ){


       int mix=std::min({p1.x,p2.x,p3.x});
       int max=std::max({p1.x,p2.x,p3.x});

       int may=std::max({p1.y,p2.y,p3.y});
       int miy=std::min({p1.y,p2.y,p3.y});

       mix = std::max(mix, 0);
       miy = std::max(miy, 0);
       max = std::min(max, m_Window->m_width  - 1);
       may= std::min(may,m_Window->m_height - 1);

       for(int i=miy;i<=may;++i){
         for(int j=mix;j<=max;++j){

           if(InsideTrig(INV::Vec2<float>(j,i),p1,p2,p3)){
             SetPixelColor(INV::Vec2<uint16_t>(j,i),colors);
           }

         }
       }
     }

     // drawing with a color function

     void DrawTriangle(INV::Vec2<float> p1,INV::Vec2<float>p2,INV::Vec2<float>p3,INV::Vec3<uint8_t> basecolor

         ,INV::Vec3<uint8_t>(*X)(INV::Vec2<uint16_t>,float)){


             int mix=std::min({p1.x,p2.x,p3.x});
             int max=std::max({p1.x,p2.x,p3.x});

             int may=std::max({p1.y,p2.y,p3.y});
             int miy=std::min({p1.y,p2.y,p3.y});


             mix = std::max(mix, 0);
             miy = std::max(miy, 0);
             max = std::min(max, m_Window->m_width  - 1);
             may= std::min(may,m_Window->m_height - 1);

             float p=256.0/static_cast<float>(may-miy);
             for(int i=miy;i<may;++i){
               for(int j=mix;j<=max;++j){
                  if(InsideTrig(INV::Vec2<float>(j,i),p1,p2,p3)){
                    SetPixelColor(INV::Vec2<uint16_t>(j,i),X(INV::Vec2<uint16_t>(j,i),p));

                  }
                }
              }

     }
     void DrawPlane(INV::Vec2<float> p1,INV::Vec2<float>p2,INV::Vec2<float>p3,INV::Vec2<float> p4,INV::Vec3<uint8_t> color){

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
    /*  void Create_PPM_File(std::string filename){
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

*/

     //---------------------Getters-----------------------------//
     INV::Vec3<uint8_t> GetColor(INV::Vec2<uint16_t> cord){
         return m_Window->GetColor(cord);
     }

     INV::Vec2<uint16_t> GetDimensions(){
         return {m_Window->GetWidth(),m_Window->GetHeight()};
     }

//-----------------------------------
     void Draw_Cube(INV::Vec3<uint16_t> p1,INV::Vec3<uint16_t>p2,INV::Vec3<uint16_t>p3,INV::Vec2<uint16_t>p4
         ,INV::Vec3<uint16_t> p5,INV::Vec3<uint16_t>p6,INV::Vec3<uint16_t> p7,INV::Vec3<uint16_t> p8,INV::Vec3<uint16_t> Color){



     }

     // Drawing a triangle in 3d space but then it can also accept a function pointer(can be passes as null)
    // but here main thing is to set color val
  // assuming world space cordinates-> otherwise local->world transformation
  void Draw_Triangle_3d(camera&cam,INV::Vec3<float> p1,INV::Vec3<float> p2,INV::Vec3<float> p3,
      INV::Vec3<uint8_t> color,INV::Vec3<uint8_t> (*f)(INV::Vec3<float>)
  ){
      INV::Vec3<float> maxvals;
      INV::Vec3<float> minvals;
      minvals.x=std::min({p1.x,p2.x,p3.x});
      minvals.y=std::min({p1.y,p2.y,p3.y});
      minvals.z=std::min({p1.z,p2.z,p3.z});
      maxvals.x=std::max({p1.x,p2.x,p3.x});
      maxvals.y=std::max({p1.y,p2.y,p3.y});
      maxvals.z=std::max({p1.z,p2.z,p3.z});

     INV::Matrix4<float> ProjectionView = cam.GetProjectionView();

      if(f==nullptr){
          for(int i=minvals.z;i<=maxvals.z;++i){
              for(int j=minvals.y;j<=maxvals.y;++j){
                  for(int k=minvals.x;k<=maxvals.x;++k){
                    INV::Vec4<float>p=INV::Vec4<float>(k,j,i,1);
                    INV::Vec4<float>clip=INV::Matrix4<float>::Matrix4_Vec4_mul(ProjectionView,p);

                    INV::Vec3<float> ndc=INV::Vec3<float>(clip.x/clip.w,clip.y/clip.w,clip.z/clip.w);
                    INV::Vec2<float> screen=INV::Vec2<float>((ndc.x+1)*0.5*m_Window->m_width,(1-ndc.y)*0.5*m_Window->m_height);
                    if(screen.x>=0 && screen.x<m_Window->m_width && screen.y>=0 && screen.y<m_Window->m_height){
                        INV::Vec3<uint8_t>C(color.x,color.y,color.z);
                        uint16_t c=screen.y*m_Window->m_width+screen.x;
                         if(InsideTriangle_3D(INV::Vec3<float>(INV::Vec3<float>(i,j,k)),p1, p2,p3)){
                          SetPixelColor(c,C);
                         }

                    }
                  }
              }
          }
      }else{
          for(int i=minvals.z;i<=maxvals.z;++i){
              for(int j=minvals.y;j<=maxvals.y;++j){
                  for(int k=minvals.x;k<=maxvals.x;++k){
                    INV::Vec4<float>p=INV::Vec4<float>(k,j,i,1);
                    INV::Vec4<float>clip=INV::Matrix4<float>::Matrix4_Vec4_mul(ProjectionView,p);
                    INV::Vec3<float> ndc=INV::Vec3<float>(clip.x/clip.w,clip.y/clip.w,clip.z/clip.w);
                    INV::Vec2<float> screen=INV::Vec2<float>((ndc.x+1)*0.5*m_Window->m_width,(1-ndc.y)*0.5*m_Window->m_height);
                    if(screen.x>=0 && screen.x<m_Window->m_width && screen.y>=0 && screen.y<m_Window->m_height){

                        if(InsideTriangle_3D(INV::Vec3<float>(INV::Vec3<float>(i,j,k)),p1, p2,p3)){
                      m_Window->SetPixelColor(INV::Vec2<uint16_t>(screen.x,screen.y),f(INV::Vec3<float>(k,j,i)));

                        }
                    }
                  }
              }
          }
      }

      }

   void ClearColor(INV::Vec4<uint8_t> Color){
   //    printf("%d %d",m_Window->frame_buffer.begin(),m_Window->frame_buffer.end());
   std::fill(
       m_Window->frame_buffer.begin(),
       m_Window->frame_buffer.end(),
       Color
   );
   }
   const uint8_t* GetColorBufferBytes() const {
       return reinterpret_cast<const uint8_t*>(m_Window->frame_buffer.data());
   }
  private:
    uint8_t m_id;
    std::unique_ptr<INV::Window> m_Window;

    bool InsideTrig(INV::Vec2<float> Point,INV::Vec2<float> a,INV::Vec2<float> b,INV::Vec2<float> c){


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
    bool InsideTriangle_3D(INV::Vec3<float> Point,INV::Vec3<float> a,INV::Vec3<float> b,INV::Vec3<float> c){
   INV::Vec3<float> ab=b-a;
   INV::Vec3<float> ac=c-a;
   INV::Vec3<float> ap=c-Point;

   INV::Vec3<float> v0=ab;
   INV::Vec3<float> v1=ac;
   INV::Vec3<float> v2=ap;

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
      return true;
    };
   void linear_interpolation(INV::Vec2<uint16_t> p1,INV::Vec2<uint16_t>p2,INV::Vec3<uint8_t> color){

       //TODO: FIX THIS
   //  DrawLine(p1,p2,color);

   }

   bool InsideScreenSpace(INV::Vec2<int> Point,INV::Vec2<float> a,INV::Vec2<float> b,INV::Vec2<float> c){

     bool h=(Point.x>=0 && Point.x<m_Window->m_width && Point.y>=0 && Point.y<m_Window->m_height);
     bool j=(a.x>=0 && a.x<m_Window->m_width && a.y>=0 && a.y<m_Window->m_height);
     bool k=(b.x>=0 && b.x<m_Window->m_width && b.y>=0 && b.y<m_Window->m_height);
     bool l=(c.x>=0 && c.x<m_Window->m_width && c.y>=0 && c.y<m_Window->m_height);
     return(h&&j&&k&&l);
   }
};
