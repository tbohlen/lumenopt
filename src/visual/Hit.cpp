#include "Hit.hpp"

#include "Ray.hpp"
#include <float.h>

// constructors
Hit::Hit() {
    t = FLT_MAX;
    hasTex=false;
}

Hit::Hit( float _t, Material* m, const Vector3f& n ) {
    t = _t;
    material = m;
    normal = n;
    hasTex=false;
}

Hit::Hit( const Hit& h ) {
    t = h.t;
    material = h.material;
    normal = h.normal;
    hasTex=h.hasTex;
}

// destructor
Hit::~Hit() {

}

float Hit::getT() const {
    return t;
}

Material* Hit::getMaterial() const {
    return material;
}

const Vector3f& Hit::getNormal() const {
    return normal;
}

void Hit::set( float _t, Material* m, const Vector3f& n ) {
    t = _t;
    material = m;
    normal = n;
}
void Hit::setTexCoord(const Vector2f &coord) {
    texCoord = coord;
    hasTex = true;
}
