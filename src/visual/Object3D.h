#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include <iostream>

using namespace std;

class Object3D
{
    public:
        Object3D()
        {

        }
        virtual ~Object3D(){
        }

        Object3D( boost::shared_ptr<Material> material){
            this->material = material ;
        }

        virtual bool intersect( const Ray& r , Hit& h, float tmin) = 0;

        char* type;
    protected:

        boost::shared_ptr<Material> material;
};

#endif

