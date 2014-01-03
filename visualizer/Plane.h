#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
using namespace std;
///TODO: Implement Plane representing an infinite plane
///choose your representation , add more fields and fill in the functions
class Plane: public Object3D
{
public:
	Plane(){}
	Plane( const Vector3f& normal , float d , Material* m):Object3D(m){
        this->normal = normal;
        this->distance = d;
	}
	~Plane(){}
	virtual bool intersect( const Ray& r , Hit& h , float tmin){
        Vector3f dir = r.getDirection();
        Vector3f origin = r.getOrigin();
        float dn = Vector3f::dot(dir, normal);
        float on = Vector3f::dot(origin, normal);
        float t = (distance-on)/dn;
        if (t < h.getT() && t > tmin) {
            Vector3f hitNormal;
            if (dn > 0) {
                hitNormal = -1 * normal;
            }
            else {
                hitNormal = normal;
            }

            h.set(t, material, hitNormal);

            return true;
        }
        return false;
	}

protected:
    Vector3f normal;
    float distance;
};
#endif //PLANE_H
