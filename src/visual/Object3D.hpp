#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Ray.hpp"
#include "Hit.hpp"
#include "Material.hpp"

class Object3D
{
    public:
        Object3D()
        {

        }
        virtual ~Object3D(){
        }

        Object3D( Material* material){
            this->material = material ;
        }

        virtual bool intersect( const Ray& r , Hit& h, float tmin) = 0;

        char* type;
    protected:

        Material* material;
};

#endif

