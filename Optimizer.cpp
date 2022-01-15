#include "Optimizer.h"
#include <iostream>

using namespace std;

Optimizer::Optimizer() {
    population = new vector<Individual*>();
    problem = new Max3SatProblem();
    populationSize = 0;
    crossoverProbability = 0;
    mutationProbability = 0;
    genotypeSize = 0;
    crypto_random_generator = new random_device();
    doubleDistro = new uniform_real_distribution<double>(0, 1);
}

Optimizer::~Optimizer() {
    delete problem;
    for (auto & i : *population) delete i;
    delete population;
}

int Optimizer::setPopulationSize(int newSize) {
    if (newSize < 0) return OPTIMIZER_ERROR_ILLEGAL_VALUE;
    populationSize = newSize;
    return OPTIMIZER_OK;
}

int Optimizer::getPopulationSize() const {
    return populationSize;
}

int Optimizer::setCrossoverProbability(double newProbability) {
    if (newProbability < 0) return OPTIMIZER_ERROR_ILLEGAL_VALUE;
    crossoverProbability = newProbability;
    return OPTIMIZER_OK;
}

double Optimizer::getCrossoverProbability() const {
    return crossoverProbability;
}

int Optimizer::setMutationProbability(double newProbability) {
    if (newProbability < 0 || newProbability > 1) return OPTIMIZER_ERROR_ILLEGAL_VALUE;
    mutationProbability = newProbability;
    return OPTIMIZER_OK;
}

double Optimizer::getMutationProbability() const {
    return mutationProbability;
}

int Optimizer::setGenotypeSize(int newSize) {
    if (newSize < 0) return OPTIMIZER_ERROR_ILLEGAL_VALUE;
    genotypeSize = newSize;
    return OPTIMIZER_OK;
}

int Optimizer::getGenotypeSize() const {
    return genotypeSize;
}

void Optimizer::initialize() {
    problem->loadClausesFromFile();
    genotypeSize = problem->calculateGenotypeSize();
    for (int i=0; i<populationSize; i++)
        population->push_back(new Individual(genotypeSize));
}

void Optimizer::runIteration() {
    auto* newPopulation = new vector<Individual*>();
    while (newPopulation->size() < populationSize) {
        Individual* firstParent = selectParent();
        Individual* secondParent = selectParent();
        if ((*doubleDistro)(*crypto_random_generator) < crossoverProbability) {
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
//    double oldFit = maxFit(population);
//    double newFit = maxFit(newPopulation);
//    cout << "oldFit = " << oldFit << " newFit = " << newFit << '\n';
//    if (newFit > oldFit) {
        //cout << "replacing\n";
        for (auto & i : *population) {
            delete i;
        }
        delete population;
        population = newPopulation;
//    } else {
//        //cout << "no action\n";
//        for (auto & i : *newPopulation) {
//            delete i;
//        }
//        delete newPopulation;
//    }
}

#define TOURNAMENT_SIZE 15
Individual* Optimizer::selectParent() {
    auto** individuals = new Individual*[TOURNAMENT_SIZE];
    for (int i=0; i<TOURNAMENT_SIZE; i++) {
        individuals[i] = population->at((*doubleDistro)(*crypto_random_generator) * populationSize);
    }
    double bestFit = 0;
    int winnerIndex;
    for (int i=0; i<TOURNAMENT_SIZE; i++) {
        double fitness = individuals[i]->fitness(problem);
        if (fitness > bestFit) {
            bestFit = fitness;
            winnerIndex = i;
        }
    }
    Individual* toReturn = individuals[winnerIndex];
    delete individuals;
    return toReturn;
}

void Optimizer::setProblem(Max3SatProblem *newProblem) {
    delete problem;
    problem = newProblem;
}

Max3SatProblem* Optimizer::getProblem() const {
    return problem;
}

vector<Individual*>* Optimizer::getPopulation() const {
    return population;
}

double Optimizer::maxFit(vector<Individual*>* individuals) {
    double max = 0;
    for (auto & individual : *individuals) {
        double fit = problem->compute(individual);
        if (fit > max) max = fit;
    }
    return max;
}

void Optimizer::setFilename(const string &filename) {
    problem->setFilename(filename);
}
