#include <iostream>
#include "Optimizer.h"

int main() {
    Optimizer optimizer;
    optimizer.initialize();
    optimizer.setPopulationSize(10);
    optimizer.setGenotypeSize(50);
    optimizer.setCrossoverProbability(0.3);
    optimizer.setMutationProbability(0.2);

    return 0;
}
