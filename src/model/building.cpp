#include "model/building.hpp"
#include "math.h"
#include "helpers.hpp"
#include <string>
#include <iostream>

#define EPSILON 0.000001

using namespace std;

Building::Building() {
    this->maxZ = 0;
}

Building::Building(boolMatrix exists, float xSize, float ySize, float zSize) {
	this->exists = exists;
	this->xSize = xSize; // size in m of each x unit
	this->ySize = ySize; // size in m of each y unit
	this->zSize = zSize; // size in m of each z unit
    this->maxZ = 0;

    this->makeCentroids();
}

Building::~Building() {}

void Building::makeCentroids() {
	this->centroids.resize(exists.size());
	for (int i=0; i<this->exists.size(); i++) {
		this->centroids[i].resize(exists[i].size());
		for (int j=0; j<this->exists[i].size(); j++) {
            int zDim = this->exists[i][j].size();
            if (zDim > this->maxZ) { this->maxZ = zDim; }
			this->centroids[i][j].resize(zDim);
			for (int k=0; k<this->exists[i][j].size(); k++) {
				this->centroids[i][j][k].x = (float(i) + 0.5)*this->xSize;
				this->centroids[i][j][k].y = (float(j) + 0.5)*this->ySize;
				this->centroids[i][j][k].z = float(k)*this->zSize;
			}
		}
	}
}

bool Building::inShade(indices const panel, coord const sundir) const {
    // make sure this panel exists
    if (panel.x < 0 || panel.x >= this->exists.size() ||
        panel.y < 0 || panel.y >= this->exists[panel.x].size() ||
        panel.z < 0 || panel.z >= this->exists[panel.x][panel.y].size()) {
        return 1;
    }

    // if the z component is 0 then the panel is light at an angle
    if (sundir.z < EPSILON && sundir.z > -EPSILON) {
        return 0; // not in shade if the sun is coming in horizontally
    }

	bool shade = 0; //panel is in sun
    coord c = this->centroids[panel.x][panel.y][panel.z];
    float dz = zSize;
    //cout << "dz is " << zSize << endl;
    float t = -dz/sundir.z;
    //cout << "T is " << t << endl;
	for (int i=panel.z+1; i<this->maxZ; i++) {
		//find intersection point on next possible level (px,py,pz)
        float px = c.x - (i-panel.z) * sundir.x*t;
        float py = c.y - (i-panel.z) * sundir.y*t;
        float pz = c.z + (i-panel.z) * dz;
        //cout << "Testing " << px << ", " << py << ", " << pz << endl;
		//find indices of panel associated with intersection point
        int pxind = (int) floor(px/(this->xSize));
        int pyind = (int) floor(py/(this->ySize));
        int pzind = (int) floor(pz/(this->zSize));
        //cout << "Testing " << pxind << ", " << pyind << ", " << pzind << endl;
        // make sure that this is a valid index before checking
        if (pxind >= 0 && pxind < this->exists.size() &&
            pyind >= 0 && pyind < this->exists[pxind].size() &&
            pzind >= 0 && pzind < this->exists[pxind][pyind].size()) {
            //cout << "In if" << endl;
            if (this->exists[pxind][pyind][pzind] == 1) {
                shade = 1;
                break;
            }
        }
	}
	return shade;
}

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

int Building::getDimension() const {
    return this->exists.size();
}
int Building::getSecondDimension(int i) const {
    myAssert(i >= 0);
    myAssert(i < this->exists.size());
    return this->exists[i].size();
}

int Building::getThirdDimension(int i, int j) const {
    myAssert(i >= 0);
    myAssert(i < this->exists.size());
    myAssert(j >= 0);
    myAssert(j < this->exists[i].size());
    return this->exists[i][j].size();
}

bool Building::floorExists(int i, int j, int k) const {
    if (i < 0 || i >= this->exists.size() ||
        j < 0 || j >= this->exists[i].size() ||
        k < 0 || k >= this->exists[i][j].size()) {
        return false;
    }
    return this->exists[i][j][k];
}

float Building::getXSize() const {
    return this->xSize;
}
float Building::getYSize() const {
    return this->ySize;
}
float Building::getZSize() const {
    return this->zSize;
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

ostream& operator<< (ostream& os, Building& b) {
    // save the first size
    int i, j, k;
    int size = b.getDimension();
    os << "Xsize: " << b.xSize << endl;
    os << "Ysize: " << b.ySize << endl;
    os << "Zsize: " << b.zSize << endl;
    os << "Size: " << size << endl;
    for (i = 0; i < size; i++) {
        int secondDimension = b.getSecondDimension(i);
        os << "nextX: " << secondDimension << endl;
        for (j = 0; j < secondDimension; j++) {
            int thirdDimension = b.getThirdDimension(i, j);
            os << "nextY: " << thirdDimension << endl;
            for (k = 0; k < thirdDimension; k++) {
                os << "panel: " << b.floorExists(i, j, k) << endl;
            }
        }
    }
    os << "end" << endl;
    return os;
}

istream& operator>> (istream& is, Building& b) {
    int i = -1;
    int j = -1;
    int k = -1;

    string str;

    is >> str;
    myAssert(str.compare("Xsize:") == 0);
    is >> b.xSize;

    is >> str;
    myAssert(str.compare("Ysize:") == 0);
    is >> b.ySize;

    is >> str;
    myAssert(str.compare("Zsize:") == 0);
    is >> b.zSize;

    is >> str;
    myAssert(str.compare("Size:") == 0);
    int size;
    is >> size;
    b.exists.resize(size);

    while (is >> str) {
        // read through each word
        if (str.compare("panel:") == 0) {
            // load the next panel
            k++;
            bool ex;
            is >> ex;
            b.exists[i][j][k] = ex;
        }
        else if (str.compare("nextX:") == 0) {
            // load the size of the next x array
            i++;
            j = -1;
            k = -1;
            int ySize;
            is >> ySize;
            b.exists[i].resize(ySize);
        }
        else if (str.compare("nextY:") == 0) {
            // load the size of the next y array
            j++;
            k = -1;
            int zSize;
            is >> zSize;
            b.exists[i][j].resize(zSize);
        }
        else if (str.compare("end") == 0) {
            // exit
            break;
        }
    }

    b.makeCentroids();

    return is;
}

