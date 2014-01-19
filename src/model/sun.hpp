#ifndef SUN_H
#define SUN_H

#include "types.h"

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

	~Sun();

	private:
		float latitude;
		
};

#endif
