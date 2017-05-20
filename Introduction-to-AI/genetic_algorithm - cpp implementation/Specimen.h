//
// Created by Kamil Kosiński on 09/05/2017.
//

#ifndef GENETIC_ALGORITHM_SPECIMEN_H
#define GENETIC_ALGORITHM_SPECIMEN_H

#include <vector>
#include <cstdlib>

class Specimen {
    std::vector<short> values;
    std::vector<double> decodedValues;
    double evaluatedValue;

    int amountOfVariables;
    int amountOfBits;
    int size;

public:
    Specimen(const std::vector<short>&, int, int);

    std::vector<short> getValues();
    std::vector<double> getArgs();
    double getEvaluatedValue();

    void setValues(const std::vector<short>&);
    void setArgs(const std::vector<double>&);
    void setEvaluatedValue(double);

    void cross(Specimen&);
    void mutate();
};


#endif //GENETIC_ALGORITHM_SPECIMEN_H
