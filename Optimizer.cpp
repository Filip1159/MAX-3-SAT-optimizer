#include "Optimizer.h"
#include <iostream>

using namespace std;

Optimizer::Optimizer() {
    population = new vector<Individual*>();
    problem = new Max3SatProblem();
    populationSize = 0;
    crossoverProbability = 0;
    mutationProbability = 0;
}

Optimizer::~Optimizer() {
    cout << "dest1\n";
    delete problem;
    for (auto & i : *population) {
        cout << "dest2\n";
        delete i;
    }
    cout << "dest3\n";
    delete population;
}


void Optimizer::setPopulationSize(int newPopulationSize) {
    populationSize = newPopulationSize;
}

int Optimizer::getPopulationSize() const {
    return populationSize;
}

void Optimizer::setCrossoverProbability(double newCrossoverProbability) {
    crossoverProbability = newCrossoverProbability;
}

double Optimizer::getCrossoverProbability() const {
    return crossoverProbability;
}

void Optimizer::setMutationProbability(double newMutationProbability) {
    mutationProbability = newMutationProbability;
}

double Optimizer::getMutationProbability() const {
    return mutationProbability;
}

void Optimizer::setGenotypeSize(int newGenotypeSize) {
    genotypeSize = newGenotypeSize;
}

int Optimizer::getGenotypeSize() const {
    return genotypeSize;
}

void Optimizer::initialize() {
    for (int i=0; i<populationSize; i++) {
        population->push_back(new Individual(genotypeSize));
    }
    problem->setFilename(R"(C:\Users\PAVILION\CLionProjects\TEPmax3sat\clauses\50\m3s_50_0.txt)");
    problem->load();
}

void Optimizer::runIteration() {
    auto* newPopulation = new vector<Individual*>();
    while (newPopulation->size() < populationSize) {
        Individual* firstParent = selectParent();
        Individual* secondParent = selectParent();
        if ((double)(rand() % 100) / 100 < crossoverProbability) {
            Individual** children = firstParent->crossover(secondParent);
            auto* firstChild = children[0];
            auto* secondChild = children[1];
            firstChild->mutation(mutationProbability);
            secondChild->mutation(mutationProbability);
            newPopulation->push_back(firstChild);
            newPopulation->push_back(secondChild);
            delete children;
        } else {
            firstParent->mutation(mutationProbability);
            secondParent->mutation(mutationProbability);
            newPopulation->push_back(new Individual(*firstParent));
            newPopulation->push_back(new Individual(*secondParent));
        }
    }
    for (auto & i : *population) {
        delete i;
    }
    delete population;
    population = newPopulation;
}

Individual* Optimizer::selectParent() {
    Individual* firstIndividual = population->at(rand() % populationSize);
    Individual* secondIndividual = population->at(rand() % populationSize);
    if (firstIndividual->fitness(problem) > secondIndividual->fitness(problem)) {
        return firstIndividual;
    } else {
        return secondIndividual;
    }
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

