#include <iostream>
#include <random>
#include "Optimizer.h"

#define FILENAME R"(C:\Users\PAVILION\CLionProjects\TEPmax3sat\clauses\350\m3s_350_0.txt)"

int main() {
    Optimizer optimizer;  // constructor with default parameter values
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