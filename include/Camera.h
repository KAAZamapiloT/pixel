#include"storage.h"


/* A SIMPLE IMPLEMETAION OF CAMERA WHAT IT IS AND WHAT IT CAN DO
 *
 */

 enum class Type{
     Perspective,
     Orthographic
 };


template<typename T>
class camera{

    camera(Type p,INV::Vec3<T> location_3d){
        camera_type=p;
        Location_3d=location_3d;
        Location_2d=INV::Vec2<T>(location_3d.x,location_3d.y);
    }

    private:
    Type camera_type=Type::Orthographic;

    INV::Vec3<T> Location_3d;
    INV::Vec2<T> Location_2d; // I dont know if i will use it
    // struct orthographics/presective values
    // matrices projection vs prespective

};
