#include "Optimizer.h"

#include <iostream>

using namespace std;

Optimizer::Optimizer() {
    population = new vector<Individual*>();
    problem = new Max3SatProblem();
    populationSize = OPTIMIZER_DEF_POPULATION_SIZE;
    crossoverProbability = OPTIMIZER_DEF_CROSSOVER_PROBABILITY;
    mutationProbability = OPTIMIZER_DEF_MUTATION_PROBABILITY;
    genotypeSize = 0;
    tournamentSize = OPTIMIZER_DEF_TOURNAMENT_SIZE;
    bestIndividual = nullptr;
}

Optimizer::~Optimizer() {
    delete problem;
    for (auto & i : *population) delete i;
    delete population;
    delete bestIndividual;
}

void Optimizer::initialize() {
    problem->loadClausesFromFile();
    genotypeSize = problem->calculateGenotypeSize();
    for (int i=0; i<populationSize; i++)
        population->push_back(new Individual(genotypeSize));
    findBestIndividual();
}

void Optimizer::runIteration() {
    auto* newPopulation = new vector<Individual*>();
    while (newPopulation->size() < populationSize) {
        Individual* firstParent = selectParent();
        Individual* secondParent = selectParent();
        if (Random::getFloat() < crossoverProbability) {
            Individual** children = firstParent->crossover(secondParent);
            auto* firstChild = children[0];
            auto* secondChild = children[1];
            firstChild->mutation(mutationProbability);
            secondChild->mutation(mutationProbability);
            newPopulation->push_back(firstChild);
            newPopulation->push_back(secondChild);
            delete children;
        } else {
            auto firstChild = new Individual(*firstParent);
            auto secondChild = new Individual(*secondParent);
            firstChild->mutation(mutationProbability);
            secondChild->mutation(mutationProbability);
            newPopulation->push_back(firstChild);
            newPopulation->push_back(secondChild);
        }
    }
    for (auto & i : *population) delete i;
    delete population;
    population = newPopulation;
    findBestIndividual();
}

Individual* Optimizer::selectParent() {
    double bestFit = 0;
    Individual* winner;
    for (int i=0; i<tournamentSize; i++) {
        Individual* selected = population->at(Random::getFloat() * populationSize);  // NOLINT
        double fitness = selected->fitness(problem);
        if (fitness > bestFit) {
            bestFit = fitness;
            winner = selected;
        }
    }
    return winner;
}

void Optimizer::findBestIndividual() {
    double maxFit = 0;
    Individual* currentBest;
    for (auto & individual : *population) {
        double fit = individual->fitness(problem);
        if (fit > maxFit) {
            maxFit = fit;
            currentBest = individual;
        }
    }
    if (bestIndividual == nullptr || maxFit > bestIndividual->fitness(problem)) {
        if (bestIndividual != nullptr) delete bestIndividual;  // NOLINT
        bestIndividual = new Individual(*currentBest);
    }
}

Individual* Optimizer::getBestIndividual() const {
    return bestIndividual;
}

void Optimizer::setFilename(const string &filename) {
    problem->setFilename(filename);
}

int Optimizer::getPopulationSize() const {
    return populationSize;
}

int Optimizer::setPopulationSize(int newSize) {
    if (newSize < OPTIMIZER_MIN_POPULATION_SIZE) return OPTIMIZER_ERROR_ILLEGAL_VALUE;
    populationSize = newSize;
    return OPTIMIZER_OK;
}

double Optimizer::getCrossoverProbability() const {
    return crossoverProbability;
}

int Optimizer::setCrossoverProbability(double newProbability) {
    if (newProbability < 0) return OPTIMIZER_ERROR_ILLEGAL_VALUE;
    crossoverProbability = newProbability;
    return OPTIMIZER_OK;
}

double Optimizer::getMutationProbability() const {
    return mutationProbability;
}

int Optimizer::setMutationProbability(double newProbability) {
    if (newProbability < 0 || newProbability > 1) return OPTIMIZER_ERROR_ILLEGAL_VALUE;
    mutationProbability = newProbability;
    return OPTIMIZER_OK;
}


int Optimizer::getTournamentSize() const {
    return tournamentSize;
}

int Optimizer::setTournamentSize(int newSize) {
    if (newSize < OPTIMIZER_MIN_TOURNAMENT_SIZE || newSize > populationSize) return OPTIMIZER_ERROR_ILLEGAL_VALUE;
    tournamentSize = newSize;
    return OPTIMIZER_OK;
}

Max3SatProblem* Optimizer::getProblem() const {
    return problem;
}

void Optimizer::setProblem(Max3SatProblem *newProblem) {
    delete problem;
    problem = newProblem;
}

vector<Individual*>* Optimizer::getPopulation() const {
    return population;
}