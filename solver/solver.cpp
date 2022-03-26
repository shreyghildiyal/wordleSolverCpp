#include "solver.h"

#include <iostream>
#include <map>

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

    std::cout << "Total Words after pruning " << words.size() << '\n';
    if (words.size() < 10) {
        for (std::map<std::string, int>::iterator i = words.begin(); i != words.end(); i++) {
            std::cout << i->first << " " << i->second << "\n";
        }
    }

    // now that we have a list of possible words, we try to find the word that divides the solution space into the smallest pieces

    std::string suggestedWord = getSuggestedWord(words);
}

bool Solver::isMatch(std::string word, Attempt attempt) {
    std::string testWord = "epoxy";
    bool testStatus = (word == testWord);

    std::map<char, int> attemptCharCounts;
    std::map<char, int> wordCharCounts;
    std::string attemptWord = attempt.getWord();
    std::string attemptResult = attempt.getResult();

    for (int i = 0; i < word.length(); i++) {
        if (attemptCharCounts.find(attemptWord[i]) != attemptCharCounts.end()) {
            attemptCharCounts[attemptWord[i]] = 0;
        }

        if (attemptResult[i] == 'G') {
            if (word[i] != attemptWord[i]) {
                return false;
            }
        } else if (word[i] == attemptWord[i]) {
            return false;
        }
        if (attemptResult[i] == 'G' || attemptResult[i] == 'Y') {
            attemptCharCounts[attemptWord[i]]++;
        }

        if (wordCharCounts.find(word[i]) != wordCharCounts.end()) {
            wordCharCounts[word[i]] = 0;
        }
        wordCharCounts[word[i]]++;
    }

    for (int i = 0; i < word.length(); i++) {
        if (attemptCharCounts[attemptWord[i]] == 0) {
            if (wordCharCounts.find(attemptWord[i]) != wordCharCounts.end()) {
                if (testStatus) {
                    std::cout << "found char " << attemptWord[i] << " in word " << word
                              << " but its count is supposed to be 0\n";
                }

                return false;
            }
        } else {
            if (wordCharCounts.find(attemptWord[i]) == wordCharCounts.end()) {
                if (testStatus) {
                    std::cout << "needed char " << attemptWord[i] << " not found in word " << word << "\n";
                }
                return false;
            } else if (wordCharCounts[attemptWord[i]] < attemptCharCounts[attemptWord[i]]) {
                if (testStatus) {
                    std::cout << "char " << attemptWord[i] << "doesnt appear often enough in word " << word << "\n";
                }
                return false;
            }
        }
    }

    return true;
}

std::string Solver::getSuggestedWord(std::map<std::string, int> words)
{
    int minScore = -1;
    std::string bestWord = "";
    int bestWordFreq = 0;
    int count = 0;
    std::cout << "inside get suggested word\n" ;
    for (std::map<std::string, int>::iterator word = words.begin(); word != words.end(); word++) {
        int score = getWordScore(word->first, words);
        // std::cout << "got score for " << word->first << " " << score << "\n";
        if (minScore == -1) {
            bestWord = word->first;
            bestWordFreq = word->second;
            minScore = score;
            std::cout << "Current best Word " << word->first << " with freq " << word->second << " minscore " << minScore << "\n"; 
        } else if (score < minScore) {
            bestWord = word->first;
            bestWordFreq = word->second;
            minScore = score;
            std::cout << "Current best Word " << word->first << " with freq " << word->second << " minscore " << minScore << "\n"; 
        } else if (score == minScore) {
            if (word->second > bestWordFreq) {
                bestWordFreq = word->second;
                minScore = score;
                std::cout << "Current best Word " << word->first << " with freq " << word->second << " minscore " << minScore << "\n"; 
            }
        }
    }
    std::cout << "finally best score is " << minScore << "\n";
    return bestWord;
}

int Solver::getWordScore(std::string word, std::map<std::string, int> words)
{
    std::map<std::string, int> resmap;
    int maxScore = 0;
    for (std::map<std::string, int>::iterator otherWord = words.begin(); otherWord != words.end(); otherWord++) {
        std::string res = getMatchResult(word, otherWord->first);
        if (resmap.find(res) == resmap.end()) {
            resmap[res] = 0;
        }
        resmap[res]++;
        if (resmap[res] > maxScore) {
            maxScore = resmap[res];
        }
    }
    return maxScore;

    

    return 0;
}

std::string Solver::getMatchResult(std::string checkingWord, std::string possiblyActualWord) {
    std::string res = "";
    std::map<char, int> acCharCounts;
    for (int i = 0; i < checkingWord.length(); i++) {
        if (acCharCounts.find(possiblyActualWord[i]) == acCharCounts.end()) {
            acCharCounts[possiblyActualWord[i]] = 0;
        } 
        acCharCounts[possiblyActualWord[i]]++;
    }
    for (int i = 0; i < checkingWord.length(); i++) {
        if (checkingWord[i] == possiblyActualWord[i]) {
            res = res + "G";
        } else {
            if (acCharCounts.find(checkingWord[i]) == acCharCounts.end()) {
                res = res + "B";
            } else {
                if (acCharCounts[checkingWord[i]] > 0) {
                    res = res + "Y";
                } else {
                    res = res + "B";
                }
            }
        }
    }
    return res;
}

std::string Attempt::getWord() { return word; }

std::string Attempt::getResult() { return result; }

Attempt::Attempt(std::string word, std::string result) {
    if (word.length() != result.length()) {
        throw std::invalid_argument("the length of attempted word and response cant be different");
    }
    this->word = word;
    this->result = result;
}

std::map<std::string, int> Solver::getPrunedWords(std::map<std::string, int> words, Attempt attempt) {
    std::map<std::string, int> result;

    std::string testWord = "epoxy";
    int count = 0;

    for (std::map<std::string, int>::iterator i = words.begin(); i != words.end(); i++) {
        count++;
        if (i->first == testWord) {
            std::cout << "found the test word " << testWord << "\n";
        }
        if (isMatch(i->first, attempt)) {
            result[i->first] = i->second;
        } else {
            if (count % 100 == 0) {
                // std::cout << "word " << i->first << " rejected\n";
            }
        }
    }

    return result;
}
