#include "Group.hpp"
#include "Object3D.hpp"
#include "Ray.hpp"
#include "Hit.hpp"

using  namespace std;

Group::Group(){

}

Group::Group( int num_objects ){
    objects.resize(num_objects);
}

Group::~Group(){

}

bool Group::intersect( const Ray& r , Hit& h , float tmin ) {
    int i;
    bool intersected = false;
    for (i = 0; i < objects.size(); i++) {
        ObjPtr obj = objects[i];
        if (obj) {
            bool retVal = obj->intersect(r, h, tmin);
            if (retVal) {
                intersected = true;
            }
        }
    }

    return intersected;
}

void Group::addObject( int index , const ObjPtr obj ){
    objects[index] = obj;
}

void Group::appendObject( const ObjPtr obj ){
    objects.push_back(obj);
}

int Group::getGroupSize() const {
    return objects.size();
}
