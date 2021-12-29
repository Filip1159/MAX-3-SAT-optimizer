#include <iostream>
#include <random>
#include "Optimizer.h"

int main() {
    Optimizer optimizer;
    optimizer.setPopulationSize(10);
    optimizer.setGenotypeSize(50);
    optimizer.setCrossoverProbability(0.3);
    optimizer.setMutationProbability(0.2);
    optimizer.initialize();
    Max3SatProblem* problem = optimizer.getProblem();

    vector<Individual*>* population = optimizer.getPopulation();

    double maxFit = 0;
    for (auto & i : *population) {
        cout << i->toString() << '\n';
        double fitness = problem->compute(i);
        if (fitness > maxFit) maxFit = fitness;
    }
    cout << "maxFit = " << maxFit << '\n';

    optimizer.runIteration();
    population = optimizer.getPopulation();

    maxFit = 0;
    for (int i=0; i<population->size(); i++) {
        cout << population->at(i)->toString() << '\n';
        double fitness = problem->compute(population->at(0));
        if (fitness > maxFit) maxFit = fitness;
    }
    cout << "maxFit = " << maxFit << '\n';

    return 0;
}