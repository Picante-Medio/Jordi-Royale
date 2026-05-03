#include "JordiRandom.h"
#include <random>

void
JordiRandom::Init(unsigned long int seed) {
    rng = std::default_random_engine(seed);
}

double 
JordiRandom::randomInRange(double minInclusive, double maxExclusive) {
    std::uniform_real_distribution<double> urd(minInclusive, maxExclusive);
    return urd(rng);
}

int 
JordiRandom::randomInRange(int minInclusive, int maxInclusive) {
    std::uniform_int_distribution<int> uid(minInclusive, maxInclusive);
    return uid(rng);
}

double 
JordiRandom::randomWithVariance(double value, double variance){
    return value + randomInRange(-variance, variance);
}

int 
JordiRandom::randomWithVariance(int value, int variance){
    return value + randomInRange(-variance, variance);
}
