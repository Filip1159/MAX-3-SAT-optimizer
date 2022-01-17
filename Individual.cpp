#include "Individual.h"
#include "Max3SatProblem.h"

Individual::Individual() {
    genotype = new vector<bool>();
    isFitnessUpToDate = false;
    savedFitness = 0;
}

Individual::Individual(int genotypeSize) {
    genotype = new vector<bool>();
    isFitnessUpToDate = false;
    savedFitness = 0;
    for (int i=0; i<genotypeSize; i++)
        genotype->push_back(Random::getBool());
}

Individual::Individual(vector<bool> *newGenotype) {
    genotype = newGenotype;
    isFitnessUpToDate = false;
    savedFitness = 0;
}

Individual::Individual(const Individual& other) {
    genotype = new vector<bool>();
    isFitnessUpToDate = other.isFitnessUpToDate;
    savedFitness = other.savedFitness;
    for (auto && i : *other.genotype)
        genotype->push_back(i);
}

Individual::~Individual() {
    delete genotype;
}

Individual** Individual::crossover(Individual* other) {
    auto** newGenotypes = new vector<bool>*[2];
    newGenotypes[0] = new vector<bool>();
    newGenotypes[1] = new vector<bool>();
    for (int i=0; i<genotype->size(); i++) {
        bool gene = (Random::getBool() ? genotype : other->genotype)->at(i);  // NOLINT
        newGenotypes[0]->push_back(gene);
        newGenotypes[1]->push_back(!gene);
    }
    auto** children = new Individual*[2];
    children[0] = new Individual(newGenotypes[0]);
    children[1] = new Individual(newGenotypes[1]);
    delete newGenotypes;
    return children;
}

int Individual::mutation(double probability) {
    if (genotype->empty()) return INDIVIDUAL_EMPTY_GENOTYPE;
    for (auto && i : *genotype) {
        float r = Random::getFloat();  // NOLINT
        if (r < probability) i.flip();
    }
    isFitnessUpToDate = false;
    savedFitness = 0;
    return INDIVIDUAL_OK;
}

double Individual::fitness(Max3SatProblem* problem) {
    if (!isFitnessUpToDate) {
        isFitnessUpToDate = true;
        savedFitness = problem->compute(this);
    }
    return savedFitness;
}

int Individual::getSingleGene(int number) {
    if (number > genotype->size()) return INDIVIDUAL_BAD_GENE_NUMBER;
    return genotype->at(number);
}

void Individual::print() {
    for (auto && i : *genotype)
        cout << (i ? '1' : '0');
}
