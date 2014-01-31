#include "model/sampler.hpp"
#include "model/building.hpp"
#include <random>

using namespace std;

Sampler::Sampler(Building *templateBldg) : templateBldg(templateBldg) {

}

boolMatrix Sampler::generateSample() {
    int i;
    int j;
    int k;
    int iDimension = this->templateBldg->getDimension();
    default_random_engine generator;
    bernoulli_distribution distribution(0.5);
    boolMatrix sample(iDimension);
	for (i = 0; i < iDimension; i++) {
        int jDimension = this->templateBldg->getSecondDimension(i);
        sample[i].resize(jDimension);
		for (j = 0; j < jDimension; j++) {
            int kDimension = this->templateBldg->getThirdDimension(i, j);
            sample[i][j].resize(kDimension);
			for (k = 0; k < kDimension; k++) {
                sample[i][j][k] = distribution(generator);
			}
		}
	}
    return sample;
}
