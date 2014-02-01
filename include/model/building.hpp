#ifndef BUILDING_H
#define BUILDING_H

#include "types.hpp"
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
        Building();

		Building(boolMatrix exists, float xSize, float ySize, float zSize);

		~Building();

		/*
		 * Method: inShade
		 *
		 * Determines if ray from centroid to the sun hits another panel,
		 * thereby putting it in shade. If the panel requested does not exist,
         * this returns 1.
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
         * Method: getDimension
         *
         * Returns the size of the top-level dimension of the boolMatrix.
         */
        int getDimension() const;

        /*
         * Method: getSecondDimension
         *
         * Returns the size of the ith row of the exists matrix.
         */
        int getSecondDimension(int i) const;

        /*
         * Method: getThirdDimension
         *
         * Returns the size of the jth column of the ith row of the exists
         * matrix.
         */
        int getThirdDimension(int i, int j) const;

        /*
         * Method: floorExists
         *
         * Returns true if there is a floor panel at i, j, k and false if not.
         */
        bool floorExists(int i, int j, int k) const;

        float getXSize() const;
        float getYSize() const;
        float getZSize() const;

        friend std::istream& operator>> (std::istream& is, Building& b);
        friend std::ostream& operator<< (std::ostream& os, Building& b);
		boolMatrix exists;

	private:
		float xSize;
		float ySize;
		float zSize;
        int maxZ;
		coordMatrix centroids;
};

#endif
