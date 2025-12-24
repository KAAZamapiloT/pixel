#include"Renderer.h"

namespace renderer
{


    void Create_PPM_File(std::string filename){

        std::ofstream outFile(filename);
        if(!outFile){
          std::cerr<<"Failed In Creating a File"<<std::endl;
          return;
        }

        outFile<<"P3\n";
        outFile<<m_Window->GetWidth()<<" "<<m_Window->GetHeight<<"\n";
        outFile<<"255\n";

        // here is writing pizel data
        //

        for(int i=0;i<m_Window->GetHeight();++i){
          for(int j=0;j<m_Window->GetWidth();++i){

           // INV::Vec3<uint8_t> Col={i,j,128};

            uint32_t Col=j+i*m_Window->GetWidth();
            outFile<<frame_buffer[Col].x<<" "<<frame_buffer[Col].y<<" "<<frame_buffer[Col].z;
          }
          outFile<<"\n";
        }
        outFile.close();
        std::cout<<"PPM File Created"<<std::endl;

    }
}
