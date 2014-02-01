#include "model/building.hpp"
#include "model/sun.hpp"
#include "model/value.hpp"
#include "helpers.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "types.hpp"

#define XSIZE 1.0
#define YSIZE 2.0
#define ZSIZE 0.5
#define EPSILON 0.000001
#define PI 3.14159265

// Test set for the model

// TODO: Add out-of-bounds tests

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
        cout << "\033[31mFAIL:\033[0m floorExists returned wrong value." << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building::floorExists works." << endl;
    }

    // test inShade
    // TODO: Test additional points
    // TODO: Test out-of-bounds assertions
    tests++;
    indices p1; // bottom left. lit on diagonal
    p1.x = 0;
    p1.y = 0;
    p1.z = 0;
    indices p2; //  top left. Lit straight down
    p2.x = 0;
    p2.y = 0;
    p2.z = 2;
    indices p3; // second up on right. Does not exist
    p3.x = 0;
    p3.y = 1;
    p3.z = 1;
    coord dir1; // straight down
    dir1.x = 0;
    dir1.y = 0;
    dir1.z = -1;
    coord dir2; // diagonal
    dir2.x = 0;
    dir2.y = -1;
    dir2.z = -0.5;
    coord dir3;
    dir3.x = 0;
    dir3.y = -1;
    dir3.z = 0;
    bool answerOne = bldg->inShade(p1, dir1); // should be true
    bool answerTwo = bldg->inShade(p1, dir2); // should be false
    bool answerThree = bldg->inShade(p2, dir1); // should be false
    bool answerFour = bldg->inShade(p2, dir2); // should be true
    bool answerFive = bldg->inShade(p1, dir3); // should be false
    bool answerSix = bldg->inShade(p3, dir1); // should be true
    if (!answerOne || answerTwo || answerThree || !answerFour || answerFive || !answerSix) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Building::inShade returned wrong value" << endl;
        //cout << "One: " << answerOne << endl;
        //cout << "Two: " << answerTwo << endl;
        //cout << "Three: " << answerThree << endl;
        //cout << "Four: " << answerFour << endl;
        //cout << "Five: " << answerFive << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Building::floorExists works." << endl;
    }


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

    // TODO: test centroids

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


    ////////////////////////////////////////////////////////////////////////////
    // Sun
    ////////////////////////////////////////////////////////////////////////////

    Sun *sun = new Sun(10, 10);
    // make sure that the directions are close. Our values should be normalized, so
    // that means values will be less than 1. EPSILON defined at top of file
    float y0 = -1 * cos(0);
    float z0 = -1 * sin(0);
    float y1 = -1 * cos(PI/9);
    float z1 = -1 * sin(PI/9);
    float y7 = -1 * cos((7*PI)/9);
    float z7 = -1 * sin((7*PI)/9);

    tests++;
    int num = sun->getNumberOfSamples();
    if(num != 10) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Sun created " << num << " samples instead of 10." << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Sun construction works." << endl;
    }

    tests++;
    coord zero = sun->getDirectionForIndex(0);
    coord one = sun->getDirectionForIndex(1);
    coord seven = sun->getDirectionForIndex(7);
    if (!compFloat(zero.x, 0.0, EPSILON) || !compFloat(zero.y, y0, EPSILON) ||
        !compFloat(zero.z, z0, EPSILON) || !compFloat(one.x, 0.0, EPSILON) ||
        !compFloat(one.y, y1, EPSILON) || !compFloat(one.z, z1, EPSILON) ||
        !compFloat(seven.x, 0.0, EPSILON) || !compFloat(seven.y, y7, EPSILON) ||
        !compFloat(seven.z, z7, EPSILON)) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Sun getDirectionForIndex does not work." << endl;
        //cout << "Calc'd zero: " << "(" << zero.x << ", " << zero.y << ", " << zero.z << ")" << endl;
        //cout << "Correct zero: " << "(" << 0.0 << ", " << y0 << ", " << z0 << ")" << endl;
        //cout << "Calc'd one: " << "(" << one.x << ", " << one.y << ", " << one.z << ")" << endl;
        //cout << "Correct one: " << "(" << 0.0 << ", " << y1 << ", " << z1 << ")" << endl;
        //cout << "Calc'd seven: " << "(" << seven.x << ", " << seven.y << ", " << seven.z << ")" << endl;
        //cout << "Correct seven: " << "(" << 0.0 << ", " << y7 << ", " << z7 << ")" << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Sun::getDirectionForIndex works." << endl;
    }

    delete sun;

    ////////////////////////////////////////////////////////////////////////////
    // Value
    ////////////////////////////////////////////////////////////////////////////

    boolMatrix smallMatrix(2);
    smallMatrix[0].resize(2);
    smallMatrix[1].resize(2);
    smallMatrix[0][0].resize(2);
    smallMatrix[0][1].resize(2);
    smallMatrix[1][0].resize(2);
    smallMatrix[1][1].resize(2);
    smallMatrix[0][0][0] = 1;
    smallMatrix[0][0][1] = 1;
    smallMatrix[0][1][0] = 1;
    smallMatrix[0][1][1] = 1;
    smallMatrix[1][0][0] = 1;
    smallMatrix[1][0][1] = 1;
    smallMatrix[1][1][0] = 1;
    smallMatrix[1][1][1] = 1;
    Building *smallBldg = new Building(smallMatrix, 1, 1, 1);
    Sun *secondSun = new Sun(10, 5);
    Value *value = new Value();

    // test the calculateExposure function
    indices panelOne;
    panelOne.x = 0;
    panelOne.y = 0;
    panelOne.z = 0;
    indices panelTwo;
    panelTwo.x = 1;
    panelTwo.y = 1;
    panelTwo.z = 0;
    indices panelThree;
    panelThree.x = 1;
    panelThree.y = 1;
    panelThree.z = 1;
    float expOne = value->calculateExposure(panelOne, smallBldg, secondSun);
    float expTwo = value->calculateExposure(panelTwo, smallBldg, secondSun);
    float expThree = value->calculateExposure(panelThree, smallBldg, secondSun);

    tests++;
    if (!compFloat(expOne, 3.0/5.0, EPSILON) ||
        !compFloat(expTwo, 3.0/5.0, EPSILON) ||
        !compFloat(expThree, 1.0, EPSILON)) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Value::calculateExposure does not work." << endl;
        //cout << expOne << " compared to " << 3.0/5.0 << endl;
        //cout << expTwo << " compared to " << 3.0/5.0 << endl;
        //cout << expThree << " compared to " << 1.0 << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Value::calculateExposure works." << endl;
    }

    // test the getValue function
    float correctValue = 4.0 + ((3.0/5.0) * 4.0);
    float measuredValue = value->getValue(smallBldg, secondSun);

    tests++;
    if (!compFloat(measuredValue, correctValue, EPSILON)) {
        testsFailed++;
        cout << "\033[31mFAIL:\033[0m Value::getValue does not work." << endl;
        //cout << measuredValue << " compared to " << correctValue << endl;
    }
    else {
        cout << "\033[32mOK:\033[0m   Value::getValue works." << endl;
    }

    // cleanup
    delete smallBldg;
    delete secondSun;
    delete value;

    cout << endl << tests << " tests run, " << testsFailed << " tests failed." << endl;
}

