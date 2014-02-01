#include "model/sun.hpp"
#include "helpers.hpp"
#include <math.h>

#define PI 3.14159265

Sun::Sun(float latitude) : latitude(latitude) {

}

Sun::Sun(float latitude, int n) : latitude(latitude) {
    this->build(n);
}

Sun::~Sun() {

}

void Sun::build(int n) {
    assert(n > 0);
    directions.resize(n);
    int i;
    for (i = 0; i < n; i++) {
        coord dir;
        dir.x = 0;
        dir.y = -1 * cos((i * PI)/(n-1));
        dir.z = -1 * sin((i * PI)/(n-1));
        directions[i] = dir;
    }
}

int Sun::getNumberOfSamples() const {
    return this->directions.size();
}

coord Sun::getDirectionForIndex(int i) const {
    myAssert(i >= 0);
    myAssert(i < this->directions.size());
    return this->directions[i];
}
