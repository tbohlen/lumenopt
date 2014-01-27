#include "Sphere.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Sphere::Sphere() {
    //unit ball at the center
    radius = 1.0;
    center = Vector3f(0.0, 0.0, 0.0);
}

Sphere::Sphere( Vector3f center , float radius , Material* material ) : Object3D(material) {
    this->radius = radius;
    this->center = center;
}

Sphere::~Sphere(){
    // do nothing. This will call the parent's destrutor
}

Vector3f Sphere::getNormal(Vector3f point) {
    Vector3f centerVector = point - center;
    return centerVector.normalized();
}

bool Sphere::intersect( const Ray& r , Hit& h , float tmin){
    // calculate the intersections
    Vector3f dir = r.getDirection();
    Vector3f origin = r.getOrigin();
    float a = dir.absSquared();
    float b = (2 * Vector3f::dot(dir, origin)) - (2 * Vector3f::dot(dir, center));
    float c = origin.absSquared() - (2 * Vector3f::dot(origin, center)) + center.absSquared() - radius * radius;

    float d = sqrt(b*b - 4*a*c);
    float ans1 = (-b + d)/(2 * a);
    float ans2 = (-b - d)/(2 * a);
    float hit = +INFINITY;

    // our intersection is the closest intersect that is in front of the camera
    if (ans1 >= tmin) {
        /* code */
        hit = ans1;
    }
    if (ans2 >= tmin && ans2 <= ans1) {
        hit = ans2;
    }

    // at this point we have the hit 
    if (hit <= h.getT()) {
        // this means that we need to calculate the normal at this point
        Vector3f normal = getNormal(r.pointAtParameter(hit));
        h.set(hit, material, normal);
        return true;
    }
    return false;
}
