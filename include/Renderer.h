
#include"storage.h"
#include <cstdint>
#include <iostream>
#include<string>
#include<fstream>
#include"Camera.h"
class renderer{

  public:

    renderer(uint8_t id,std::unique_ptr<INV::Window> wind)
    {
    m_id=id;
    m_Window=std::move(wind);
    }

   //---------------------Mods-----------------------------//
     void DrawLine(INV::Vec2<uint16_t> start,INV::Vec2<uint16_t> end,INV::Vec3<uint8_t> Color){
     INV::Vec2<uint16_t> dim=GetDimensions();
     if(start.x>end.x){
         std::cerr<<"invalid arguments"<<std::endl;
         return;
     }

}
void DrawLine(INV::Vec2<uint16_t> start,INV::Vec2<uint16_t> end,INV::Vec3<uint8_t> Color,
    INV::Vec3<uint8_t>(*F)(INV::Vec2<uint16_t>,float) )
{
 float p=256.0/static_cast<float>(end.x-start.x);
 float slope=(float)(end.y-start.y)/(end.x-start.x);

 float constant=start.y-slope*start.x;
       for(uint16_t i=start.x;i<=end.x;++i){
           uint16_t y=round(slope*i+constant);
           SetPixelColor(INV::Vec2<uint16_t>(i,y),F(INV::Vec2<uint16_t>(i,y),1));
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
             for(uint16_t i=miy;i<may;++i){
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

//-----------------------------------
     void Draw_Cube(INV::Vec3<uint16_t> p1,INV::Vec3<uint16_t>p2,INV::Vec3<uint16_t>p3,INV::Vec2<uint16_t>p4
         ,INV::Vec3<uint16_t> p5,INV::Vec3<uint16_t>p6,INV::Vec3<uint16_t> p7,INV::Vec3<uint16_t> p8,INV::Vec3<uint16_t> Color){



     }

     // Drawing a triangle in 3d space but then it can also accept a function pointer(can be passes as null)
    // but here main thing is to set color val
  // assuming world space cordinates-> otherwise local->world transformation
  void Draw_Tiangle_3d(Camera*camera,INV::Vec3<double> p1,INV::Vec3<double> p2,INV::Vec3<double> p3,
      INV::Vec3<uint8_t> color,INV::Vec3<uint8_t> (*f)(INV::Vec3<double>)
  ){
       INV::Vec3<double> maxvals;
      INV::Vec3<double> minvals;
      minvals.x=std::min({p1.x,p2.x,p3.x});
      minvals.y=std::min({p1.y,p2.y,p3.y});
      minvals.z=std::min({p1.z,p2.z,p3.z});
      maxvals.x=std::max({p1.x,p2.x,p3.x});
      maxvals.y=std::max({p1.y,p2.y,p3.y});
      maxvals.z=std::max({p1.z,p2.z,p3.z});
    Matrix4<double> ProjectionView=camera->GetProjectionView();

      if(f==nullptr){
          for(int i=minvals.z;i<=maxvals.z;++i){
              for(int j=minvals.y;j<=maxvals.y;++j){
                  for(int k=minvals.x;k<=maxvals.x;++k){
                    INV::Vec4<double>p=INV::Vec4<double>(k,j,i,1);
                    INV::Vec4<double>clip=ProjectionView*p;
                    INV::Vec3<double> ndc=INV::Vec3<double>(clip.x/clip.w,clip.y/clip.w,clip.z/clip.w);
                    INV::Vec2<double> screen=INV::Vec2<double>((ndc.x+1)*0.5*m_Window->m_width,(1-ndc.y)*0.5*m_Window->m_height);
                    if(screen.x>=0 && screen.x<m_Window->m_width && screen.y>=0 && screen.y<m_Window->m_height){
                      m_Window->framebuffer[screen.y*m_Window->m_width+screen.x]=INV::Vec3<uint8_t>(color.x,color.y,color.z);
                    }
                  }
              }
          }
      }else{
          for(int i=minvals.z;i<=maxvals.z;++i){
              for(int j=minvals.y;j<=maxvals.y;++j){
                  for(int k=minvals.x;k<=maxvals.x;++k){
                    INV::Vec4<double>p=INV::Vec4<double>(k,j,i,1);
                    INV::Vec4<double>clip=ProjectionView*p;
                    INV::Vec3<double> ndc=INV::Vec3<double>(clip.x/clip.w,clip.y/clip.w,clip.z/clip.w);
                    INV::Vec2<double> screen=INV::Vec2<double>((ndc.x+1)*0.5*m_Window->m_width,(1-ndc.y)*0.5*m_Window->m_height);
                    if(screen.x>=0 && screen.x<m_Window->m_width && screen.y>=0 && screen.y<m_Window->m_height){
                      m_Window->SetPixelColor(screen.x,screen.y,INV::Vec3<uint8_t>(color.x,color.y,color.z),f(j,i,k));
                    }
                  }
              }
          }
      }

      }

   void ClearColor(INV::Vec4<uint8_t> Color){
       std::fill(m_Window->framebuffer.begin()
           ,m_Window->framebuffer.end(),
           INV::Vec3<uint8_t>(Color.x,Color.y,Color.z));
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
