#include "Plane.hpp"
#include <cmath>

Plane::Plane() {

}

Plane::Plane( const Vector3f& normal , float d , Material* m) : Object3D(m) {
    this->normal = normal;
    this->distance = d;
}

Plane::~Plane() {

}

bool Plane::intersect( const Ray& r , Hit& h , float tmin) {
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
