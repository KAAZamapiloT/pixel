
#include"storage.h"
#include<string>
#include<fstream>
class renderer{

  public:

    renderer(uint8_t id,std::unique_ptr<INV::Window> wind)
    {

      m_id=id;
   m_Window=wind.move();

    }

    void SetPixelColor(INV::Vec2 cord,INV::Vec3 Color);
    INV::Vec3 GetColor(INV::Vec2 cord);

    // virtual void DrawLine()=0;
     //virtual void DrawPlane()=0;
     //virtual void DrawTriangle()=0;

     void Create_PPM_File(std::string Filename);
  private:
uint8_t m_id;
    std::unique_ptr<INV::Window> m_Window;
};
