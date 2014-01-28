#ifndef MATERIAL_H
#define MATERIAL_H

#include "vecmath/vecmath.h"
#include "Texture.hpp"

class Hit;
class Ray;

class Material
{
    public:

        Material();

        Material( const Vector3f& d_color, const Vector3f& s_color=Vector3f::ZERO, float s=0);

        virtual ~Material();

        virtual Vector3f getDiffuseColor(const Hit *hit);

        Vector3f getSpecularColor();

        float getShininess();

        Texture getTexture();

        Vector3f Shade( const Ray& ray, const Hit& hit,
                const Vector3f& dirToLight, const Vector3f& lightColor );

        void loadTexture(const char * filename);
    protected:
        Vector3f diffuseColor;
        Vector3f specularColor;
        float shininess;
        Texture t;
};

#endif // MATERIAL_H
