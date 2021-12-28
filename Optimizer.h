#pragma once
#include <vector>
#include "Individual.h"
#include "Max3SatProblem.h"
#include "SmartPointer.h"

using namespace std;

class Optimizer {
private:
    int populationSize;
    double crossoverProbability;
    double mutationProbability;
    int genotypeSize;
    vector<SmartPointer<Individual>*>* population;
    Max3SatProblem* problem;

public:
    Optimizer();
    ~Optimizer();
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
    SmartPointer<Individual>* selectParent();
};
