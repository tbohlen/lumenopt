#ifndef SAMPLER_H
#define SAMPLER_H

#include "types.hpp"
#include <random>

class Building;

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
         * templateBldg - the template building object
         */
        Sampler(Building *templateBldg);

        /*
         * Method: generateSample
         *
         * Generates a random building based off the templateBldg. Each floor
         * tile exists with 50% probability.
         *
         * Returns a boolMatrix describing the building.
         */
        boolMatrix generateSample(std::bernoulli_distribution &distribution, std::default_random_engine &generator);
    private:
        Building *templateBldg;
};

#endif
