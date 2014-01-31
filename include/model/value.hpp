#ifndef VALUE_H
#define VALUE_H

#include "types.hpp"

class Building;
class Sun;

class Value {
    public:
        Value();
        ~Value();
        /*
         * Method: getValue
         * 
         * Calculates the value function of the design. In this case, the value
         * is the sum of the number of hours of sum each floor panel in the
         * building receives. This is calculated by interating over all floor
         * panels and calling calculateExposure.
         *
         * Parameters:
         * bldg - the bldg to score
         * sun - the sun model to use
         *
         * Returns a float value for the design.
         */
        float getValue(const Building *bldg, const Sun *sun) const;
        /*
         * Method: calculateExposure
         *
         * Calculates the number of hours of exposer a given floor panel
         * receives.
         *
         * Parameters:
         * panelIndices - the indices of the floor panel
         * sun - the sun model being used
         *
         * Returns a float value equal to the number of hours of sunlight.
         */
        float calculateExposure(const indices panelIndices, const Building *bldg, const Sun *sun) const;

    private:
};

#endif
