#include <fstream>
#include "DeterministicFiniteAutomaton.h"

int main() {
	std::ifstream finDFA{ "inputDFA.txt" };
	if (!finDFA.is_open()) {
		std::cerr << "Error opening file\n";
		return -1;
	}
	DeterministicFiniteAutomaton deterministicFiniteAutomaton;
	finDFA >> deterministicFiniteAutomaton;
	if (deterministicFiniteAutomaton.VerifyAutomaton())
		std::cout << deterministicFiniteAutomaton;
	else
		std::cout << "Invalid DFA!\n";
}