#include "Max3SatProblem.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define PARENTHESES_OFFSET 2
#define VARIABLES_IN_CLAUSE 3

Max3SatProblem::Max3SatProblem() {
    clauses = new vector<Clause*>;
    genotypeSize = 0;
}

Max3SatProblem::~Max3SatProblem() {
    for (auto & clause : *clauses) delete clause;
    delete clauses;
}

void Max3SatProblem::setFilename(const string &newFilename) {
    filename = newFilename;
}

int Max3SatProblem::loadClausesFromFile() {
    ifstream stream(filename);
    string line;
    while (getline(stream, line)) {
        auto* clause = new Clause();
        if (clause->loadFromString(line) != MAX3SAT_OK) {
            stream.close();
            return MAX3SAT_BAD_STRING_FORMAT;
        }
        clauses->push_back(clause);
    }
    stream.close();
    if (clauses->empty()) return MAX3SAT_BAD_FILENAME;
    return MAX3SAT_OK;
}

int Max3SatProblem::calculateGenotypeSize() {
    if (clauses->empty()) return MAX3SAT_CLAUSES_EMPTY;
    int maxVariableNumber = 0;
    for (auto & clause : *clauses) {
        ClauseVariable* vars = clause->getVariables();
        for (int j=0; j<VARIABLES_IN_CLAUSE; j++) {
            if (vars[j].getNumber() > maxVariableNumber) maxVariableNumber = vars[j].getNumber();
        }
    }
    genotypeSize = maxVariableNumber + 1;  // we count from 0
    return genotypeSize;
}

double Max3SatProblem::compute(Individual* individual) {
    if (clauses->empty()) return MAX3SAT_CLAUSES_EMPTY;
    int satisfied = 0;
    for (auto clause : *clauses) {
        ClauseVariable* vars = clause->getVariables();
        bool gene0 = individual->getSingleGene(vars[0].getNumber());
        bool gene1 = individual->getSingleGene(vars[1].getNumber());
        bool gene2 = individual->getSingleGene(vars[2].getNumber());
        if (clause->isSatisfied(gene0, gene1, gene2)) satisfied++;
    }
    return (double)satisfied/clauses->size();  // NOLINT
}

int ClauseVariable::getNumber() const {
    return number;
}

bool ClauseVariable::isNegated() const {
    return negated;
}

void ClauseVariable::setNegated(bool n) {
    negated = n;
}

int ClauseVariable::setNumber(int n) {
    if (n < 0) return MAX3SAT_ERROR_ILLEGAL_VALUE;
    number = n;
    return MAX3SAT_OK;
}

int ClauseVariable::loadFromString(string &str) {
    setNegated(str.starts_with('-'));
    if (isNegated()) str.erase(0, 1);
    int num;
    try { num = stoi(str); }
    catch (...) { return MAX3SAT_BAD_STRING_FORMAT; }
    setNumber(num);
    return MAX3SAT_OK;
}

void ClauseVariable::print() const {
    cout << (isNegated() ? "-" : "") << getNumber();
}

bool ClauseVariable::isSatisfied(bool var) const {
    return var == !isNegated();
}

Clause::~Clause() {
    delete variables;
}

int Clause::loadFromString(string &str) {
    str = str.substr(PARENTHESES_OFFSET, str.length() - 2*PARENTHESES_OFFSET);
    string variableCode;
    variables = new ClauseVariable[3];
    stringstream ss(str);
    for (int i=0; i<VARIABLES_IN_CLAUSE; i++) {
        ss >> variableCode;
        if (variables[i].loadFromString(variableCode) != MAX3SAT_OK)
            return MAX3SAT_BAD_STRING_FORMAT;
    }
    return MAX3SAT_OK;
}

void Clause::print() const {
    cout << "[";
    variables[0].print();
    cout << " ";
    variables[1].print();
    cout << " ";
    variables[2].print();
    cout << "]";
}

bool Clause::isSatisfied(bool var0, bool var1, bool var2) {
    return variables[0].isSatisfied(var0) || variables[1].isSatisfied(var1) || variables[2].isSatisfied(var2);
}

ClauseVariable *Clause::getVariables() {
    return variables;
}