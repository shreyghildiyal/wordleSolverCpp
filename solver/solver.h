#include <vector>
#include <string>
#include <tuple>

class Attempt {
    std::string word;
    std::string result;
    public:
    std::string getWord();
};

class Solver {
    public:
    void HelpSolve(std::vector<Attempt> prevAttempts);
};