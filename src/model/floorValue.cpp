#include "model/floorValue.hpp"

FloorValue::FloorValue() {

}

FloorValue::~FloorValue() {

}

#include "model/sun.hpp"
#include "model/building.hpp"
#include <iostream>

using namespace std;

float FloorValue::getValue(const Building *bldg, const Sun *sun) const {
    // for each square of the building, if it exists, calculate its exposure
    int i, j, k;
    float total = 0;
    for (i = 0; i < bldg->getDimension(); i++) {
        for (j = 0; j < bldg->getSecondDimension(i); j++) {
            // TODO: Unroll this loop for the compiler
            for (k = 0; k < bldg->getThirdDimension(i, j); k++) {
                if (bldg->floorExists(i, j, k)) {
                    indices panelIndices;
                    panelIndices.x = i;
                    panelIndices.y = j;
                    panelIndices.z = k;
                    float exposure = (this->numberAdjacent(panelIndices, bldg) - 1) * this->calculateExposure(panelIndices, bldg, sun);
                    total += exposure;
                }
            }
        }
    }

    return total;
}

float FloorValue::calculateExposure(const indices panelIndices, const Building *bldg, const Sun *sun) const {
    int i;
    int num = sun->getNumberOfSamples();
    float total = 0;
    // TODO: check for valid indices
    for (i = 0; i < num; i++) {
        coord sample = sun->getDirectionForIndex(i);
        bool shaded = bldg->inShade(panelIndices, sample);
        total += !shaded;
    }
    return total/(float)num;
}

float FloorValue::numberAdjacent(const indices panelIndices, const Building *bldg) const {
    return bldg->floorExists(panelIndices.x, panelIndices.y+1, panelIndices.z) +
        bldg->floorExists(panelIndices.x-1, panelIndices.y, panelIndices.z) +
        bldg->floorExists(panelIndices.x+1, panelIndices.y, panelIndices.z) +
        bldg->floorExists(panelIndices.x, panelIndices.y-1, panelIndices.z);
}
