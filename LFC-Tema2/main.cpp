#include <fstream>
#include "DeterministicFiniteAutomaton.h"
#include "RegularExpression.h"

int main() {
	DeterministicFiniteAutomaton dfa;
	RegularExpression regex;
	std::ifstream finDFA{ "inputDFA.txt" };
	if (!finDFA.is_open()) {
		std::cerr << "Error opening file\n";
		return -1;
	}
	std::ifstream finRE{ "inputRE.txt" };
	if (!finRE.is_open()) {
		std::cerr << "Error opening file\n";
		return -1;
	}
	finDFA >> dfa;
	if (dfa.VerifyAutomaton()) {
		std::cout << dfa;
		std::string word;
		std::cout << "Enter word to check: ";
		std::cin >> word;
		std::cout << "Word is" << (dfa.CheckWord(dfa.GetInitialState(), word) ? " " : " not ") << "accepted!\n\n";
	}
	else std::cout << "Invalid DFA!\n";
	finRE >> regex;
	if (regex.VerifyExpression())
		std::cout << "Regex: " << regex << "\n";
}