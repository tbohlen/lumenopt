// the first version of the main function simply runs the optimizer a set number
// of times and chooses the building with the best result. It then saves that
// building to a file

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "model/building.hpp"
#include "model/sampler.hpp"
#include "types.hpp"

#define DIM 10
#define SECOND_DIM 4
#define THIRD_DIM 15
#define XSIZE 1
#define YSIZE 1
#define ZSIZE 1

using namespace std;

Building *temp;
std::string templateFileName = "NO FILE NAME PROVIDED";
int runs = 100;

void readArguments(int argc, char *argv[]) {
    int argNum;

    for (argNum = 0; argNum < argc; argNum++) {
        char *arg = argv[argNum];

        if (strcmp(arg, "--template") == 0 || strcmp(arg, "-t") == 0) {
            // specifies a template file. The next argument is the name of the
            // template building.
            argNum++;
            templateFileName = argv[argNum];
        }
        else if (strcmp(arg, "--runs") == 0 || strcmp(arg, "-r") == 0) {
            // specifies the number of runs of the monte carlo
            // The nest argument is the number
            argNum++;
            runs = atoi(argv[argNum]);
        }
    }
}

int main( int argc, char *argv[]) {
    std::string fName = "best.bldg";
    int i;
    int j;
    int k;

    Building *templateBuilding;
    if (templateFileName.compare("NO FILE NAME PROVIDED") == 0) {
        // a template has been provided so load it
        templateBuilding = new Building();
        ifstream templateFile;
        templateFile.open(templateFileName);
        templateFile >> *templateBuilding;
        templateFile.close();
    }
    else {
        // build the matrix describing the building
        boolMatrix example(DIM);
        for (i = 0; i < example.size(); i++) {
            example[i].resize(SECOND_DIM);
            for (j = 0; j < SECOND_DIM; j++) {
                example[i][j].resize(THIRD_DIM);
                for (k = 0; k < THIRD_DIM; k++) {
                    example[i][j][k] = true;
                }
            }
        }

        templateBuilding = new Building(example, XSIZE, YSIZE, ZSIZE);
    }


    // build a sampler using that template
    Sampler *sampler = new Sampler(templateBuilding);
    Building *bestBuilding = NULL;
    float bestScore = 0;

    // run the test a bunch of times
    for (i = 0; i < runs; i++) {
        boolMatrix exists = sampler->generateSample();
        Building *bldg = new Building(exists, XSIZE, YSIZE, ZSIZE);
        // test the building
        float score = 0;

        if (score > bestScore) {
            // if this building did better than the last, save it
            if (bestBuilding != NULL) { delete bestBuilding; }
            bestBuilding = bldg;
            bestScore = score;
        }
    }

    // save the building
    ofstream saveFile(fName);
    saveFile << *bestBuilding;
    saveFile.close();

    if (bestBuilding != NULL) { delete bestBuilding; }
    delete sampler;

    return 0;
}
