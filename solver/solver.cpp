#include "solver.h"
#include <iostream>
#include "../dataLoader/loader.h"

void Solver::HelpSolve(std::vector<Attempt> prevAttempts) {

    if (prevAttempts.size() == 0) {
        std::cout << "You need to provide atleast one attempt and its result\n";
        return;
    }
    int wordLen = prevAttempts[0].getWord().size();

    std::map<std::string, int> words;
    getDictionaryWordsOfLength(wordLen, &words);
    int minFrequency = 100000;
    std::cout << "Before req filter Total Words " << words.size() << '\n';
    words = getFilteredWordsByFrequency(words, minFrequency);
    // getWordsOfLength(1)[1] << std::endl;
    std::cout << "WordLen " << wordLen << std::endl;
    // std::cout << "Found a word " << words[0] << '\n';
    std::cout << "Total Words " << words.size() << '\n';

    for (std::vector<Attempt>::iterator i = prevAttempts.begin(); i != prevAttempts.end(); i++) {
        words = getPrunedWords(words, *i);
    }
}

bool Solver::isMatch(std::string, Attempt) {
    return false;
}

std::string Attempt::getWord() {
    return word;
}

Attempt::Attempt(std::string word, std::string result)
{
    if (word.length() != result.length()) {
        throw std::invalid_argument( "the length of attempted word and response cant be different" );
    }
    this->word = word;
    this->result = result;
}

std::map<std::string, int> Solver::getPrunedWords(std::map<std::string, int> words, Attempt attempt) {

    std::map<std::string, int> result;

    for (std::map<std::string, int>::iterator i = words.begin(); i != words.end(); i++) {
        if (isMatch(i->first, attempt)) {
            result[i->first] = i->second;
        }
    }

    return result;
}
