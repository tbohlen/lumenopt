#include "Triangle.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Triangle::Triangle() {

}

Triangle::Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m):Object3D(m) {
    hasTex = false;
    this->a = a;
    this->b = b;
    this->c = c;
}

Triangle::Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m, Vector3f *normals):Object3D(m) {
    hasTex = false;
    this->a = a;
    this->b = b;
    this->c = c;
    this->normals[0] = normals[0];
    this->normals[1] = normals[1];
    this->normals[2] = normals[2];
}

bool Triangle::intersect( const Ray& r,  Hit& h , float tmin) {
    Vector3f dir = r.getDirection();
    Vector3f origin = r.getOrigin();

    Vector3f A1(a[0] - b[0], a[1]- b[1], a[2] - b[2]);
    Vector3f A2(a[0] - c[0], a[1]- c[1], a[2] - c[2]);
    Vector3f A3 = dir;
    Vector3f C(a[0] - origin[0], a[1] - origin[1], a[2] - origin[2]);

    Matrix3f aMatrix(A1, A2, A3);
    float detA = aMatrix.determinant();

    Matrix3f betaA(C, A2, A3);
    float beta = betaA.determinant()/detA;

    Matrix3f gammaA(A1, C, A3);
    float gamma = gammaA.determinant()/detA;

    Matrix3f tA(A1, A2, C);
    float t = tA.determinant()/detA;

    float alpha = 1 - beta - gamma;

    if (alpha < 1 && beta < 1 && gamma < 1 && alpha >= 0 && beta >= 0 && gamma >= 0) {
        // we have a hit!
        if (t < h.getT()) {
            // we are the closest hit
            // calculate normals based on normals at points.
            Vector3f hitNormal = alpha * normals[0] + beta * normals[1] + gamma *normals[2];
            hitNormal.normalize();
            if (hasTex) {
                Vector2f texCoord = (alpha * texCoords[0]) + (beta * texCoords[1]) + (gamma * texCoords[2]);
                h.setTexCoord(texCoord);
            }
            h.set(t, material, hitNormal);
            return true;
        }
    }
    return false;
}
