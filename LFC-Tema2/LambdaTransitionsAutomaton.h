#pragma once

#include "DeterministicFiniteAutomaton.h"

using TransitionNFA = std::map<std::pair<std::string, std::string>, std::set<std::string>>;

class LambdaTransitionsAutomaton {
	std::set<std::string> m_states;
	std::set<std::string> m_alphabet;
	std::string m_initialState;
	std::set<std::string> m_finalStates;
	TransitionNFA m_transition;
public:
	static const std::string LAMBDA;

	LambdaTransitionsAutomaton();
	LambdaTransitionsAutomaton(const std::set<std::string>& states, const std::set<std::string>& alphabet, const std::string& initialState, const std::set<std::string>& finalStates, const TransitionNFA& transition);
	friend std::istream& operator>>(std::istream& in, LambdaTransitionsAutomaton& lambdaTransitionsAutomaton);
	friend std::ostream& operator<<(std::ostream& out, const LambdaTransitionsAutomaton& lambdaTransitionsAutomaton);

	const std::set<std::string>& GetStates() const;
	const std::set<std::string>& GetAlphabet() const;
	const std::string& GetInitialState() const;
	const std::set<std::string>& GetFinalStates() const;
	const TransitionNFA& GetTransition() const;
	void SetStates(const std::set<std::string>& states);
	void SetAlphabet(const std::set<std::string>& alphabet);
	void SetInitialState(const std::string& initialState);
	void SetFinalStates(const std::set<std::string>& finalStates);
	void SetTransition(const TransitionNFA& transition);

	static LambdaTransitionsAutomaton CreateBasicAutomaton(char ch, int& nrStates);
	static LambdaTransitionsAutomaton Union(const LambdaTransitionsAutomaton& A, const LambdaTransitionsAutomaton& B, int& nrStates);
	static LambdaTransitionsAutomaton Concatenate(const LambdaTransitionsAutomaton& A, const LambdaTransitionsAutomaton& B);
	static LambdaTransitionsAutomaton KleeneClosure(const LambdaTransitionsAutomaton& A, int& nrStates);

	DeterministicFiniteAutomaton convertToDFA() const;
	std::set<std::string> GetLambdaClosure(const std::set<std::string>& states) const;
	std::set<std::string> FindReachableStates(const std::set<std::string>& states, const std::string& symbol) const;
};