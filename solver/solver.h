#include <vector>
#include <string>
#include <tuple>
#include <map>

class Attempt {
    std::string word;
    std::string result;
    public:
    std::string getWord();
    std::string getResult();
    Attempt(std::string word, std::string result);
};

class Solver {
    public:
    void HelpSolve(std::vector<Attempt> prevAttempts);
    std::map<std::string, int> getPrunedWords(std::map<std::string, int> words, Attempt attempt);
    bool isMatch(std::string word, Attempt attempt);
    std::string getSuggestedWord(std::map<std::string, int> words);
    int getWordScore(std::string word, std::map<std::string, int> words);
    std::string getMatchResult(std::string checkingWord, std::string possiblyActualWord);
};