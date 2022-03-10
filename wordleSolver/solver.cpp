#include "solver.h"
#include <stdexcept>
#include <format>

void Solver::HelpSolve(std::vector<Attempts> prevAttempts)
{
}

std::vector<Results> getResultsFromString(std::string str)
{
	std::vector<Results> res(str.length());

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 'G') {
			res[i] = Results::Green;
		}
		else if (str[i] == 'Y') {
			res[i] == Results::Yellow;
		}
		else if (str[i] == 'B') {
			res[i] == Results::Black;
		}
		else {
			throw std::invalid_argument(std::format("Unsupported input\n", str[i]));
		}
		 
	}

	return res;
}
