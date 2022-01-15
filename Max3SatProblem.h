#pragma once
#include <string>
#include <vector>
#include "Individual.h"

#define MAX3SAT_OK 0
#define MAX3SAT_ERROR_ILLEGAL_VALUE -1
#define MAX3SAT_BAD_STRING_FORMAT -2
#define MAX3SAT_BAD_FILENAME -3
#define MAX3SAT_CLAUSES_EMPTY -4

using namespace std;

class ClauseVariable {
private:
    int number;
    bool negated;
public:
    int setNumber(int n);
    void setNegated(bool n);
    int getNumber() const;  // NOLINT
    bool isNegated() const;  // NOLINT
    int loadFromString(string &str);
    void print() const;
    bool isSatisfied(bool var) const;  // NOLINT
};

class Clause {
private:
    ClauseVariable* variables;
public:
    ~Clause();
    int loadFromString(string &str);
    void print() const;
    bool isSatisfied(bool var0, bool var1, bool var2);
    ClauseVariable* getVariables();
};

class Max3SatProblem {
private:
    string filename;
    vector<Clause*>* clauses;
    int genotypeSize;

public:
    Max3SatProblem();
    ~Max3SatProblem();
    void setFilename(const string &filename);
    int loadClausesFromFile();
    int calculateGenotypeSize();
    double compute(Individual* individual);
};
