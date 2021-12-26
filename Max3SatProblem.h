#pragma once
#include <string>
#include <vector>
#include "Individual.h"

using namespace std;

class ClauseVariable {
private:
    int number;
    bool negated;
public:
    void setNumber(int n);
    void setNegated(bool n);
    [[nodiscard]] int getNumber() const;
    [[nodiscard]] bool isNegated() const;
    void loadFromString(string str);
    [[nodiscard]] string toString() const;
    [[nodiscard]] bool isSatisfied(bool var) const;
};

class Clause {
private:
    ClauseVariable* variables;
public:
    void loadFromString(string str);
    string toString();
    bool isSatisfied(bool var0, bool var1, bool var2);
    ClauseVariable* getVariables();
};

class Max3SatProblem {
private:
    string filename;
    vector<Clause*>* clauses;

public:
    Max3SatProblem();
    ~Max3SatProblem();
    void setFilename(const string &filename);
    void load();
    double compute(Individual* individual);
};
