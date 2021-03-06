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

        virtual ~Sampler();

        /*
         * Method: generateSample
         *
         * Generates a random building based off the templateBldg. Each floor
         * tile exists with 50% probability.
         *
         * Returns a boolMatrix describing the building.
         */
        virtual boolMatrix generateSample();
    protected:
        Building *templateBldg;
        std::default_random_engine generator;
        std::bernoulli_distribution bernoulli;
};

#endif
