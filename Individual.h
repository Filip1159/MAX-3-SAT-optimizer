#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Random.h"

#define INDIVIDUAL_OK 0
#define INDIVIDUAL_BAD_GENE_NUMBER -1
#define INDIVIDUAL_EMPTY_GENOTYPE -2

class Max3SatProblem;

using namespace std;

class Individual {
private:
    vector<bool>* genotype;
    bool isFitnessUpToDate;
    double savedFitness;

public:
    Individual();
    explicit Individual(int genotypeSize);
    explicit Individual(vector<bool> *newGenotype);
    Individual(const Individual& other);
    ~Individual();
    Individual** crossover(Individual* other);
    int mutation(double probability);
    double fitness(Max3SatProblem* problem);
    int getSingleGene(int number);
    void print();
};