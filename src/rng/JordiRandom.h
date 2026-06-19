#pragma once

#include <random>
#include <time.h>

class JordiRandom {
    std::default_random_engine rng;

public:
    JordiRandom() = default;

    inline static JordiRandom& Instance() {
        static JordiRandom instance;
        return instance;
    }

    void Init(unsigned long int = time(nullptr));

    double randomDoubleInRange(double minInclusive, double maxExclusive);
    int randomIntInRange(int minInclusive, int maxExclusive);

    double randomDoubleWithVariance(double value, double variance);
    int randomIntWithVariance(int value, int variance);
};
