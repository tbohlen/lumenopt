#ifndef TYPES_H
#define TYPES_H

class Object3D;
class Group;
class Light;

#include "boost/shared_ptr.hpp"
#include <vector>

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
typedef boost::shared_ptr<Group> GroupPtr;
typedef boost::shared_ptr<Light> LightPtr;

typedef std::vector<std::vector<std::vector<bool> > > boolMatrix;

typedef std::vector<std::vector<std::vector<coord> > > coordMatrix;


#endif
