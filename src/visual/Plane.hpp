#ifndef PLANE_H
#define PLANE_H

#include "Object3D.hpp"
#include <vecmath.h>

class Plane: public Object3D
{
public:
    Plane();
    Plane( const Vector3f& normal , float d , Material* m);
    ~Plane();
    bool intersect( const Ray& r , Hit& h , float tmin);

protected:
    Vector3f normal;
    float distance;
};

#endif //PLANE_H
