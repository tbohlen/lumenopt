#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>
#include <iostream>

using namespace std;

class Camera
{
    public:
        //generate rays for each screen-space coordinate
        virtual Ray generateRay( const Vector2f& point ) = 0 ;
        virtual float getTMin() const = 0 ;
        virtual ~Camera(){}
    protected:
        Vector3f center;
        Vector3f direction;
        Vector3f up;
        Vector3f horizontal;

};

///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera: public Camera
{
    public:
        PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle){

            this->center = center;
            this->direction = direction.normalized();
            this->up = up.normalized();
            this->angle = angle;

            // to avoid calculating the actual u,v,w vectors, size, and bottom-left corner coordinates each time we ray trace, we do it here
            u = Vector3f::cross(this->direction, this->up);
            v = Vector3f::cross(u, this->direction);
            u.normalize();
            v.normalize();
            screenSize = 2.0 * tan(angle/2.0);
            bottomLeft = center + this->direction - (screenSize * 0.5 * (u + v));
        }

        virtual Ray generateRay( const Vector2f& point){
            // calculate the location in space of this screen point
            Vector3f pointLoc = bottomLeft + u*screenSize*point[0] + v*screenSize*point[1];

            // normalized the direction from the camera center to this point
            Vector3f normalizedDir = (pointLoc - center).normalized();

            // return the ray that this describes
            return Ray(center, normalizedDir);
        }

        virtual float getTMin() const {
            return 0.0f;
        }

    private:
        float angle;
        // u is the vector perpendicular to both up and direction
        Vector3f u;
        // v is the accurate up vector, perpendicular to u and direction
        Vector3f v;
        float screenSize;
        Vector3f bottomLeft;
};

#endif //CAMERA_H
