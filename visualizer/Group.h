#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using  namespace std;

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
class Group:public Object3D
{
    public:

        Group(){

        }

        Group( int num_objects ){
            objects.resize(num_objects);
        }

        ~Group(){

        }

        virtual bool intersect( const Ray& r , Hit& h , float tmin ) {
            int i;
            bool intersected = false;
            for (i = 0; i < objects.size(); i++) {
                bool retVal = objects[i]->intersect(r, h, tmin);
                if (retVal) {
                    intersected = true;
                }
            }

            return intersected;
        }

        void addObject( int index , Object3D* obj ){
            objects[index] = obj;
        }

        int getGroupSize(){
            return objects.size();
        }

    private:
        vector<Object3D*> objects;
};

#endif
