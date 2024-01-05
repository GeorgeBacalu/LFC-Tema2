#include <fstream>
#include "DeterministicFiniteAutomaton.h"

int main() {
	std::ifstream finDFA{ "inputDFA.txt" };
	if (!finDFA.is_open()) {
		std::cerr << "Error opening file\n";
		return -1;
	}
	DeterministicFiniteAutomaton dfa;
	finDFA >> dfa;
	if (dfa.VerifyAutomaton()) {
		std::cout << dfa;
		std::string word;
		std::cout << "Enter word to check: ";
		std::cin >> word;
		std::cout << "Word is" << (dfa.CheckWord(dfa.GetInitialState(), word) ? " " : " not ") << "accepted!\n\n";
	}
	else
		std::cout << "Invalid DFA!\n";
}