#include "BuildingParser.hpp"
#include "ImageMaker.hpp"
#include "SceneParser.hpp"
#include "Group.hpp"
#include "types.hpp"
#include <stdio.h>

using namespace std;
int main( int argc, char* argv[]) {
    // create a building model
    // building will be 3 by 3 by 3
    int i;
    int j;
    int k;

    cout << "Building building vector..." << endl;

    vector<vector<vector<bool> > > building;
    building.resize(3);
    for (i = 0; i < 3; i++) {
        building[i].resize(3);
        for (j = 0; j < 3; j++) {
            building[i][j].resize(3);
            for (k = 0; k < 3; k++) {
                if (j != k || i == 0) {
                    building[i][j][k] = true;
                }
            }
        }
    }

    cout << "Creating building parser..." << endl;

    // parse it
    BuildingParser *bldgParser = new BuildingParser(building, 1., 1., 1.);

    cout << "Getting building group..." << endl;

    ObjPtr buildingGroup = bldgParser->getGroup();

    // parse the background scene
    cout << "Creating scene parser..." << endl;
    SceneParser *sceneParser = new SceneParser("scene-building.txt");

    // save it
    Vector3f sunPos(0, 0.5, 1);
    int resolution = 500;
    const char *filename = "building.bmp";
    cout << "Creating Image Maker..." << endl;
    ImageMaker *maker = new ImageMaker(sceneParser);
    cout << "Saving image..." << endl;
    maker->makeImageOfScene(sunPos, buildingGroup, resolution, filename);

    cout << "Done." << endl;

    delete bldgParser;
    delete maker;
    delete sceneParser;

    cout << "Cleaned up." << endl;

    return 0;
}
