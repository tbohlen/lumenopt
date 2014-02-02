#ifndef VALUE_H
#define VALUE_H

#include "types.hpp"

class Building;
class Sun;

class Value {
    public:
        Value() {};

        virtual ~Value() {};
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
        virtual float getValue(const Building *bldg, const Sun *sun) const = 0;

    private:
};

#endif
