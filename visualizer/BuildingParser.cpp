#include "BuildingParser.hpp"
#include <math.h>
#include "Vector3f.h"

using namespace std;

BuildingParser::BuildingParser
    (vector<int> plan, int xDivs, int yDivs, int zDivs, float xSize, float ySize, float zSize)
    : plan(plan), xDivs(xDivs), yDivs(yDivs), zDivs(zDivs), xSize(xSize), ySize(ySize), zSize(zSize), group(NULL) {
    // determine the size of the divisions on each axis
    this->xDivSize = this->xSize/this->xDivs;
    this->yDivSize = this->ySize/this->yDivs;
    this->zDivSize = this->zSize/this->zDivs;
    Vector3f color(1, 1, 1);
    this->material = new Material(color);
}

Group* BuildingParser::getGroup() {
    if (group == NULL) {
        // create the group
        this->buildGroup();
    }

    // return the group
    return this->group;
}

pair<ObjPtr, ObjPtr> BuildingParser::buildRectangle(int x, int y, int z) {
    pair<ObjPtr, ObjPtr> rectangle;

    // find the four corners
    float left = x * this->xDivSize;
    float right = (x + 1) * this->xDivSize;
    float bottom = y * this->xDivSize;
    float top = (y + 1) * this->xDivSize;
    float height = z * this->zDivSize;

    Vector3f bottomLeft(left, bottom, height);
    Vector3f topLeft(left, top, height);
    Vector3f bottomRight(right, bottom, height);
    Vector3f topRight(right, top, height);

    // construct the two triangles
    ObjPtr triOne( new Triangle(bottomLeft, bottomRight, topLeft, this->material) );
    ObjPtr triTwo( new Triangle(bottomRight, topRight, topLeft, this->material) );

    rectangle = make_pair(triOne, triTwo);
    return rectangle;
}

indices BuildingParser::getIndices(int index) {
    int x = index % this->xDivs;
    int y = int( floor( index/this->xDivs ) ) % this->yDivs;
    int z = int( floor( index/(this->xDivs) * this->yDivs ) );
    indices result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

void BuildingParser::buildGroup() {
    int i;
    for (i = 0; i < plan.size(); i++) {
        if (plan[i]) {
            // if this piece of floor exists, then build it
            indices inds = getIndices(i);
            pair<ObjPtr, ObjPtr> rectangle = this->buildRectangle(inds.x, inds.y, inds.z);
            // temporarily store the triangles in our triangles vector
            this->triangles.push_back(rectangle.first);
            this->triangles.push_back(rectangle.second);
        }
    }

    // move things into the group from the triangles vector
    this->group = new Group(this->triangles.size());
    for (i = 0; i < this->triangles.size(); i++) {
        this->group->addObject(i, this->triangles[i]);
    }
}

BuildingParser::~BuildingParser() {
    delete this->material;
    delete this->group;
}
