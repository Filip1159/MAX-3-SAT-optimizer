#include <iostream>
#include "Optimizer.h"

#define FILENAME R"(C:\Users\PAVILION\CLionProjects\TEPmax3sat\clauses\350\m3s_350_0.txt)"

int main() {
    Optimizer optimizer;  // constructor with default parameter values
    optimizer.setFilename(FILENAME);
    optimizer.initialize();

    for (int repeats=0; repeats<2000; repeats++)
        optimizer.runIteration();

    cout << optimizer.getBestIndividual()->fitness(optimizer.getProblem()) << '\n';
    int resultLength;
    int* result = optimizer.getBestIndividual()->getResultAsTable(&resultLength);
    for (int i=0; i<resultLength; i++)
        cout << result[i];
    delete result;
    return 0;
}