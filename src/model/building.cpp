#include "building.hpp"
#include "math.h"
#include "types.h"
#include <cassert>
#include <string>

using namespace std;

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

bool Building::checkIntersect(indices const panel, coord const sundir) const {
	bool shade = 0; //panel is in sun
	Nz = this->exists[panel.x][panel.y].size();
	c = centroids[panel.x][panel.y][panel.z];
	dz = zSize;
	t = -dz/sundir.z;
	for (int i=panel.z+1; i<Nz; i++) {
		//find intersection point on next possible level (px,py,pz)
		px = c.x - sundir.x*t;
		py = c.y - sundir.y*t;
		pz = c.z + dz;
		//find indices of panel associated with intersection point
		pxind = floor(px/(this->xSize));
		pyind = floor(py/(this->ySize));
		pzind = floor(pz/(this->zSize));
		//check if panel exists at this location
		if (this->exists[pxind][pyind][pzind] == 1) {
			shade = 1;
			break;
		}
	}
	return shade;
}

int Building::getSize() {
    return this->exists.size();
}
int Building::getSecondSize(int i) {
    assert(i < this->exists.size());
    return this->exists[i].size();
}

int Building::getThirdSize(int i, int j) {
    assert(i < this->exists.size());
    assert(j < this->exists[i].size());
    return this->exists[i][j].size();
}

bool Building::floorExists(int i, int j, int k) {
    assert(i >= 0);
    assert(i < this->exists.size());
    assert(j >= 0);
    assert(j < this->exists[i].size());
    assert(k >= 0);
    assert(k < this->exists[i][j].size());
    return this->exists[i][j][k];
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

ostream& operator << (ostream& os, const Building& b) {
    // save the first size
    int i, j, k;
    int size = b.getSize();
    os << "Size: " << size << endl;
    for (i = 0; i < size; i++) {
        int secondSize = b.getSecondSize(i);
        os << "nextX: " << secondSize << end;
        for (j = 0; j < secondSize; j++) {
            int thirdSize = b.getThirdSize(i, j);
            os << "nextY: " << thirdSize << endl;
            for (k = 0; k < thirdSize; k++) {
                os << "panel: " << b.exists(i, j, k) << endl;
            }
        }
    }
    os << "end" << endl;
}

istream& operator >> (istream& os, const Building& b) {
    int i = -1;
    int j = -1;
    int k = -1;

    string str;
    os >> str;
    assert(str.compare("Size:") == 0);

    int size;
    os >> size;
    b.exists.resize(size);
    while (os >> str) {
        // read through each word
        if (str.compare("panel:") == 0) {
            // load the next panel
            k++;
            os >> b.exists[i][j][k];
        }
        else if (str.compare("nextX:") == 0) {
            // load the size of the next x array
            i++;
            int xSize;
            os >> xSize;
            b.exists[i].resize(size);
        }
        else if (str.compare("nextY:") == 0) {
            // load the size of the next y array
            j++;
            int ySize;
            os >> ySize;
            b.exists[i][j].resize(ySize);
        }
        else if (str.compare("end") == 0) {
            // exit
            break;
        }
    }
}

