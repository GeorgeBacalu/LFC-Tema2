#include "LambdaTransitionsAutomaton.h"

LambdaTransitionsAutomaton::LambdaTransitionsAutomaton() : m_states{}, m_alphabet{}, m_initialState{}, m_finalStates{}, m_transition{} {}

LambdaTransitionsAutomaton::LambdaTransitionsAutomaton(const std::set<std::string>& states, const std::set<std::string>& alphabet, const std::string& initialState, const std::set<std::string>& finalStates, const TransitionNFA& transition)
	: m_states{ states }, m_alphabet{ alphabet }, m_initialState{ initialState }, m_finalStates{ finalStates }, m_transition{ transition } {}

const std::set<std::string>& LambdaTransitionsAutomaton::GetStates() const { return m_states; }

const std::set<std::string>& LambdaTransitionsAutomaton::GetAlphabet() const { return m_alphabet; }

const std::string& LambdaTransitionsAutomaton::GetInitialState() const { return m_initialState; }

const std::set<std::string>& LambdaTransitionsAutomaton::GetFinalStates() const { return m_finalStates; }

const TransitionNFA& LambdaTransitionsAutomaton::GetTransition() const { return m_transition; }

void LambdaTransitionsAutomaton::SetStates(const std::set<std::string>& states) { m_states = states; }

void LambdaTransitionsAutomaton::SetAlphabet(const std::set<std::string>& alphabet) { m_alphabet = alphabet; }

void LambdaTransitionsAutomaton::SetInitialState(const std::string& initialState) { m_initialState = initialState; }

void LambdaTransitionsAutomaton::SetFinalStates(const std::set<std::string>& finalStates) { m_finalStates = finalStates; }

void LambdaTransitionsAutomaton::SetTransition(const TransitionNFA& transition) { m_transition = transition; }

std::istream& operator>>(std::istream& in, LambdaTransitionsAutomaton& lambdaTransitionsAutomaton) {
	int nrStates, nrValuesAlphabet, nrFinalStates, nrTransitions;
	in >> nrStates;
	for (size_t i = 0; i < nrStates; ++i) {
		std::string state;
		in >> state;
		lambdaTransitionsAutomaton.m_states.insert(state);
	}
	in >> nrValuesAlphabet;
	for (size_t i = 0; i < nrValuesAlphabet; ++i) {
		std::string symbol;
		in >> symbol;
		lambdaTransitionsAutomaton.m_alphabet.insert(symbol);
	}
	in >> lambdaTransitionsAutomaton.m_initialState >> nrFinalStates;
	for (size_t i = 0; i < nrFinalStates; ++i) {
		std::string finalState;
		in >> finalState;
		lambdaTransitionsAutomaton.m_finalStates.insert(finalState);
	}
	in >> nrTransitions;
	for (size_t i = 0; i < nrTransitions; ++i) {
		std::string currentState, symbol, nextState;
		in >> currentState >> symbol >> nextState;
		lambdaTransitionsAutomaton.m_transition[{currentState, symbol }].push_back(nextState);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const LambdaTransitionsAutomaton& lambdaTransitionsAutomaton) {
	out << "FNA = ({ ";
	for (const auto& state : lambdaTransitionsAutomaton.m_states)
		out << state << " ";
	out << "}, { ";
	for (const auto& symbol : lambdaTransitionsAutomaton.m_alphabet)
		out << symbol << " ";
	out << "}, delta, " << lambdaTransitionsAutomaton.m_initialState << ", { ";
	for (const auto& finalState : lambdaTransitionsAutomaton.m_finalStates)
		out << finalState << " ";
	out << "})\n\n";
	out << "delta:\n";
	for (const auto& [key, value] : lambdaTransitionsAutomaton.m_transition) {
		const auto& [currentState, symbol] = key;
		for (const auto& nextState : value)
			out << " (" << currentState << ", " << symbol << ") -> " << nextState << "\n";
	}
	return out << "\n";
}

LambdaTransitionsAutomaton LambdaTransitionsAutomaton::CreateBasicAutomaton(char ch, int& nrStates) {
	return LambdaTransitionsAutomaton();
}

LambdaTransitionsAutomaton LambdaTransitionsAutomaton::Union(const LambdaTransitionsAutomaton& A, const LambdaTransitionsAutomaton& B, int& nrStates) {
	return LambdaTransitionsAutomaton();
}

LambdaTransitionsAutomaton LambdaTransitionsAutomaton::Concatenate(const LambdaTransitionsAutomaton& A, const LambdaTransitionsAutomaton& B, int& nrStates) {
	return LambdaTransitionsAutomaton();
}

LambdaTransitionsAutomaton LambdaTransitionsAutomaton::KleeneClosure(const LambdaTransitionsAutomaton& A, int& nrStates) {
	return LambdaTransitionsAutomaton();
}