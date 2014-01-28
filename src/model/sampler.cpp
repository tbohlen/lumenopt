#include "sampler.hpp"
#include <random>

using namespace std;

Sampler::Sampler(boolMatrix bldgTemplate) : bldgTemplate(bldgTemplate) {

}

boolMatrix Sampler::generateSampler() {
    int i;
    int j;
    int k;
    int iSize = this->bldgTemplate.size();
    default_random_engine generator;
    bernoulli_distribution distribution(0.5);
    boolMatrix sample(iSize);
	for (i = 0; i < iSize; i++) {
        int jSize = this->bldgTemplate[i].size();
        sample[i].resize(jSize);
		for (j = 0; j < jSize; j++) {
            int kSize = this->bldgTemplate[i][j].size();
            sample[i][j].resize(kSize)
			for (k = 0; k < kSize; k++) {
                sample[i][j][k] = distribution(generator);
			}
		}
	}
    return sample;
}
