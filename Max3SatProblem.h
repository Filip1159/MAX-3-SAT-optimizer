#pragma once
#include <string>
#include <vector>

using namespace std;

class ClauseVariable {
private:
    int number;
    bool negated;
public:
    void setNumber(int n);
    void setNegated(bool n);
    int getNumber() const;
    bool isNegated() const;
    void loadFromString(string str);
    string toString() const;
    bool isSatisfied(bool var) const;
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
    bool* variables;
    int variablesSize;
    vector<Clause*>* clauses;

public:
    Max3SatProblem();
    ~Max3SatProblem();
    void setFilename(const string &filename);
    void load();
    double compute();
    void setVariablesSize(int size);
};
