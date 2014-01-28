#ifndef BUILDING_H
#define BUILDING_H

#include "types.h"
#include <iostream>

#define MAX_PARSER_TOKEN_LENGTH 100

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
		 * Method: inShade
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

        /*
         * Method: getSize
         *
         * Returns the size of the top-level dimension of the boolMatrix.
         */
        int getSize();

        /*
         * Method: getSecondSize
         *
         * Returns the size of the ith row of the exists matrix.
         */
        int getSecondSize(int i);

        /*
         * Method: getThirdSize
         *
         * Returns the size of the jth column of the ith row of the exists
         * matrix.
         */
        int getThirdSize(int i, int j);

        /*
         * Method: floorExists
         *
         * Returns true if there is a floor panel at i, j, k and false if not.
         */
        bool floorExists(int i, int j, int k);

	private:
		boolMatrix exists;
		float xSize;
		float ySize;
		float zSize;
		coordMatrix centroids;

};

/*
 * Operator: <<
 * 
 * Redefines the << operator for this class so that we can easily print this to
 * a file.
 */
std::ostream& operator << (std::ostream& os, const Building& b);

/*
 * Operator: >>
 * 
 * Redefines the >> operator for this class so that we can easily load this
 * object from a stream.
 */
std::istream& operator >> (std::istream& os, const Building& b);

#endif
