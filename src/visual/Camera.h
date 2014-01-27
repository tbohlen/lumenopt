#ifndef CAMERA_H
#define CAMERA_H

#include <vecmath.h>

class Ray;

class Camera
{
    public:
        //generate rays for each screen-space coordinate
        virtual Ray generateRay( const Vector2f& point ) = 0 ;
        virtual float getTMin() const = 0 ;
        virtual ~Camera() { }
        virtual Camera* clone() const = 0;
    protected:
        Vector3f center;
        Vector3f direction;
        Vector3f up;
        Vector3f horizontal;

};

class PerspectiveCamera: public Camera
{
    public:
        PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle);

        virtual Ray generateRay( const Vector2f& point);

        virtual float getTMin() const;

        virtual Camera* clone() const;

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
