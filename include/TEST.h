#include "Renderer.h"


class Exampler{
public:
Exampler(){
    p1 = Vec3f(-0.5f, -0.5f, -0.5f);
    p2 = Vec3f( 0.5f, -0.5f, -0.5f);
    p3 = Vec3f( 0.5f,  0.5f, -0.5f);
    p4 = Vec3f(-0.5f,  0.5f, -0.5f);

    p5 = Vec3f(-0.5f, -0.5f,  0.5f);
    p6 = Vec3f( 0.5f, -0.5f,  0.5f);
    p7 = Vec3f( 0.5f,  0.5f,  0.5f);
    p8 = Vec3f(-0.5f,  0.5f,  0.5f);
}
    void Draw(){
    // r-> submit Data()
    // r->Draw Data()
    }

    void DepthTest1(std::unique_ptr<class renderer>&r,class camera& cam) {

        // FAR triangle (should be hidden)
        r->DrawTriangle3D(cam,
            Vec3f(-0.5f, -0.5f, 3.0f),
            Vec3f(0.5f, -0.5f, 3.0f),
            Vec3f(0.0f,  0.5f, 3.0f),
            INV::Vec3<uint8_t>(255, 0, 0), nullptr
        );

        // NEAR triangle (should always be visible)
        r->DrawTriangle3D(cam,
            Vec3f(-0.5f, -0.5f, 1.0f),
            Vec3f(0.5f, -0.5f, 1.0f),
            Vec3f(0.0f,  0.5f, 1.0f),
            INV::Vec3<uint8_t>(0, 255, 0), nullptr
        );
    }
    void DepthTest2(std::unique_ptr<class renderer>&r, class camera& cam) {

        // Triangle A (slanted)
        r->DrawTriangle3D(cam,
            Vec3f(-0.8f, -0.5f, 1.0f),
            Vec3f(0.8f, -0.5f, 2.0f),
            Vec3f(0.0f,  0.8f, 1.5f),
            INV::Vec3<uint8_t>(255, 0, 0), nullptr
        );

        // Triangle B crossing it
        r->DrawTriangle3D(cam,
            Vec3f(-0.8f,  0.5f, 2.0f),
            Vec3f( 0.8f,  0.5f, 1.0f),
            Vec3f( 0.0f, -0.8f, 1.5f),
            INV::Vec3<uint8_t>(0, 255, 0), nullptr
        );
    }
    TriangleArray CreateTestTriangle() {
        TriangleArray obj;

        Triangle t;
        t.vertices = {
            Vec3f(-0.5f, -0.5f, 2.0f),
                Vec3f( 0.5f, -0.5f, 2.0f),
                Vec3f( 0.0f,  0.5f, 2.0f)
        };

        obj.triangles.push_back(t);
        obj.colors.push_back({255, 0, 0}); // red

        Transform tr;
        tr.position = {0,0,0};
        tr.scale    = {1,1,1};
        tr.rotation = quat(0,0,0,1);

        obj.Transforms.push_back(tr);

        return obj;
    }
void CubeTest(std::unique_ptr<class renderer>&r, class camera& cam,INV::Vec3<uint8_t>col){
    r->Draw_Cube(cam, p1, p2, p3, p4, p5, p6, p7, p8,col);
}

void Rotate_Cube(float angle,Vec3f axis){
Mat3f rotation = Math::Rotation3D(angle,axis);
   p1 = rotation * p1;
   p2 = rotation * p2;
   p3 = rotation * p3;
   p4 = rotation * p4;
   p5 = rotation * p5;
   p6 = rotation * p6;
   p7 = rotation * p7;
   p8 = rotation * p8;
}
void Rotate_Cube(std::vector<Vec3f>& cube,float angle,Vec3f axis){
Mat3f rotation = Math::Rotation3D(angle,axis);
   cube[0] = rotation * cube[0];
   cube[1] = rotation * cube[1];
   cube[2] = rotation * cube[2];
   cube[3] = rotation * cube[3];
   cube[4] = rotation * cube[4];
   cube[5] = rotation * cube[5];
   cube[6] = rotation * cube[6];
   cube[7] = rotation * cube[7];
}
void CubeDepthTest(std::unique_ptr<class renderer>&r, class camera& cam,INV::Vec3<uint8_t>col,
    std::vector<Vec3f>& cube1,std::vector<Vec3f>& cube2){
   r->Draw_Cube(cam,cube1[0],cube1[1],cube1[2],cube1[3],cube1[4],cube1[5],cube1[6],cube1[7],col);
   r->Draw_Cube(cam,cube2[0],cube2[1],cube2[2],cube2[3],cube2[4],cube2[5],cube2[6],cube2[7],col);

}


  private:

std::vector<TriangleArray> Tarray;
Vec3f p1,p2,p3,p4,p5,p6,p7,p8; //cube points

};

class TEST {
public:
    std::vector<Entity> entities;

const int SIZE = 6;
const float spacing = 2.1f;
void S(){
    Mesh SphereMesh = MeshFactory::CreateSphere(2.f,30,30);
for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
        for (int z = 0; z < SIZE; z++) {

            Entity e(SphereMesh);
            e.transform.position = Vec3f(
                (x - SIZE/2) * spacing,
                (y - SIZE/2) * spacing,
                (z - SIZE/2) * spacing
            );
            e.transform.scale = Vec3f(0.6f, 0.6f, 0.6f);

            entities.push_back(e);
        }
    }
}
}
void P(){
    Mesh cubeMesh = MeshFactory::CreateCube(1.0f);
for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
        for (int z = 0; z < SIZE; z++) {

            Entity e(cubeMesh);

            e.transform.position = Vec3f(
                (x - SIZE/2) * spacing,
                (y - SIZE/2) * spacing,
                (z - SIZE/2) * spacing
            );

            e.transform.scale = Vec3f(0.5f, 0.5f, 0.5f);

            entities.push_back(e);
        }
    }
}

}
};
