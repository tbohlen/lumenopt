#ifndef BUILDING_H
#define BUILDING_H

#include "types.h"

/*
 * Class Building
 *
 * Constructs a Building object containing a 3D matrix of panel centroids and
 * boolean value determining existance of panel.
 */

class Building { 
	public:
		/*
		 * Constructor: Building
		 */
		Building(boolMatrix exists, float xSize, float ySize, float zSize);

		~Building();
		
		/*
		 * Method inShade
		 *
		 * Determines if ray from centroid to the sun hits another panel,
		 * thereby putting it in shade.
		 * 
		 * Inputs:
		 * 	panel - indices of the panel whose centroid we want
		 * 	sundir - unit vector in the direction of sunlight (towards the
		 * 	building)
		 *
		 * Returns a boolean.
		 * 	True: hits panel, panel is in shade
		 * 	False: no panel intersects with ray, panel is in sunlight
		 */
		bool inShade(indices const panel, coord const sundir) const; 

	private:
		boolMatrix exists;
		float xSize;
		float ySize;
		float zSize;
		coordMatrix centroids;
		
};

#endif
