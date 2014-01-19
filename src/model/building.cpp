#include "building.hpp"
#include "math.h"
#include "types.h"

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
