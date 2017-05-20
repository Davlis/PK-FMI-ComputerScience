//
// Created by Kamil Kosiński on 09/05/2017.
//

#ifndef GENETIC_ALGORITHM_POPULATION_H
#define GENETIC_ALGORITHM_POPULATION_H

#include <iostream>
#include <functional>
#include "Specimen.h"

class Population {
    int size;
    int amountOfVariables;
    int amountOfBits;
    double probabilityOfCross;
    double probabilityOfMutation;
    double startOfRange;
    double endOfRange;
    double dx;

    std::vector<Specimen> population;
    std::function<double(const std::vector<double>&)> function;

    std::vector<std::vector<double>> plot_values;
    double best;

public:
    Population(const std::function<double(const std::vector<double>&)>&, int, int, double, double, double, double, double);

    double nbits(double, int&);
    void generatePopulation();
    void makeGenerations(int);

    void decodePopulation();
    void evaluatePopulation();
    void roulette();
    void cross();
    void mutate();

    double getBest();
    double getAverage();

    void outputPlotValues();
};


#endif //GENETIC_ALGORITHM_POPULATION_H
