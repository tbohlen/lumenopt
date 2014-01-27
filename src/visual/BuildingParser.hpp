#ifndef MESH_H
#define MESH_H
#include <vector>
#include "types.h"

class Material;

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
         * The building parser object interprets the 3-dimensional building
         * vector to allow for visualizing the building. the x y and z sizes are
         * the sizes of the individual divisions in the x, y, and z directions
         * respectively.
         *
         * Arguments:
         * plan - a vector containing true and false vlues indicating where a
         * floor exists
         * xSize - the number of divisions along the x axis
         * ySize - the number of divisions along the y axis
         * zSize - the number of divisions along the z axis
         */
        BuildingParser(std::vector<std::vector<std::vector<bool> > > plan, float xSize, float ySize, float zSize);

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
        GroupPtr getGroup();

    private:
        std::vector<std::vector<std::vector<bool> > > plan;
        float xSize;
        float ySize;
        float zSize;
        Material* material;
        GroupPtr group;

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
         * Method: buildGroup
         *
         * Builds the group of triangles that represents the building. The group
         * is stored in this->group but not returned.
         */
        void buildGroup();
};

#endif
