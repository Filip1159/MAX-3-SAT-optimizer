#pragma once
#include <vector>
#include <ctime>
#include <string>
#include <random>

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
    void mutation(double probability);
    double fitness(Max3SatProblem* problem);
    bool getSingleGene(int number);
    string toString();
};