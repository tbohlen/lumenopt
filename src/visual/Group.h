#ifndef GROUP_H
#define GROUP_H

#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include "types.h"

using  namespace std;

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
class Group : public Object3D
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

        void addObject( int index , const ObjPtr obj ){
            objects[index] = obj;
        }

        void appendObject( const ObjPtr obj ){
            objects.push_back(obj);
        }

        int getGroupSize() const {
            return objects.size();
        }

    private:
        vector<ObjPtr> objects;
};

#endif
