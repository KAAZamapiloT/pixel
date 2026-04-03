#include "Renderer.h"
class TEST {
public:
    std::vector<Entity> entities;

const int SIZE = 3;
const float spacing = 2.0f;
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

            e.transform.scale = Vec3f(1.0f, 1.0f, 1.0f);

            entities.push_back(e);
        }
    }
}

}
};
