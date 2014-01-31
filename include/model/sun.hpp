#ifndef SUN_H
#define SUN_H

#include "types.hpp"
#include <vector>

/* 
 * Class Sun
 *
 * Defines direction of sunlight at a given time of day and latitude.
 * 
 */

class Sun {
	public:
	/*
	 * Constructor: Sun
	 */
	Sun(float latitude);

    /*
     * Constructor: Sun
     *
     * Builds the sun and precalculates n directions from which sunlight will
     * be coming.
     */
    Sun(float latitude, int n);

	~Sun();

    /*
     * Method: build
     *
     * Builds the sun model ahead of time to avoid computation on every queery.
     * Builds the sun model with n individual sample directions. To use these
     * pre calculated directions the caller must use getDirectionForIndex not
     * simply getDirection.
     *
     * Parameter:
     * n - the number of sun directions to calculate
     */
    void build(int n);

    /*
     * Method: getNumberOfSamples
     *
     * Returns the number of precalculated samples.
     */
    int getNumberOfSamples() const;

    /*
     * Method getDirectionForIndex
     *
     * Returns the direction mapped to that index in the precalculated sun
     * directions vector.
     */
    coord getDirectionForIndex(int i) const;

	private:
		float latitude;
        std::vector<coord> directions;
};

#endif
