#include "Individual.h"
#include "Max3SatProblem.h"
#include <random>

Individual::Individual() {
    genotype = new vector<bool>();
    srand(time(nullptr));  // NOLINT
}

Individual::~Individual() {
    delete genotype;
}

Individual::Individual(int genotypeSize) {
    random_device crypto_random_generator;
    uniform_int_distribution<int> intDistro(0, 1);
    genotype = new vector<bool>();
    srand(time(nullptr));  // NOLINT
    for (int i=0; i<genotypeSize; i++) {
        genotype->push_back(intDistro(crypto_random_generator));
    }
}

Individual::Individual(vector<bool> *newGenotype) {
    genotype = newGenotype;
    srand(time(nullptr));  // NOLINT
}

Individual** Individual::crossover(Individual* other) {
    auto** newGenotypes = new vector<bool>*[2];
    newGenotypes[0] = new vector<bool>();
    newGenotypes[1] = new vector<bool>();
    for (int i=0; i<genotype->size(); i++) {
        bool gene = (rand() % 2 == 0 ? genotype : other->genotype)->at(i);  // NOLINT
        newGenotypes[0]->push_back(gene);
        newGenotypes[1]->push_back(!gene);
    }
    auto** children = new Individual*[2];
    children[0] = new Individual(newGenotypes[0]);
    children[1] = new Individual(newGenotypes[1]);
    delete newGenotypes;
    return children;
}

void Individual::mutation(double probability) {
    for (auto && i : *genotype) {
        double r = (double)(rand() % 100) / 100;  // NOLINT
        if (r < probability) {
            i.flip();
        }
    }
}

double Individual::fitness(Max3SatProblem* problem) {
    return problem->compute(this);
}

bool Individual::getSingleGene(int number) {
    return genotype->at(number);
}

string Individual::toString() {
    string s;
    for (auto && i : *genotype) {
        s += i ? '1' : '0';
    }
    return s;
}

Individual::Individual(const Individual& other) {
    genotype = new vector<bool>();
    for (auto && i : *other.genotype) {
        genotype->push_back(i);
    }
}