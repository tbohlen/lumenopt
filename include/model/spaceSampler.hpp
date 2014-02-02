#ifndef SPACESAMPLER_H
#define SPACESAMPLER_H

#include "model/sampler.hpp"
#include "types.hpp"
#include <random>

class Building;

class SpaceSampler: public Sampler {
    public:
        /*
         * Constructor: SpaceSampler
         *
         * Builds the sampler with a template building that is the correct
         * dimensions. Each sample generated will have the same dimensions as
         * this template building.
         *
         * Parameters:
         * templateBldg - the template building object
         */
        SpaceSampler(Building *templateBldg);

        ~SpaceSampler();

        /*
         * Method: generateSample
         *
         * Generates a random building based off the templateBldg. Each floor
         * tile exists with 50% probability.
         *
         * Returns a boolMatrix describing the building.
         */
        virtual boolMatrix generateSample();
    private:
        std::uniform_int_distribution<int> intDistribution;
        void extendFloor(indices p, boolMatrix &sample, boolMatrix &touched);
};

#endif
