#ifndef PROBABILITYGENERATOR_H
#define PROBABILITYGENERATOR_H

#include <random>
#include <iostream>

class ProbabilityGenerator {
private:
    std::mt19937 generator; // Mersenne Twister random number engine

public:
    // Constructor: Seed the generator
    ProbabilityGenerator() 
        : generator(std::random_device{}()) {}

    // Generate a random floating-point number in a given range [min, max]
    float getRandomProb(float min = 0, float max = 1) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(generator);
    }
};

#endif