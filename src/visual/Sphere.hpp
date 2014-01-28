#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.hpp"
#include "vecmath/vecmath.h"

class Sphere: public Object3D
{
public:
	Sphere();

	Sphere( Vector3f center , float radius , Material* material );

	~Sphere();

    Vector3f getNormal(Vector3f point);

	virtual bool intersect( const Ray& r , Hit& h , float tmin);

protected:
    Vector3f center;
    float radius;
};


#endif
