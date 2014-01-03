#ifndef MESH_H
#define MESH_H
#include <vector>
#include "Triangle.h"
#include "Vector4f.h"
#include "Group.h"

class BuildingParser {
    public:
        BuildingParser(std::vector<float> plan, float width, float length, float height);
        Group* getGroup();

    private:
        std::vector<Triangle>
        float width;
        float length;
        float height;
        Triangle* buildTriangle(int x, int y, int z);

}
