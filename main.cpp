#include <iostream>
#include "Max3SatProblem.h"

int main() {
    Max3SatProblem problem;
    problem.setFilename(R"(C:\Users\PAVILION\CLionProjects\TEPmax3sat\clauses\50\m3s_50_0.txt)");
    problem.load();
    problem.setVariablesSize(50);
    cout << problem.compute();

    return 0;
}
