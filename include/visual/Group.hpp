#ifndef GROUP_H
#define GROUP_H

#include "Object3D.hpp"
#include <vector>
#include "types.hpp"

class Ray;
class Hit;

class Group : public Object3D
{
    public:

        Group();

        Group( int num_objects );

        ~Group();

        virtual bool intersect( const Ray& r , Hit& h , float tmin );

        void addObject( int index , const ObjPtr obj );

        void appendObject( const ObjPtr obj );

        int getGroupSize() const;

    private:
        std::vector<ObjPtr> objects;
};

#endif
