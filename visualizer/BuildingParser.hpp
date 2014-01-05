#ifndef MESH_H
#define MESH_H
#include <vector>
#include "Triangle.h"
#include "Object3D.h"
#include "Vector4f.h"
#include "Group.h"
#include "types.h"
#include "Material.h"
#include "boost/shared_ptr.hpp"

/*
 * Class: BuildingParser
 *
 * Takes in a representation for a building and constructs group that can be
 * used to display an image of the building.
 *
 * Generally, one is going to construct a building parser with the building plan
 * to be parsed, then call getGroup when the group is needed. The first call to
 * getGroup will construct the group.
 */
class BuildingParser {
    public:
        /*
         * Constructor: BuildingParser
         *
         * The plan should be a flattened matrix in the following order:
         * (0, 0, 0), (1, 0, 0), (0, 1, 0), (1, 1, 0), (0, 0, 1), (1, 0, 1), ...
         *
         * Arguments:
         * plan - a vector containing true and false vlues indicating where a
         * floor exists
         * xDivs - the number of divisions along the x axis
         * yDivs - the number of divisions along the y axis
         * zDivs - the number of divisions along the z axis
         */
        BuildingParser(std::vector<int> plan, int xDivs, int yDivs, int zDivs, float xSize, float ySize, float zSize);

        /*
         * Deconstructor
         */
        ~BuildingParser();

        /*
         * Method: getGroup
         *
         * If the group as already been created, returns it. Otherwise, it
         * builds the group by constructing a series of triangles that define
         * the building's floors.
         */
        Group* getGroup();

    private:
        std::vector<int> plan;
        int xDivs;
        int yDivs;
        int zDivs;
        float xSize;
        float ySize;
        float zSize;
        float xDivSize;
        float yDivSize;
        float zDivSize;
        Material* material;
        Group* group;
        std::vector<ObjPtr> triangles;

        /*
         * Method: buildRectangle
         *
         * Builds two triangles that together form a rectangle of floor area
         * with indices x, y, z.
         *
         * Arguments:
         * x - x index of floor
         * y - y index of floor
         * z - z index of floor
         *
         * Returns a pair containing pointers to two triangles that together
         * make the rectangle.
         */
        std::pair<ObjPtr, ObjPtr> buildRectangle(int x, int y, int z);

        /*
         * Method: getIndices
         *
         * Finds the x, y, and z indices of the floor square at index in the
         * building plan.
         *
         * Arguments:
         * index - the index in the building plan vector for which we would like
         * the indices
         *
         * Returns a indices object containing the x, y, and z indices
         * caluclated.
         */
        indices getIndices(int index);

        /*
         * Method: buildGroup
         *
         * Builds the group of triangles that represents the building. The group
         * is stored in this->group but not returned.
         */
        void buildGroup();


};

#endif
