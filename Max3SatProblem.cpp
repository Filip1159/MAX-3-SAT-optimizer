#include "Max3SatProblem.h"
#include <fstream>
#include <sstream>
#include <iostream>

Max3SatProblem::Max3SatProblem() {
    clauses = new vector<Clause*>;
}

Max3SatProblem::~Max3SatProblem() {
    for (auto & clause : *clauses) {
        delete clause;
    }
    delete clauses;
}

void Max3SatProblem::setFilename(const string &newFilename) {
    filename = newFilename;
}

void Max3SatProblem::load() {
    ifstream stream(filename);
    string line;
    while (getline(stream, line)) {
        auto* clause = new Clause();
        clause->loadFromString(line);
        clauses->push_back(clause);
        cout << clause->toString() << '\n';
    }
    stream.close();
}

double Max3SatProblem::compute(Individual* individual) {
    int satisfied = 0;
    for (auto clause : *clauses) {
        ClauseVariable* vars = clause->getVariables();
        bool gene0 = individual->getSingleGene(vars[0].getNumber());
        bool gene1 = individual->getSingleGene(vars[1].getNumber());
        bool gene2 = individual->getSingleGene(vars[2].getNumber());
        if (clause->isSatisfied(gene0, gene1, gene2)) satisfied++;
    }
    return (double)satisfied/clauses->size();
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

void ClauseVariable::setNumber(int n) {
    number = n;
}

void ClauseVariable::loadFromString(string str) {
    setNegated(str.starts_with('-'));
    if (isNegated()) str.erase(0, 1);
    setNumber(stoi(str));
}

string ClauseVariable::toString() const {
    return (isNegated() ? "-" : "") + to_string(getNumber());
}

bool ClauseVariable::isSatisfied(bool var) const {
    return var == !isNegated();
}

void Clause::loadFromString(string str) {
    str = str.substr(2, str.length()-4);
    string variableCode;
    variables = new ClauseVariable[3];
    stringstream ss(str);
    for (int i=0; i<3; i++) {
        ss >> variableCode;
        variables[i].loadFromString(variableCode);
    }
}

string Clause::toString() {
    return "[" + variables[0].toString() + " " + variables[1].toString() + " " + variables[2].toString() + "]";
}

bool Clause::isSatisfied(bool var0, bool var1, bool var2) {
    return variables[0].isSatisfied(var0) && variables[1].isSatisfied(var1) && variables[2].isSatisfied(var2);
}

ClauseVariable *Clause::getVariables() {
    return variables;
}
