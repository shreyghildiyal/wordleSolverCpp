#include "solver.h"
#include <iostream>
#include "../dataLoader/loader.h"

void Solver::HelpSolve(std::vector<Attempt> prevAttempts) {

    if (prevAttempts.size() == 0) {
        std::cout << "You need to provide atleast one attempt and its result\n";
        return;
    }
    int wordLen = prevAttempts[0].getWord().size();

    std::vector<std::string> words;
    getWordsOfLength(wordLen, &words);
    // getWordsOfLength(1)[1] << std::endl;
    std::cout << "Found a word " << words[0] << '\n';
    std::cout << "Total Words " << words.size() << '\n';
}

std::string Attempt::getWord() {
    return word;
}