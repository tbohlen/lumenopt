#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <vector>

class Visualizer {
    public:
        Visualizer(std::vector<std::vector<std::vector<bool> > > building, float xSize, float ySize, float zSize);
        void draw();

    private:
        std::vector<std::vector<std::vector<bool> > > building;
        int xDivs;
        int yDivs;
        int zDivs;
        float xSize;
        float ySize;
        float zSize;
        float xDivSize;
        float yDivSize;
        float zDivSize;
};
#endif
