//
// Created by Kamil Kosiński on 09/05/2017.
//

#include <cstdlib>
#include "Specimen.h"

Specimen::Specimen(const std::vector<short>& val, int vars, int bits){
    amountOfVariables = vars;
    amountOfBits = bits;
    values = val;
    size = amountOfBits*amountOfVariables;
}

std::vector<short> Specimen::getValues() {
    return values;
}

std::vector<double> Specimen::getArgs() {
    return decodedValues;
}

double Specimen::getEvaluatedValue() {
    return evaluatedValue;
}

void Specimen::setValues(const std::vector<short>& args) {
    values = args;
}

void Specimen::setArgs(const std::vector<double>& args){
    decodedValues = args;
}

void Specimen::setEvaluatedValue(double result) {
    evaluatedValue = result;
}

void Specimen::cross(Specimen& s) {
    int amountOfCrossingPoints = (size / 10) + 1;
    std::vector<int> crossingPoints;
    for(int i = 0; i < amountOfCrossingPoints; ++i)
        crossingPoints.push_back((rand()%(size-1))+1);

    std::vector<short> current, another;

    for(int i = 0; i < size; i++){
        for(int crossingPoint: crossingPoints){
            if(i == crossingPoint)
                current.swap(another);
        }
        current.push_back(values[i]);
        another.push_back(s.values[i]);
    }

    values.swap(current);
    s.values.swap(another);
}

void Specimen::mutate() {
    int mutationPoint = rand()%size;

    values[mutationPoint] += 1;
    values[mutationPoint] %= 2;
}