//
// Created by Kamil Kosiński on 09/05/2017.
//

#ifndef GENETIC_ALGORITHM_RANDOMGEN_H
#define GENETIC_ALGORITHM_RANDOMGEN_H

#include <random>
#include <chrono>

namespace RGen {
    long long my_seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(my_seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double next() {
        return distribution(generator);
    }
};

#endif //GENETIC_ALGORITHM_RANDOMGEN_H
