#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.hpp"
#include <vecmath.h>

class Triangle: public Object3D {
    public:
        Triangle();
        ///@param a b c are three vertex positions of the triangle
        Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m);

        Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m, Vector3f *normals);

        virtual bool intersect( const Ray& r,  Hit& h , float tmin);

        bool hasTex;
        Vector3f normals[3];
        Vector2f texCoords[3];

    protected:
        Vector3f a;
        Vector3f b;
        Vector3f c;
        Vector3f normal;
};

#endif //TRIANGLE_H
