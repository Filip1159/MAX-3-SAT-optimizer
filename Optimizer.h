#pragma once
#include <vector>
#include "Individual.h"
#include "Max3SatProblem.h"
#include "Random.h"

#define OPTIMIZER_OK 0
#define OPTIMIZER_ERROR_ILLEGAL_VALUE -1
#define OPTIMIZER_ERROR_POPULATION_EMPTY -2
#define OPTIMIZER_INIT_ERROR -2

#define OPTIMIZER_MIN_POPULATION_SIZE 10
#define OPTIMIZER_MIN_TOURNAMENT_SIZE 2
#define OPTIMIZER_DEF_POPULATION_SIZE 50
#define OPTIMIZER_DEF_CROSSOVER_PROBABILITY .5
#define OPTIMIZER_DEF_MUTATION_PROBABILITY .005
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
    Individual* bestIndividual;

    Individual* selectParent();
    int findBestIndividual();

public:
    Optimizer();
    ~Optimizer();

    void setFilename(const string &filename);
    int initialize();
    void runIteration();

    Max3SatProblem* getProblem() const;  // NOLINT
    void setProblem(Max3SatProblem* newProblem);
    vector<Individual*>* getPopulation() const;  // NOLINT
    Individual* getBestIndividual() const;

    int getPopulationSize() const;  // NOLINT
    int setPopulationSize(int newSize);
    double getCrossoverProbability() const;  // NOLINT
    int setCrossoverProbability(double newProbability);
    double getMutationProbability() const;  // NOLINT
    int setMutationProbability(double newProbability);
    int getTournamentSize() const;  // NOLINT
    int setTournamentSize(int newSize);
};