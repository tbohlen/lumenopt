#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>
#include <stdio.h>

#include "Ray.h"
#include "Hit.h"
#include "texture.hpp"
///TODO:
///Implement Shade function that uses ambient, diffuse, specular and texture
class Material
{
    public:

        Material( const Vector3f& d_color ,const Vector3f& s_color=Vector3f::ZERO, float s=0):
            diffuseColor( d_color),specularColor(s_color), shininess(s) {

        }

        virtual ~Material()
        {

        }

        virtual Vector3f getDiffuseColor(const Hit *hit) {
            if (hit->hasTex && t.valid()) {
                Vector2f texCoord = hit->texCoord;
                return t(texCoord[0], texCoord[1]);
            }
            else {
                return diffuseColor;
            }
        }

        Vector3f Shade( const Ray& ray, const Hit& hit,
                const Vector3f& dirToLight, const Vector3f& lightColor ) {

            Vector3f normal = hit.getNormal();
            Vector3f dir = ray.getDirection();
            Vector3f diffuseColor = getDiffuseColor(&hit);
            float d = Vector3f::dot(dirToLight, normal);
            if (d < 0) {
                d = 0;
            }

            // specular phong
            float len = Vector3f::dot(-1 * ray.getDirection(), normal);
            Vector3f reflection = dir + (len * 2 * normal);
            float reflectionValue = Vector3f::dot(dirToLight, reflection);
            if (reflectionValue < 0) {
                reflectionValue = 0;
            }
            float c = pow(reflectionValue, shininess);
            return d*lightColor*diffuseColor + c*lightColor*specularColor;

        }

        void loadTexture(const char * filename){
            t.load(filename);
        }
    protected:
        Vector3f diffuseColor;
        Vector3f specularColor;
        float shininess;
        Texture t;
};

#endif // MATERIAL_H
