#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>

using Transition = std::map<std::pair<std::string, std::string>, std::string>;

class DeterministicFiniteAutomaton {
	std::set<std::string> m_states;
	std::set<std::string> m_alphabet;
	std::string m_initialState;
	std::set<std::string> m_finalStates;
	Transition m_transition;

	bool CheckNonEmptyStates() const;
	bool CheckNonEmptyAlphabet() const;
	bool CheckValidInitialState() const;
	bool CheckValidFinalStates() const;
	bool CheckValidTransition() const;
public:
	DeterministicFiniteAutomaton();
	DeterministicFiniteAutomaton(const std::set<std::string>& states, const std::set<std::string>& alphabet, const std::string& initialState, const std::set<std::string>& finalStates, const Transition& transition);
	friend std::istream& operator>>(std::istream& in, DeterministicFiniteAutomaton& deterministicFiniteAutomaton);
	friend std::ostream& operator<<(std::ostream& out, const DeterministicFiniteAutomaton& deterministicFiniteAutomaton);

	const std::set<std::string>& GetStates() const;
	const std::set<std::string>& GetAlphabet() const;
	const std::string& GetInitialState() const;
	const std::set<std::string>& GetFinalStates() const;
	const Transition& GetTransition() const;
	void SetStates(const std::set<std::string>& states);
	void SetAlphabet(const std::set<std::string>& alphabet);
	void SetInitialState(const std::string& initialState);
	void SetFinalStates(const std::set<std::string>& finalStates);
	void SetTransition(const Transition& transition);

	bool VerifyAutomaton() const;
};