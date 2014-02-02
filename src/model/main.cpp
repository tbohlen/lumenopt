// the first version of the main function simply runs the optimizer a set number
// of times and chooses the building with the best result. It then saves that
// building to a file

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include "model/building.hpp"
#include "model/sampler.hpp"
#include "model/floorValue.hpp"
#include "model/sun.hpp"
#include "types.hpp"

#define DIM 4
#define SECOND_DIM 4
#define THIRD_DIM 6
#define XSIZE 1
#define YSIZE 1
#define ZSIZE 1

using namespace std;

Building *temp;
std::string templateFileName = "NO FILE NAME PROVIDED";
int runs = 100;
int suns = 12;

void readArguments(int argc, char *argv[]) {
    int argNum;

    for (argNum = 1; argNum < argc; argNum++) {
        char *arg = argv[argNum];

        if (strcmp(arg, "--template") == 0 || strcmp(arg, "-t") == 0) {
            // specifies a template file. The next argument is the name of the
            // template building.
            argNum++;
            assert(argNum < argc);
            templateFileName = argv[argNum];
        }
        else if (strcmp(arg, "--runs") == 0 || strcmp(arg, "-r") == 0) {
            // specifies the number of runs of the monte carlo
            // The nest argument is the number
            argNum++;
            assert(argNum < argc);
            runs = atoi(argv[argNum]);
        }
        else if (strcmp(arg, "--suns") == 0 || strcmp(arg, "-s") == 0) {
            argNum++;
            assert(argNum < argc);
            suns = atoi(argv[argNum]);
        }
    }
}

int main( int argc, char *argv[]) {
    cout << "Reading arguments" << endl;

    readArguments(argc, argv);

    std::string fName = "best.bldg";
    int i;
    int j;
    int k;

    cout << "Building the template building" << endl;
    Building *templateBuilding;
    if (templateFileName.compare("NO FILE NAME PROVIDED") == 0) {
        // a template has been provided so load it
        cout << "No template file provided. Building from scratch" << endl;
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
    else {
        cout << "Template file provided. Parsing it" << endl;
        templateBuilding = new Building();
        ifstream templateFile;
        templateFile.open(templateFileName);
        templateFile >> *templateBuilding;
        templateFile.close();
    }

    // build the sun model
    cout << "Building sun" << endl;
    Sun *sun = new Sun(45.5, suns);

    // build to value function
    cout << "Building value" << endl;
    Value *value = new FloorValue();

    // build a sampler using that template
    cout << "Building sampler" << endl;
    Sampler *sampler = new Sampler(templateBuilding);
    Building *bestBuilding = NULL;
    float bestScore = 0;

    default_random_engine generator;
    bernoulli_distribution distribution(0.5);

    // run the test a bunch of times
    cout << "Running monte carlo" << endl;
    for (i = 0; i < runs; i++) {
        boolMatrix exists = sampler->generateSample(distribution, generator);
        Building *bldg = new Building(exists, XSIZE, YSIZE, ZSIZE);
        // test the building
        float score = value->getValue(bldg, sun);

        if (score > bestScore) {
            cout << "Sample " << i << " with score " << score << " is new best" << endl;
            // if this building did better than the last, save it
            if (bestBuilding != NULL) { delete bestBuilding; }
            bestBuilding = bldg;
            bestScore = score;
        }
        else {
            //cout << "Sample " << i << " with score " << score << " is worse that previous best." << endl;
            delete bldg;
        }
    }

    // save the building
    cout << "Saving best with score " << bestScore << endl;
    ofstream saveFile(fName);
    saveFile << *bestBuilding;
    saveFile.close();

    cout << "Cleaning up" << endl;
    if (bestBuilding != NULL) { delete bestBuilding; }
    delete sampler;
    delete sun;
    delete templateBuilding;
    delete value;

    return 0;
}
