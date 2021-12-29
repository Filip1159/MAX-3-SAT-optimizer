#pragma once
#include <vector>
#include "Individual.h"
#include "Max3SatProblem.h"

using namespace std;

class Optimizer {
private:
    int populationSize;
    double crossoverProbability;
    double mutationProbability;
    int genotypeSize;
    vector<Individual*>* population;
    Max3SatProblem* problem;

public:
    Optimizer();
    ~Optimizer();
    void setProblem(Max3SatProblem* newProblem);
    [[nodiscard]] Max3SatProblem* getProblem() const;
    [[nodiscard]] vector<Individual*>* getPopulation() const;
    void setPopulationSize(int newPopulationSize);
    [[nodiscard]] int getPopulationSize() const;
    void setCrossoverProbability(double newCrossoverProbability);
    [[nodiscard]] double getCrossoverProbability() const;
    void setMutationProbability(double newMutationProbability);
    [[nodiscard]] double getMutationProbability() const;
    void setGenotypeSize(int newGenotypeSize);
    [[nodiscard]] int getGenotypeSize() const;

    void initialize();
    void runIteration();
    Individual* selectParent();
};
