#pragma once
#include <vector>
#include <ctime>
#include <string>
#include <random>
#include <iostream>

#define INDIVIDUAL_OK 0
#define INDIVIDUAL_BAD_GENE_NUMBER -1
#define INDIVIDUAL_EMPTY_GENOTYPE -2

class Max3SatProblem;

using namespace std;

class Individual {
private:
    vector<bool>* genotype;

public:
    Individual();
    ~Individual();
    explicit Individual(int genotypeSize);
    explicit Individual(vector<bool> *newGenotype);
    Individual(const Individual& other);
    Individual** crossover(Individual* other);
    int mutation(double probability);
    double fitness(Max3SatProblem* problem);
    int getSingleGene(int number);
    void print();
};