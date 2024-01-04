#include "DeterministicFiniteAutomaton.h"

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton() : m_states{}, m_alphabet{}, m_initialState{}, m_finalStates{}, m_transition{} {}

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(const std::set<std::string>& states, const std::set<std::string>& alphabet, const std::string& initialState, const std::set<std::string>& finalStates, const Transition& transition)
	: m_states{ states }, m_alphabet{ alphabet }, m_initialState{ initialState }, m_finalStates{ finalStates }, m_transition{ transition } {}

const std::set<std::string>& DeterministicFiniteAutomaton::GetStates() const { return m_states; }

const std::set<std::string>& DeterministicFiniteAutomaton::GetAlphabet() const { return m_alphabet; }

const std::string& DeterministicFiniteAutomaton::GetInitialState() const { return m_initialState; }

const std::set<std::string>& DeterministicFiniteAutomaton::GetFinalStates() const { return m_finalStates; }

const Transition& DeterministicFiniteAutomaton::GetTransition() const { return m_transition; }

void DeterministicFiniteAutomaton::SetStates(const std::set<std::string>& states) { m_states = states; }

void DeterministicFiniteAutomaton::SetAlphabet(const std::set<std::string>& alphabet) { m_alphabet = alphabet; }

void DeterministicFiniteAutomaton::SetInitialState(const std::string& initialState) { m_initialState = initialState; }

void DeterministicFiniteAutomaton::SetFinalStates(const std::set<std::string>& finalStates) { m_finalStates = finalStates; }

void DeterministicFiniteAutomaton::SetTransition(const Transition& transition) { m_transition = transition; }

std::istream& operator>>(std::istream& in, DeterministicFiniteAutomaton& deterministicFiniteAutomaton) {
	int nrStates, nrValuesAlphabet, nrFinalStates, nrTransitions;
	in >> nrStates;
	for (size_t i = 0; i < nrStates; ++i) {
		std::string state;
		in >> state;
		deterministicFiniteAutomaton.m_states.insert(state);
	}
	in >> nrValuesAlphabet;
	for (size_t i = 0; i < nrValuesAlphabet; ++i) {
		std::string symbol;
		in >> symbol;
		deterministicFiniteAutomaton.m_alphabet.insert(symbol);
	}
	in >> deterministicFiniteAutomaton.m_initialState >> nrFinalStates;
	for (size_t i = 0; i < nrFinalStates; ++i) {
		std::string finalState;
		in >> finalState;
		deterministicFiniteAutomaton.m_finalStates.insert(finalState);
	}
	in >> nrTransitions;
	for (size_t i = 0; i < nrTransitions; ++i) {
		std::string currentState, symbol, nextState;
		in >> currentState >> symbol >> nextState;
		deterministicFiniteAutomaton.m_transition[{currentState, symbol }] = nextState;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const DeterministicFiniteAutomaton& deterministicFiniteAutomaton) {
	out << "AFN = ({ ";
	for (const auto& state : deterministicFiniteAutomaton.m_states)
		out << state << " ";
	out << "}, { ";
	for (const auto& symbol : deterministicFiniteAutomaton.m_alphabet)
		out << symbol << " ";
	out << "}, delta, " << deterministicFiniteAutomaton.m_initialState << ", { ";
	for (const auto& finalState : deterministicFiniteAutomaton.m_finalStates)
		out << finalState << " ";
	out << "})\n\n";
	out << "delta:\n";
	for (const auto& [key, value] : deterministicFiniteAutomaton.m_transition) {
		const auto& [currentState, symbol] = key;
		const auto& nextState = value;
		out << " (" << currentState << ", " << symbol << ") -> " << nextState << "\n";
	}
	return out << "\n";
}

bool DeterministicFiniteAutomaton::VerifyAutomaton() const {
	return CheckNonEmptyStates() && CheckNonEmptyAlphabet() && CheckValidInitialState() && CheckValidFinalStates() && CheckValidTransition();
}

bool DeterministicFiniteAutomaton::CheckNonEmptyStates() const {
	if (m_states.empty()) {
		std::cout << "Invalid automaton: empty set of states!\n";
		return false;
	}
	return true;
}

bool DeterministicFiniteAutomaton::CheckNonEmptyAlphabet() const {
	if (m_alphabet.empty()) {
		std::cout << "Invalid automaton: empty alphabet!\n";
		return false;
	}
	return true;
}

bool DeterministicFiniteAutomaton::CheckValidInitialState() const {
	if (m_initialState.empty()) {
		std::cout << "Invalid automaton: empty initial state!\n";
		return false;
	}
	if (m_states.find(m_initialState) == m_states.end()) {
		std::cout << "Invalid automaton: initial state not in set of states!\n";
		return false;
	}
	return true;
}

bool DeterministicFiniteAutomaton::CheckValidFinalStates() const {
	if (m_finalStates.empty()) {
		std::cout << "Invalid automaton: empty set of final states!\n";
		return false;
	}
	for (const auto& finalState : m_states)
		if (m_states.find(finalState) == m_states.end()) {
			std::cout << "Invalid automaton: final state not in set of states!\n";
			return false;
		}
	return true;
}

bool DeterministicFiniteAutomaton::CheckValidTransition() const {
	if (m_transition.empty()) {
		std::cout << "Invalid automaton: empty transition function!\n";
		return false;
	}
	for (const auto& [key, value] : m_transition) {
		const auto& [currentState, symbol] = key;
		const auto& nextState = value;
		if (m_states.find(currentState) == m_states.end()) {
			std::cout << "Invalid automaton: State " << currentState << "from transition function not in set of states!\n";
			return false;
		}
		if (m_alphabet.find(symbol) == m_alphabet.end()) {
			std::cout << "Invalid automaton: Symbol " << symbol << "from transition function not in alphabet!\n";
			return false;
		}
		if (m_states.find(nextState) == m_states.end()) {
			std::cout << "Invalid automaton: State " << nextState << "from transition function not in set of states!\n";
			return false;
		}
	}
	return true;
}