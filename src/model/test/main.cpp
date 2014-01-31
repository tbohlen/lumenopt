#include "model/building.hpp"
#include <string>
#include <iostream>
#include <sstream>

#define XSIZE 1.0
#define YSIZE 2.0
#define ZSIZE 0.5

// Test set for the model

using namespace std;

int main(int argc, char *argv[]) {
    int testsFailed = 0;
    int tests = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Building
    ////////////////////////////////////////////////////////////////////////////

    // creating a building
    boolMatrix example(1);
    example[0].resize(2);
    example[0][0].resize(3);
    example[0][1].resize(6);
    example[0][0][0] = true;
    example[0][0][1] = true;
    example[0][0][2] = true;
    example[0][1][0] = true;
    example[0][1][1] = false;
    example[0][1][2] = false;
    example[0][1][3] = true;
    example[0][1][4] = true;
    example[0][1][5] = true;

    Building *bldg = new Building(example, XSIZE, YSIZE, ZSIZE);

    // testing sizes
    tests++;
    if (bldg->getDimension() != 1) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Building's first dimension is not 1!" << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building::getDimension works" << endl;
    }

    tests++;
    if (bldg->getSecondDimension(0) != 2) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Building's second dimension is not 2!" << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building::getSecondDimension works" << endl;
    }

    tests++;
    if (bldg->getThirdDimension(0, 0) != 3 || bldg->getThirdDimension(0, 1) != 6) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Building's third dimensions do not match expectations!" << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building::getThirdDimension works" << endl;
    }

    //TODO: include assertion tests

    // test values in the boolMatrix
    tests++;
    if (bldg->floorExists(0, 0, 0) != true || bldg->floorExists(0, 1, 1) != false || bldg->floorExists(0, 0, 2) != true || bldg->floorExists(0, 1, 0) != true) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m floorExists returned wrong value for (0, 0, 0)." << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building::floorExists works." << endl;
    }

    // test inShade

    // test x, y, and z sizes
    tests++;
    if (bldg->getXSize() != XSIZE) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Building::getXSize fails." << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building::getXSize functions works." << endl;
    }

    tests++;
    if (bldg->getYSize() != YSIZE) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Building::getYSize fails." << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building::getYSize functions works." << endl;
    }

    tests++;
    if (bldg->getZSize() != ZSIZE) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Building::getZSize fails." << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building::getZSize functions works." << endl;
    }

    // test centroids

    // test saving
    stringstream ss;
    ss << *bldg;
    Building *secondBldg = new Building();
    ss >> *secondBldg;
    stringstream ss2;
    ss2 << *secondBldg;
    string s = ss.str();
    string s2 = ss2.str();

    tests++;
    if (s.compare(s2) != 0) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Building serialization failed to produce identical objects." << endl;
        //cout << "FIRST BUILDING" << endl << endl;
        //cout << s << endl << endl;
        //cout << "SECOND BUILDING" << endl << endl;
        //cout << s2 << endl << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building serialization works." << endl;
    }

    delete bldg;
    delete secondBldg;

    cout << endl << tests << " tests run, " << testsFailed << " tests failed." << endl;

}

