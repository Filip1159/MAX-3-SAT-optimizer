#include "Optimizer.h"

Optimizer::Optimizer() {
    population = new vector<SmartPointer<Individual>*>();
    problem = new Max3SatProblem();
    populationSize = 0;
    crossoverProbability = 0;
    mutationProbability = 0;
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
        population->push_back(new SmartPointer(new Individual(genotypeSize)));
    }
    problem->setFilename(R"(C:\Users\PAVILION\CLionProjects\TEPmax3sat\clauses\50\m3s_50_0.txt)");
    problem->load();
}

void Optimizer::runIteration() {
    auto* newPopulation = new vector<SmartPointer<Individual>*>();
    for (int i=0; i<populationSize; i++) {
        SmartPointer<Individual>* firstParent = selectParent();
        SmartPointer<Individual>* secondParent = selectParent();
        if ((double)(rand() % 100) / 100 < crossoverProbability) {
            Individual** children = (*firstParent)->crossover(secondParent->getValue());
            auto* firstChild = new SmartPointer(children[0]);
            auto* secondChild = new SmartPointer(children[1]);
            (*firstChild)->mutation(mutationProbability);
            (*secondChild)->mutation(mutationProbability);
            newPopulation->push_back(firstChild);
            newPopulation->push_back(secondChild);
        } else {
            (*firstParent)->mutation(mutationProbability);
            (*secondParent)->mutation(mutationProbability);
            newPopulation->push_back(firstParent);
            newPopulation->push_back(secondParent);
        }
    }
    delete population;  // TODO create smart pointer with ref counter, because you should delete also individuals, but not all, except those in newPopulation
    population = newPopulation;
}

SmartPointer<Individual>* Optimizer::selectParent() {
    SmartPointer<Individual>* firstIndividual = population->at(rand() % populationSize);
    SmartPointer<Individual>* secondIndividual = population->at(rand() % populationSize);
    if ((*firstIndividual)->fitness(problem) > (*secondIndividual)->fitness(problem)) {
        return firstIndividual;
    } else {
        return secondIndividual;
    }
}