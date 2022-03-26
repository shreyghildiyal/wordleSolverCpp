#include <iostream>

#ifndef SOLVER_H
#include "solver/solver.h"
#endif


int main(int, char**) {
    std::cout << "Hello, world!\n";
    std::cout << "Second Line" << std::endl;
    Solver solver;
    std::vector<Attempt> attempts;
    attempts.push_back(Attempt("raise", "BBBBB"));
    attempts.push_back(Attempt("blunt", "BBBYB"));
    attempts.push_back(Attempt("knock", "BYBBB"));
    solver.HelpSolve(attempts);
    // std::string word = "rowdy";
    // std::string attemptWord = "raise";
    // std::string attemptRes = "GBBBB";
    // bool res = solver.isMatch(word, Attempt(attemptWord, attemptRes));
    // std::cout << word << " " << attemptWord << " " << attemptRes << " " <<  std::endl;
    // if (res) {
    //     std::cout << "true\n";
    // } else {
    //     std::cout << "false\n";
    // }
}
