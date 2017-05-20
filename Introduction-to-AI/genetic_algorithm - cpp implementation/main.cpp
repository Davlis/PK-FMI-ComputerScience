//
// Created by Kamil Kosiński on 09/05/2017.
//

#include <iostream>
#include <cmath>
#include <vector>
#include "Population.h"

double function(const std::vector<double>& x){
    double x1 = x[0];
    double x2 = x[1];
    return -1.25 * (-20 * pow(M_E, (-0.2 * sqrt((x1*x1 + x2*x2) / 2))) -  pow(M_E, ((cos(2 * M_PI * x1) + cos(2 * M_PI * x2)) / 2)) + M_E + 25.7);
}

int main() {
    Population pop(function, 100, 2, 0.7, 0.02, -1.5, 1.5, 0.00000001);
    pop.makeGenerations(1000);
    pop.outputPlotValues();
    return 0;
}