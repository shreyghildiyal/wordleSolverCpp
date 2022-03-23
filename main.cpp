#include <iostream>

#ifndef SOLVER_H
#include "solver/solver.h"
#endif


int main(int, char**) {
    std::cout << "Hello, world!\n";
    std::cout << "Second Line" << std::endl;
    Solver solver;
    std::vector<Attempt> attempts;
    attempts.push_back(Attempt("raise", "GBBBB"));
    solver.HelpSolve(attempts);
}
