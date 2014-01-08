#ifndef TYPES_H
#define TYPES_H

#include "boost/shared_ptr.hpp"

typedef struct {
    int x;
    int y;
    int z;
} indices;

typedef struct {
    float x;
    float y;
    float z;
} coord;

typedef boost::shared_ptr<Object3D> ObjPtr;

typedef std::vector<std::vector<std::vector<bool>>> boolMatrix;

typedef std::vector<std::vector<std::vector<coord>>> coordMatrix;

#endif
