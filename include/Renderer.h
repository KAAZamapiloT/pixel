// Renderer.h

#pragma once
#include "Camera.h"
#include"Math_Utils.h"
#include "Objects.h"
#include <cstdint>
#include<algorithm>
#include<vector>
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
                    depth_buffer = std::vector<float>(width * height, std::numeric_limits<float>::infinity());


      }
      inline uint16_t GetWidth(){return m_width;}
      inline uint16_t GetHeight(){return m_height;}

      void SetPixelColor(Vec2<uint16_t> cord,Vec3<uint8_t> Color){

   if(cord.x >= m_width || cord.y >= m_height) return;
          frame_buffer[cord.x + cord.y * m_width].x=Color.x;
        frame_buffer[cord.x + cord.y * m_width].y=Color.y;
        frame_buffer[cord.x + cord.y * m_width].z=Color.z;
      }
      void SetPixelColor(Vec2<uint16_t> cord,Vec4<uint8_t> Color){
if(cord.x >= m_width || cord.y >= m_height) return;
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
        if(index >=m_width * m_height) return;
        frame_buffer[index].x=Color.x;
         frame_buffer[index].y=Color.y;
          frame_buffer[index].z=Color.z;
      }
      void SetPixelColor(uint32_t index,Vec4<uint8_t> Color){
              if(index >=m_width * m_height) return;
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
      std::vector<float> depth_buffer;

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
void DrawTraingles3D(TriangleArray&Tri,camera&Cam){
    for(size_t i=0;i<Tri.triangles.size();++i){

    }
}
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
  void DrawTriangle3D(camera&cam,INV::Vec3<float> p1,INV::Vec3<float> p2,INV::Vec3<float> p3,
      INV::Vec3<uint8_t> color,INV::Vec3<uint8_t> (*f)(INV::Vec3<float>)
  ){


     INV::Matrix4<float> ProjectionView = cam.GetProjectionView();
     Vec4f a(p1,1);
     Vec4f b(p2,1);
     Vec4f c(p3,1);

     Vec4f a1 = ProjectionView.Matrix4_Vec4_mul(ProjectionView, a);
     Vec4f b1 = ProjectionView.Matrix4_Vec4_mul(ProjectionView, b);
     Vec4f c1 = ProjectionView.Matrix4_Vec4_mul(ProjectionView, c);

     Vec3f ndc_a(a1.x/a1.w,a1.y/a1.w,a1.z/a1.w);
     Vec3f ndc_b(b1.x/b1.w,b1.y/b1.w,b1.z/b1.w);
     Vec3f ndc_c(c1.x/c1.w,c1.y/c1.w,c1.z/c1.w);


     // preventing warap arounds
     if (a1.w > 0 && b1.w > 0 && c1.w > 0)
         return;

     Vec2f screen_a(
         static_cast<float>((ndc_a.x + 1.0f) * 0.5f * m_Window->m_width),
         static_cast<float>((1.0f - ndc_a.y) * 0.5f * m_Window->m_height)
     );

     Vec2f screen_b(
         static_cast<float>((ndc_b.x + 1.0f) * 0.5f * m_Window->m_width),
         static_cast<float>((1.0f - ndc_b.y) * 0.5f * m_Window->m_height)
     );

     Vec2f screen_c(
         static_cast<float>((ndc_c.x + 1.0f) * 0.5f * m_Window->m_width),
         static_cast<float>((1.0f - ndc_c.y) * 0.5f * m_Window->m_height)
     );

     int32_t MAx=std::max({screen_a.x,screen_b.x,screen_c.x});
     int32_t MAy=std::max({screen_a.y,screen_b.y,screen_c.y});
      int32_t MIy=std::min({screen_a.y,screen_b.y,screen_c.y});
        int32_t MIx=std::min({screen_a.x,screen_b.x,screen_c.x});

     if(MAx<MIx){
         std::swap(MAx,MIx);

     }
     if(MAy<MIy){
         std::swap(MAy,MIy);

     }

     MAx=std::min(MAx,static_cast<int32_t>(m_Window->m_width));
     MAy=std::min(MAy,static_cast<int32_t>(m_Window->m_height));
     MIx=std::max(MIx,0);
     MIy=std::max(MIy,0);

     Vec3f v1=p1-p2;
     Vec3f v2=p2-p1;
     Vec3f PlaneNormal=v1.Cross(v2);
      if(f==nullptr){

          for(int i=MIx;i<=MAx;i++){
              for(int j=MIy;j<=MAy;j++){
                  if(InsideTrig(Vec2f(i,j),screen_a,screen_b,screen_c)){
                      Vec3f w=BaryCentric(Vec2f(i,j),screen_a,screen_b,screen_c);
                      float depth=w.x*ndc_a.z+w.y*ndc_b.z+w.z*ndc_c.z;
                      if(SetDepthBuffer(INV::Vec2<uint16_t>(i,j),depth)){
                      SetPixelColor(INV::Vec2<uint16_t>(i,j),color);
                      }

                  }
              }
          }
      }else{

      }

      }

      void DrawCircle(INV::Vec2<float> center , float radius,INV::Vec3<uint8_t>col,bool filled){

          int minx=std::max({0,(int)(center.x-radius)});
          int miy=std::max({0,(int)(center.y-radius)});
          int maxx=
              (m_Window->m_width)>static_cast<int>(center.x+radius)?
              static_cast<int>(center.x+radius):m_Window->m_width;
          int mayy=(m_Window->m_height)>static_cast<int>(center.y+radius)?
          static_cast<int>(center.y+radius):m_Window->m_height;

          // A deterministick counting points approach could be made here
          if(filled){
          for(int x=minx;x<maxx;x++){
              for(int y=miy;y<mayy;y++){
                  float dx=x-center.x;
                  float dy=y-center.y;
                  if(dx*dx+dy*dy<=radius*radius){
                      SetPixelColor(INV::Vec2<uint16_t>(x,y), col);
                  }
              }
          }
          }else{
              for(int x=minx;x<maxx;x++){
                  for(int y=miy;y<mayy;y++){
                      float dx=x-center.x;
                      float dy=y-center.y;
                      if(dx*dx+dy*dy==radius*radius){
                          SetPixelColor(INV::Vec2<uint16_t>(x,y), col);
                      }
                  }
              }
          }
      }

      bool SetDepthBuffer(INV::Vec2<uint16_t>cord,float depth){
          if (cord.x >= m_Window->m_width || cord.y >= m_Window->m_height)
                return false;
          int c = cord.x + cord.y * m_Window->m_width;

          if(c<0){
              return false;
          }
          if(m_Window->depth_buffer[c]>depth){
              m_Window->depth_buffer[c] = depth;
              return true;
          }

          return false;
      }
   void ClearColor(INV::Vec4<uint8_t> Color){
   //    printf("%d %d",m_Window->frame_buffer.begin(),m_Window->frame_buffer.end());
   std::fill(
       m_Window->frame_buffer.begin(),
       m_Window->frame_buffer.end(),
       Color
   );
   std::fill(m_Window->depth_buffer.begin(), m_Window->depth_buffer.end(), std::numeric_limits<float>::infinity());
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

   INV::Vec3<float> BaryCentric(INV::Vec2<float>p1,INV::Vec2<float> p2,INV::Vec2<float> p3
       ,INV::Vec2<float> p4){

           INV::Vec2<float> v0=p3-p2;
           INV::Vec2<float> v1=p4-p2;
           INV::Vec2<float> v2=p1-p2;

           float denom=v0.x*v1.y-v0.y*v1.x;
           if (fabs(denom) < 1e-6f)
                   return INV::Vec3<float>(-1, -1, -1);

           float invDenom = 1.0f / denom;

               float w1 = (v2.x * v1.y - v1.x * v2.y) * invDenom;
               float w2 = (v0.x * v2.y - v2.x * v0.y) * invDenom;
               float w0 = 1.0f - w1 - w2;
               return INV::Vec3<float>(w0, w1, w2);


   }
   bool InsideScreenSpace(INV::Vec2<int> Point,INV::Vec2<float> a,INV::Vec2<float> b,INV::Vec2<float> c){

     bool h=(Point.x>=0 && Point.x<m_Window->m_width && Point.y>=0 && Point.y<m_Window->m_height);
     bool j=(a.x>=0 && a.x<m_Window->m_width && a.y>=0 && a.y<m_Window->m_height);
     bool k=(b.x>=0 && b.x<m_Window->m_width && b.y>=0 && b.y<m_Window->m_height);
     bool l=(c.x>=0 && c.x<m_Window->m_width && c.y>=0 && c.y<m_Window->m_height);
     return(h&&j&&k&&l);
   }
};
