#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.h"
///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary
class Transform: public Object3D
{
    public:
        Transform(){}
        Transform( const Matrix4f& m, ObjPtr obj ):o(obj){
            o = obj;
            transform = m;
        }
        ~Transform(){
        }

        virtual bool intersect( const Ray& r , Hit& h , float tmin) {
            Matrix4f inverse = transform.inverse();
            Vector4f o4 = Vector4f(r.getOrigin(), 1.0);
            Vector4f d4 = Vector4f(r.getDirection(), 0.0);
            Vector3f newOrigin = (inverse * o4).xyz();
            Vector3f newDirection = (inverse * d4).xyz();
            Ray transformedRay(newOrigin, newDirection);
            bool retVal = o->intersect( transformedRay , h , tmin);
            if (retVal) {
                float t = h.getT();
                boost::shared_ptr<Material> mat = h.getMaterial();
                Vector3f normal = h.getNormal();
                Matrix4f normalTransform = inverse.transposed();
                Vector4f normal4 = Vector4f(normal, 0.0);
                Vector3f transformedNormal = (normalTransform * normal4).xyz().normalized();
                // if last intersect was ours, transform the normal
                h.set(t, mat, transformedNormal);
            }
            return retVal;
        }

    protected:
        ObjPtr o; //un-transformed object
        Matrix4f transform;
};

#endif //TRANSFORM_H
