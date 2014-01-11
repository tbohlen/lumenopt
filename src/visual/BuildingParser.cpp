#include "BuildingParser.hpp"
#include <math.h>
#include "Group.h"
#include "Material.h"
#include "Object3D.h"
#include "vecmath.h"
#include "Triangle.h"

using namespace std;

BuildingParser::BuildingParser
    (vector<vector<vector<bool> > > plan, float xSize, float ySize, float zSize)
    : plan(plan), xSize(xSize), ySize(ySize), zSize(zSize) {
    // determine the size of the divisions on each axis
    this->xDivs = this->plan.size();
    this->yDivs = (xDivs == 0) ? 0 : this->plan[0].size();
    this->zDivs = (yDivs == 0) ? 0 : this->plan[0][0].size();
    this->xDivSize = this->xSize/this->plan.size();
    this->yDivSize = this->ySize/this->plan[0].size();
    this->zDivSize = this->zSize/this->plan[0][0].size();
    Vector3f color(1., 1., 1.);
    this->material = new Material(color);
}

GroupPtr BuildingParser::getGroup() {
    if (!group) {
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
    float height = y * this->yDivSize;
    float back = z * this->zDivSize;
    float front = (z + 1) * this->zDivSize;

    Vector3f bottomLeft(left, height, front);
    Vector3f topLeft(left, height, back);
    Vector3f bottomRight(right, height, front);
    Vector3f topRight(right, height, back);

    // construct normals
    Vector3f normalsOne[3];
    normalsOne[0] = Vector3f(0, 1, 0);
    normalsOne[1] = Vector3f(0, 1, 0);
    normalsOne[2] = Vector3f(0, 1, 0);

    Vector3f normalsTwo[3];
    normalsTwo[0] = Vector3f(0, 1, 0);
    normalsTwo[1] = Vector3f(0, 1, 0);
    normalsTwo[2] = Vector3f(0, 1, 0);

    // construct the two triangles
    ObjPtr triOne( new Triangle(bottomLeft, bottomRight, topLeft, this->material, normalsOne) );
    ObjPtr triTwo( new Triangle(bottomRight, topRight, topLeft, this->material, normalsTwo) );

    rectangle = make_pair(triOne, triTwo);
    return rectangle;
}

void BuildingParser::buildGroup() {
    int i;
    int j;
    int k;
    // move things into the group from the triangles vector

    // guess a starting size
    this->group = GroupPtr( new Group( ceil( plan.size()/3 ) ) );

    for (i = 0; i < this->xDivs; i++) {
        for (j = 0; j < this->yDivs; j++) {
            for (k = 0; k < this->zDivs; k++) {
                if (plan[i][j][k]) {
                    // if this piece of floor exists, then build it
                    pair<ObjPtr, ObjPtr> rectangle = this->buildRectangle(i, j, k);
                    // temporarily store the triangles in our triangles vector
                    this->group->appendObject(rectangle.first);
                    this->group->appendObject(rectangle.second);
                }
            }
        }
    }
}

BuildingParser::~BuildingParser() {
    delete this->material;
}
