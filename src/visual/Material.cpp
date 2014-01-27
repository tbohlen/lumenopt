#include "Material.hpp"

#include <cassert>
#include "Ray.hpp"
#include "Hit.hpp"

Material::Material() : diffuseColor(0), specularColor(0), shininess(0) {

}

Material::Material( const Vector3f& d_color, const Vector3f& s_color, float s):
    diffuseColor( d_color),specularColor(s_color), shininess(s) {

}

Material::~Material() {

}

Vector3f Material::getDiffuseColor(const Hit *hit) {
    if (hit->hasTex && t.valid()) {
        Vector2f texCoord = hit->texCoord;
        return t(texCoord[0], texCoord[1]);
    }
    else {
        return diffuseColor;
    }
}

Vector3f Material::getSpecularColor() {
    return this->specularColor;
}

float Material::getShininess() {
    return this->shininess;
}

Texture Material::getTexture() {
    return t;
}

Vector3f Material::Shade( const Ray& ray, const Hit& hit,
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

void Material::loadTexture(const char * filename){
    t.load(filename);
}
