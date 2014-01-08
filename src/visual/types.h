#ifndef TYPES_H
#define TYPES_H

#include "boost/shared_ptr.hpp"

typedef struct {
    int x;
    int y;
    int z;
} indices;

typedef boost::shared_ptr<Object3D> ObjPtr;

#endif
