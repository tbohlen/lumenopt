#include "Camera.hpp"
#include "Ray.hpp"
#include <cmath>
#include <iostream>

PerspectiveCamera::PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle) {

    this->center = center;
    this->direction = direction.normalized();
    this->up = up.normalized();
    this->angle = angle;

    // to avoid calculating the actual u,v,w vectors, size, and bottom-left corner coordinates each time we ray trace, we do it here
    this->u = Vector3f::cross(this->direction, this->up);
    this->v = Vector3f::cross(u, this->direction);
    this->u.normalize();
    this->v.normalize();
    this->screenSize = 2.0 * tan(angle/2.0);
    this->bottomLeft = this->center + this->direction - (this->screenSize * 0.5 * (this->u + this->v));
}

Ray PerspectiveCamera::generateRay( const Vector2f& point) {
    // calculate the location in space of this screen point
    Vector3f pointLoc = bottomLeft + u*screenSize*point[0] + v*screenSize*point[1];

    // normalized the direction from the camera center to this point
    Vector3f normalizedDir = (pointLoc - center).normalized();

    // return the ray that this describes
    return Ray(center, normalizedDir);
}

float PerspectiveCamera::getTMin() const {
    return 0.0f;
}

Camera* PerspectiveCamera::clone() const {
    return new PerspectiveCamera(*this);
}
