#include <iostream>
#include <random>
#include "Optimizer.h"

const int POPULATION_SIZE = 50;
const double CROSSOVER_PROBABILITY = .5;
const double MUTATION_PROBABILITY = .01;
const string FILENAME = R"(C:\Users\PAVILION\CLionProjects\TEPmax3sat\clauses\350\m3s_350_0.txt)"; // NOLINT

int main() {
    Optimizer optimizer;
    optimizer.setPopulationSize(POPULATION_SIZE);
    optimizer.setCrossoverProbability(CROSSOVER_PROBABILITY);
    optimizer.setMutationProbability(MUTATION_PROBABILITY);
    optimizer.setFilename(FILENAME);
    optimizer.initialize();
    Max3SatProblem* problem = optimizer.getProblem();
    vector<Individual*>* population = optimizer.getPopulation();

    double maxFit = 0;
    for (auto & i : *population) {
        double fitness = problem->compute(i);
        if (fitness > maxFit) maxFit = fitness;
    }
    cout << "maxFit= " << maxFit << '\n';

    double maxMaxFit = 0;
    for (int repeats=0; repeats<200; repeats++) {
        optimizer.runIteration();
        population = optimizer.getPopulation();

        maxFit = optimizer.maxFit(population);
        if (maxFit > maxMaxFit) maxMaxFit = maxFit;
        cout << "maxFit = " << maxFit << '\n';
    }
    cout << "__END__ = " << maxMaxFit;
    return 0;
}