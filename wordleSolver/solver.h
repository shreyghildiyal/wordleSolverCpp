#include <vector>
#include <string>


enum class Results {
	Green,
	Yellow,
	Black
};

class Attempts {
	std::string word;
	std::vector<Results> result;
};

class Solver {
	void HelpSolve(std::vector<Attempts> prevAttempts);
};

std::vector<Results> getResultsFromString(std::string str);