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

    double randomInRange(double minInclusive, double maxExclusive);
    int randomInRange(int minInclusive, int maxExclusive);

    double randomWithVariance(double value, double variance);
    int randomWithVariance(int value, int variance);
};
