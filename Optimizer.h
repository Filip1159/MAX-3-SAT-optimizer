#pragma once
#include <vector>
#include "Individual.h"
#include "Max3SatProblem.h"
#include "Random.h"

#define OPTIMIZER_OK 0
#define OPTIMIZER_ERROR_ILLEGAL_VALUE -1

#define OPTIMIZER_MIN_POPULATION_SIZE 10
#define OPTIMIZER_MIN_TOURNAMENT_SIZE 2
#define OPTIMIZER_DEF_POPULATION_SIZE 50
#define OPTIMIZER_DEF_CROSSOVER_PROBABILITY .5
#define OPTIMIZER_DEF_MUTATION_PROBABILITY .01
#define OPTIMIZER_DEF_TOURNAMENT_SIZE 15

using namespace std;

class Optimizer {
private:
    int populationSize;
    double crossoverProbability;
    double mutationProbability;
    int genotypeSize;
    int tournamentSize;
    vector<Individual*>* population;
    Max3SatProblem* problem;

public:
    Optimizer();
    ~Optimizer();
    void setProblem(Max3SatProblem* newProblem);
    Max3SatProblem* getProblem() const;  // NOLINT
    vector<Individual*>* getPopulation() const;  // NOLINT
    int setPopulationSize(int newSize);
    int getPopulationSize() const;  // NOLINT
    int setCrossoverProbability(double newProbability);
    double getCrossoverProbability() const;  // NOLINT
    int setMutationProbability(double newProbability);
    double getMutationProbability() const;  // NOLINT
    int setTournamentSize(int newSize);
    int getTournamentSize() const;  // NOLINT

    void setFilename(const string &filename);
    void initialize();
    void runIteration();
    Individual* selectParent();

    double maxFit(vector<Individual*>* population);
};