//
// Created by Kamil Kosiński on 09/05/2017.
//

#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "Population.h"
#include "RandomGen.h"

Population::Population(const std::function<double(const std::vector<double>&)>& func, int popsize, int vars, double pk, double pm, double a, double b, double dx_tmp) {
    srand((unsigned) time(NULL));

    function = func;
    size = popsize;
    amountOfVariables = vars;
    probabilityOfCross = pk;
    probabilityOfMutation = pm;
    startOfRange = a;
    endOfRange = b;

    dx = nbits(dx_tmp, amountOfBits);
    generatePopulation();
    decodePopulation();
    evaluatePopulation();

    best = getBest();
    std::vector<double> first;
    first.push_back(best);
    first.push_back(best);
    first.push_back(getAverage());
    plot_values.push_back(first);
}

void Population::makeGenerations(int amountOfIterations) {
    double currentBest;
    for(int i = 0; i < amountOfIterations; ++i) {
        roulette();
        cross();
        mutate();
        decodePopulation();
        evaluatePopulation();

        currentBest = getBest();
        if(currentBest > best) best = currentBest;

        std::vector<double> generation;
        generation.push_back(best);
        generation.push_back(currentBest);
        generation.push_back(getAverage());
        plot_values.push_back(generation);
    }
}

double Population::nbits(double dx, int& bits) {
    double amountOfValues = (endOfRange - startOfRange) / dx + 1;
    for(bits = 0; amountOfValues > 1; ++bits) amountOfValues /= 2;
    return ((endOfRange - startOfRange) / (pow(2, bits) - 1));
}

void Population::generatePopulation() {
    for(int i = 0; i < size; i++){
        std::vector<short> values;
        for(int j = 0 ; j < amountOfBits * amountOfVariables; j++)
            values.push_back((short) (rand()%2));
        population.push_back(Specimen(values, amountOfVariables, amountOfBits));
    }
}

void Population::decodePopulation() {
    for(Specimen& s: population){
        std::vector<short> input(s.getValues());
        std::vector<double> output;
        for(int i = 0; i < amountOfVariables; i++){
            int value = 0;
            int pos = i * amountOfBits;
            for(int power = amountOfBits-1; power >= 0; --power){
                value += input[pos] * pow(2, power);
                ++pos;
            }
            output.push_back((startOfRange + (value * dx)));
        }
        s.setArgs(output);
    }
}

void Population::evaluatePopulation() {
    for(Specimen& s: population)
        s.setEvaluatedValue(function(s.getArgs()));
}

void Population::roulette() {
    std::vector<Specimen> values;

    for(Specimen s: population){
        bool wasFound = false;
        for(Specimen& i: values){
            if(s.getEvaluatedValue() == i.getEvaluatedValue()){
                wasFound = true;
                break;
            }
        }
        if(!wasFound)
            values.push_back(s);
    }

    double minimumValue = INFINITY;
    double smallestValue = INFINITY;

    for(Specimen& i: values){
        double temp = i.getEvaluatedValue();
        if(temp < minimumValue)
            minimumValue = temp;
    }

    for(Specimen& i: values){
        double temp = i.getEvaluatedValue();
        if(temp > minimumValue && temp < smallestValue)
            smallestValue = temp;
    }

    double difference = smallestValue - (minimumValue * 2);
    for(Specimen& i: values)
        i.setEvaluatedValue(i.getEvaluatedValue() + difference);

    double sum = 0;
    for(Specimen& i: values)
        sum += i.getEvaluatedValue();

    std::vector<double> probabilities;
    for(Specimen& i: values)
        probabilities.push_back(i.getEvaluatedValue()/sum);

    population.clear();
    double currentRouletteSpin = 0;
    for(int i = 0; i < size; ++i){
        if((currentRouletteSpin += RGen::next()) >= 1)
            currentRouletteSpin -= currentRouletteSpin/1;
        double temp = currentRouletteSpin;
        bool inRange = false;
        for(int j = 0; j < probabilities.size(); ++j){
            temp -= probabilities[j];
            if(temp<=0){
                population.push_back(values[j]);
                inRange = true;
                break;
            }
        }
        if(!inRange){
            population.push_back(values[values.size()-1]);
        }
    }
}

void Population::cross() {
    std::vector<int> cross;
    std::vector<int> values;
    for(int i = 0; i < size; ++i)
        values.push_back(i);

    for(int i = 0; i < size; ++i){
        long int choice = rand()%values.size();

        if(probabilityOfCross >= RGen::next()){
            cross.push_back(values[choice]);
            if(cross.size() == 2){
                population[cross[0]].cross(population[cross[1]]);
                cross.clear();
            }
        }
        values.erase(values.begin()+choice);
    }
}

void Population::mutate() {
    for(Specimen& s: population)
        if(probabilityOfMutation >= RGen::next())
            s.mutate();
}

double Population::getBest() {
    double best = population[0].getEvaluatedValue();
    for(Specimen& s: population)
        if(best < s.getEvaluatedValue())
            best = s.getEvaluatedValue();
    return best;
}

double Population::getAverage() {
    double sum = 0;
    for(Specimen& s: population)
        sum += s.getEvaluatedValue();
    return (sum/size);
}

void Population::outputPlotValues() {
    std::fstream out;
    out.open("out", std::ios::out);
    for(const std::vector<double>& plot_value: plot_values){
        out << std::setprecision(20) << plot_value[0] << " " << plot_value[1] << " " << plot_value[2] << std::endl;
    }
    out.close();
}