#include <fstream>
#include "RegularExpression.h"

DeterministicFiniteAutomaton ConvertRegexToDFA(const std::string& expression);

int main() {
	RegularExpression regex;
	std::ifstream finRE{ "inputRE.txt" };
	if (!finRE.is_open()) {
		std::cerr << "Error opening input file\n";
		return -1;
	}
	std::ofstream foutDFA{ "outputDFA.txt" };
	if (!foutDFA.is_open()) {
		std::cerr << "Error opening output file\n";
		return -1;
	}
	finRE >> regex;
	int option;
	DeterministicFiniteAutomaton dfa;
	do {
		std::cout << "Command menu:\n";
		std::cout << "0. Exit\n";
		std::cout << "1. Transform Regex in DFA and display it to console and output file\n";
		std::cout << "2. Comprehensively display regex from file\n";
		std::cout << "3. Check if a word is accepted by DFA\n";
		std::cout << "Choose option: ";
		std::cin >> option;
		switch (option) {
		case 0: break;
		case 1:
			try {
				dfa = ConvertRegexToDFA(regex.GetExpression());
				std::cout << "Regex -> Postfix -> NFA -> DFA:\n" << dfa << "\n\n";
				foutDFA << "Regex -> Postfix -> NFA -> DFA:\n" << dfa << "\n\n";
			}
			catch (const std::invalid_argument& exception) {
				std::cout << exception.what() << "\n";
			}
			break;
		case 2:
			std::cout << "\nRegex: " << regex << "\n\n";
			break;
		case 3:
			try {
				dfa = ConvertRegexToDFA(regex.GetExpression());
				std::cout << "Regex -> Postfix -> NFA -> DFA:\n" << dfa << "\n\n";
				std::string word;
				std::cout << "Enter word to check: ";
				std::cin >> word;
				std::cout << "Word is" << (dfa.CheckWord(dfa.GetInitialState(), word) ? " " : " not ") << "accepted!\n\n";
			}
			catch (const std::invalid_argument& exception) {
				std::cout << exception.what() << "\n";
			}
			break;
		}
	} while (option);
}

DeterministicFiniteAutomaton ConvertRegexToDFA(const std::string& expression) {
	RegularExpression regex{ expression };
	if (!regex.VerifyExpression())
		throw std::invalid_argument("Invalid regular expression");
	std::cout << "\nRegex: " << regex << "\n\n";
	std::string postfixForm = regex.ConvertToPostfixForm();
	std::cout << "Regex -> Postfix: " << postfixForm << "\n\n";
	LambdaTransitionsAutomaton nfa = regex.convertToNFA(postfixForm);
	std::cout << "Regex -> Postfix -> NFA:\n" << nfa << "\n\n";
	return nfa.convertToDFA();
}