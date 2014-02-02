#ifndef FLOORVALUE_H
#define FLOORVALUE_H

#include "model/value.hpp"

class Building;
class Sun;

class FloorValue : public Value {
    public:
        FloorValue();
        ~FloorValue();
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
        virtual float getValue(const Building *bldg, const Sun *sun) const;
        /*
         * Method: calculateExposure
         *
         * Calculates the number of hours of exposer a given floor panel
         * receives. This number is the number of samples for which it is
         * exposed to sun divided by the total number of sun samples taken.
         *
         * Parameters:
         * panelIndices - the indices of the floor panel
         * sun - the sun model being used
         *
         * Returns a float value equal to the number of hours of sunlight.
         */
        float calculateExposure(const indices panelIndices, const Building *bldg, const Sun *sun) const;
        float numberAdjacent(const indices panelIndices, const Building *bldg) const;
    private:
};

#endif
