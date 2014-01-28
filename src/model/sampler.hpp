#ifndef SAMPLER_H
#define SAMPLER_H

#include "types.hpp"

class Sampler {
    public:
        /*
         * Constructor: Sampler
         *
         * Builds the sampler with a template building that is the correct
         * dimensions. Each sample generated will have the same dimensions as
         * this template building.
         *
         * Parameters:
         * bldgTemplate - the template building object
         */
        Sampler(boolMatrix bldgTemplate);

        /*
         * Method: generateSample
         *
         * Generates a random building based off the bldgTemplate. Each floor
         * tile exists with 50% probability.
         *
         * Returns a boolMatrix describing the building.
         */
        boolMatrix generateSample();
    private:
        boolMatrix bldgTemplate;
};

#endif
