#include "model/building.hpp"
#include "math.h"
#include "helpers.hpp"
#include <string>

using namespace std;

Building::Building() {

}

Building::Building(boolMatrix exists, float xSize, float ySize, float zSize) {
	this->exists = exists;
	this->xSize = xSize; // size in m of each x unit
	this->ySize = ySize; // size in m of each y unit
	this->zSize = zSize; // size in m of each z unit

	coordMatrix centroids (exists.size());
	for (int i=0; i<exists.size(); i++) {
		centroids[i].resize(exists[i].size());
		for (int j=0; j<exists[i].size(); j++) {
			centroids[i][j].resize(exists[i][j].size());
			for (int k=0; k<exists[i][j].size(); k++) {
				centroids[i][j][k].x = (float(i) + 0.5)*xSize;
				centroids[i][j][k].y = (float(j) + 0.5)*ySize;
				centroids[i][j][k].z = float(k)*zSize;

			}
		}
	}

}

Building::~Building() {}

bool Building::inShade(indices const panel, coord const sundir) const {
	bool shade = 0; //panel is in sun
	int Nz = this->exists[panel.x][panel.y].size();
	coord c = centroids[panel.x][panel.y][panel.z];
	float dz = zSize;
	float t = -dz/sundir.z;
	for (int i=panel.z+1; i<Nz; i++) {
		//find intersection point on next possible level (px,py,pz)
		float px = c.x - sundir.x*t;
		float py = c.y - sundir.y*t;
		float pz = c.z + dz;
		//find indices of panel associated with intersection point
		int pxind = (int) floor(px/(this->xSize));
		int pyind = (int) floor(py/(this->ySize));
		int pzind = (int) floor(pz/(this->zSize));
		//check if panel exists at this location
		if (this->exists[pxind][pyind][pzind] == 1) {
			shade = 1;
			break;
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
    myAssert(i >= 0);
    myAssert(i < this->exists.size());
    myAssert(j >= 0);
    myAssert(j < this->exists[i].size());
    myAssert(k >= 0);
    myAssert(k < this->exists[i][j].size());
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
    return is;
}

