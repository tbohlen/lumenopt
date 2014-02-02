#include "model/spaceSampler.hpp"
#include "model/building.hpp"
#include <iostream>
#include <climits>

using namespace std;

SpaceSampler::SpaceSampler(Building *templateBldg) : Sampler(templateBldg) {
    this->intDistribution = uniform_int_distribution<int>(0, INT_MAX);
}

SpaceSampler::~SpaceSampler() {}

boolMatrix SpaceSampler::generateSample() {
    //cout << "In function" << endl;
    int i;
    int j;
    int k;
    int iDimension = this->templateBldg->getDimension();
    //cout << "Got dimension" << endl;

    boolMatrix sample(iDimension);
    boolMatrix touched(iDimension);

	for (i = 0; i < iDimension; i++) {
        int jDimension = this->templateBldg->getSecondDimension(i);
        sample[i].resize(jDimension);
        touched[i].resize(jDimension);
		for (j = 0; j < jDimension; j++) {
            int kDimension = this->templateBldg->getThirdDimension(i, j);
            sample[i][j].resize(kDimension);
            touched[i][j].resize(kDimension);
            for (k = 0; k < kDimension; k++) {
                touched[i][j][k] = false;
                sample[i][j][k] = false;
            }
		}
	}

    // NOTE: assumes single continuous floors and all floors being the same
    // height. will fail otherwise

    for (i = 0; i < this->templateBldg->getMaxZ(); i++) {
        // pick a random starting point for each floor
        //cout << "looping through floors with i = " << i << endl;
        indices startingPoint;
        startingPoint.x = this->intDistribution(this->generator)
                          % this->templateBldg->getDimension();
        startingPoint.y = this->intDistribution(this->generator)
                          % this->templateBldg->getSecondDimension(startingPoint.x);
        startingPoint.z = i;
        touched[startingPoint.x][startingPoint.y][startingPoint.z] = true;

        //cout << "Founding starting point..." << endl;

        // find its neighbors
        this->extendFloor(startingPoint, sample, touched);
    }

    //cout << "Returning" << endl;

    return sample;
}

void SpaceSampler::extendFloor(indices p, boolMatrix &sample, boolMatrix &touched) {
    // for each neighbor, if it is a valid coordinate, randomly assign it a bool
    // value
    indices n1;
    n1.x = p.x+1;
    n1.y = p.y;
    n1.z = p.z;
    indices n2;
    n2.x = p.x-1;
    n2.y = p.y;
    n2.z = p.z;
    indices n3;
    n3.x = p.x;
    n3.y = p.y+1;
    n3.z = p.z;
    indices n4;
    n4.x = p.x;
    n4.y = p.y-1;
    n4.z = p.z;

    //cout << "Found neighbors" << endl;

    if (this->templateBldg->inbounds(n1) && !touched[n1.x][n1.y][n1.z]) {
        //cout << "Checking first neighbor" << endl;
        touched[n1.x][n1.y][n1.z] = true;
        bool makeFloor = this->bernoulli(this->generator);
        //cout << "Sampled!" << endl;
        sample[n1.x][n1.y][n1.z] = makeFloor;

        if (makeFloor) {
            //cout << "Recursing" << endl;
            this->extendFloor(n1, sample, touched);
        }
    }
    if (this->templateBldg->inbounds(n2) && !touched[n2.x][n2.y][n2.z]) {
        //cout << "Checking second neighbor" << endl;
        touched[n2.x][n2.y][n2.z] = true;
        bool makeFloor = this->bernoulli(this->generator);
        //cout << "Sampled!" << endl;
        sample[n2.x][n2.y][n2.z] = makeFloor;

        if (makeFloor) {
            //cout << "Recursing" << endl;
            this->extendFloor(n2, sample, touched);
        }
    }
    if (this->templateBldg->inbounds(n3) && !touched[n3.x][n3.y][n3.z]) {
        //cout << "Checking third neighbor" << endl;
        touched[n3.x][n3.y][n3.z] = true;
        bool makeFloor = this->bernoulli(this->generator);
        //cout << "Sampled!" << endl;
        sample[n3.x][n3.y][n3.z] = makeFloor;

        if (makeFloor) {
            //cout << "Recursing" << endl;
            this->extendFloor(n3, sample, touched);
        }
    }
    if (this->templateBldg->inbounds(n4) && !touched[n4.x][n4.y][n4.z]) {
        //cout << "Checking fourth neighbor" << endl;
        touched[n4.x][n4.y][n4.z] = true;
        bool makeFloor = this->bernoulli(this->generator);
        //cout << "Sampled!" << endl;
        sample[n4.x][n4.y][n4.z] = makeFloor;

        if (makeFloor) {
            //cout << "Recursing" << endl;
            this->extendFloor(n4, sample, touched);
        }
    }
}
