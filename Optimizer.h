#pragma once
#include <vector>
#include "Individual.h"
#include "Max3SatProblem.h"

#define OPTIMIZER_OK 0
#define OPTIMIZER_ERROR_ILLEGAL_VALUE -1

using namespace std;

class Optimizer {
private:
    int populationSize;
    double crossoverProbability;
    double mutationProbability;
    int genotypeSize;
    vector<Individual*>* population;
    Max3SatProblem* problem;
    random_device* crypto_random_generator;
    uniform_real_distribution<double>* doubleDistro;

public:
    Optimizer();
    ~Optimizer();
    void setProblem(Max3SatProblem* newProblem);
    Max3SatProblem* getProblem() const;  // NOLINT
    vector<Individual*>* getPopulation() const;  // NOLINT
    int setPopulationSize(int newPopulationSize);
    int getPopulationSize() const;  // NOLINT
    int setCrossoverProbability(double newCrossoverProbability);
    double getCrossoverProbability() const;  // NOLINT
    int setMutationProbability(double newMutationProbability);
    double getMutationProbability() const;  // NOLINT
    int setGenotypeSize(int newGenotypeSize);
    int getGenotypeSize() const;  // NOLINT

    void setFilename(const string &filename);
    void initialize();
    void runIteration();
    Individual* selectParent();

    double maxFit(vector<Individual*>* population);
};