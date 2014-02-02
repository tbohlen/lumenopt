#ifndef VISUALIZER_H
#define VISUALIZER_H

class Building;
class Sun;

class Visualizer {
    public:
        Visualizer(Building *building, Sun *sun);
        void draw();
        void nextSunPosition();

    private:
        Building *building;
        Sun *sun;
        float xSize;
        float ySize;
        float zSize;
        int sunIndex;
};

#endif
