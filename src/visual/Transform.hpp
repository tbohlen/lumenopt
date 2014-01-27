#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.hpp"
#include "types.hpp"

class Transform: public Object3D
{
    public:
        Transform();
        Transform( const Matrix4f& m, ObjPtr obj );
        ~Transform();

        virtual bool intersect( const Ray& r , Hit& h , float tmin);

    protected:
        ObjPtr o; //un-transformed object
        Matrix4f transform;
};

#endif //TRANSFORM_H
