#include "LambdaTransitionsAutomaton.h"
#include <stack>

const std::string LambdaTransitionsAutomaton::LAMBDA = "@";

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
		lambdaTransitionsAutomaton.m_transition[{currentState, symbol }].insert(nextState);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const LambdaTransitionsAutomaton& lambdaTransitionsAutomaton) {
	out << "NFA = ({ ";
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
	if (!isalnum(ch))
		std::cout << "Invalid automaton: invalid symbol!\n";

	std::string newInitialState = "q_" + std::to_string(nrStates++);
	std::string newFinalState = "q_" + std::to_string(nrStates++);
	std::string symbol = std::string{ ch };

	std::set<std::string> states = { newInitialState, newFinalState };
	std::set<std::string> alphabet = { symbol };
	std::string initialState = newInitialState;
	std::set<std::string> finalStates = { newFinalState };
	TransitionNFA transition = { {{newInitialState, symbol}, {newFinalState}} };
	return { states, alphabet, initialState, finalStates, transition };
}

LambdaTransitionsAutomaton LambdaTransitionsAutomaton::Union(const LambdaTransitionsAutomaton& A, const LambdaTransitionsAutomaton& B, int& nrStates) {
	LambdaTransitionsAutomaton C;
	std::string newInitialState = "q_" + std::to_string(nrStates++);
	std::string newFinalState = "q_" + std::to_string(nrStates++);
	C.m_states.insert(A.m_states.begin(), A.m_states.end());
	C.m_states.insert(B.m_states.begin(), B.m_states.end());
	C.m_alphabet.insert(A.m_alphabet.begin(), A.m_alphabet.end());
	C.m_alphabet.insert(B.m_alphabet.begin(), B.m_alphabet.end());
	C.m_initialState = newInitialState;
	C.m_finalStates.insert(newFinalState);
	C.m_transition.insert(A.m_transition.begin(), A.m_transition.end());
	C.m_transition.insert(B.m_transition.begin(), B.m_transition.end());
	C.m_transition[{newInitialState, LAMBDA}].insert(A.m_initialState);
	C.m_transition[{newInitialState, LAMBDA}].insert(B.m_initialState);
	for (const auto& finalStateA : A.m_finalStates)
		C.m_transition[{finalStateA, LAMBDA}].insert(newFinalState);
	for (const auto& finalStateB : B.m_finalStates)
		C.m_transition[{finalStateB, LAMBDA}].insert(newFinalState);
	return C;
}

LambdaTransitionsAutomaton LambdaTransitionsAutomaton::Concatenate(const LambdaTransitionsAutomaton& A, const LambdaTransitionsAutomaton& B) {
	LambdaTransitionsAutomaton C;
	C.m_states.insert(A.m_states.begin(), A.m_states.end());
	C.m_states.insert(B.m_states.begin(), B.m_states.end());
	C.m_alphabet.insert(A.m_alphabet.begin(), A.m_alphabet.end());
	C.m_alphabet.insert(B.m_alphabet.begin(), B.m_alphabet.end());
	C.m_initialState = A.m_initialState;
	C.m_finalStates.insert(B.m_finalStates.begin(), B.m_finalStates.end());
	C.m_transition.insert(A.m_transition.begin(), A.m_transition.end());
	C.m_transition.insert(B.m_transition.begin(), B.m_transition.end());
	// Transitions leading to initial state of B are redirected to lead to final states of A
	for (const auto& finalStateA : A.m_finalStates) {
		// Find transitions from initial state of B with each symbol in B alphabet
		for (const auto& symbol : B.m_alphabet) {
			auto transitions = B.m_transition.find({ B.m_initialState, symbol });
			if (transitions != B.m_transition.end()) {
				const auto& nextStates = transitions->second;
				for (const auto& nextState : nextStates)
					C.m_transition[{finalStateA, symbol}].insert(nextState);
			}
		}
		// Add lambda-transitions from final states of A to states that are directly accessible by initial state of B
		auto lambdaTransitions = B.m_transition.find({ B.m_initialState, LAMBDA });
		if (lambdaTransitions != B.m_transition.end()) {
			const auto& nextStates = lambdaTransitions->second;
			for (const auto& nextState : nextStates)
				C.m_transition[{finalStateA, LAMBDA}].insert(nextState);
		}
	}
	// Remove initial state of B and final states of A from C states
	C.m_states.erase(B.m_initialState);
	for (const auto& finalStateA : A.m_finalStates)
		C.m_finalStates.erase(finalStateA);
	return C;
}

LambdaTransitionsAutomaton LambdaTransitionsAutomaton::KleeneClosure(const LambdaTransitionsAutomaton& A, int& nrStates) {
	LambdaTransitionsAutomaton B;
	std::string newInitialState = "q_" + std::to_string(nrStates++);
	std::string newFinalState = "q_" + std::to_string(nrStates++);
	B.m_states.insert(A.m_states.begin(), A.m_states.end());
	B.m_states.insert(newInitialState);
	B.m_states.insert(newFinalState);
	B.m_alphabet.insert(A.m_alphabet.begin(), A.m_alphabet.end());
	B.m_initialState = newInitialState;
	B.m_finalStates.insert(newFinalState);
	B.m_transition[{newInitialState, LAMBDA}].insert(A.m_initialState);
	B.m_transition[{newInitialState, LAMBDA}].insert(newFinalState);
	for (const auto& finalStateA : A.m_finalStates) {
		B.m_transition[{finalStateA, LAMBDA}].insert(A.m_initialState);
		B.m_transition[{finalStateA, LAMBDA}].insert(newFinalState);
	}
	return B;
}

std::set<std::string> LambdaTransitionsAutomaton::GetLambdaClosure(const std::set<std::string>& states) const {
	std::set<std::string> lambdaClosure = states;
	std::stack<std::string> stack;
	// Push input states to stack
	for (const auto& state : states)
		stack.push(state);
	while (!stack.empty()) {
		std::string top = stack.top();
		stack.pop();
		// Get lambda-transitions for current state
		auto transitionsIt = m_transition.find({ top, LAMBDA });
		if (transitionsIt != m_transition.end()) {
			const auto& reachableStates = transitionsIt->second;
			for (const auto& reachableState : reachableStates) 
				if (lambdaClosure.insert(reachableState).second) // checks whether insertion in set was performed or the state was already in the set
					stack.push(reachableState);
		}
	}
	return lambdaClosure;
}

// Applies a transition on a given symbol for a set of states and returns the set of states that can be reached. 
// For NFAs with lambda-transitions, it means finding all the states that can be reached from the current states with a certain symbol, without including lambda-transitions
std::set<std::string> LambdaTransitionsAutomaton::FindReachableStates(const std::set<std::string>& states, const std::string& symbol) const {
	std::set<std::string> resultStates;
	for (const auto& state : states) {
		auto transitions = m_transition.find({ state, symbol });
		if (transitions != m_transition.end()) {
			const auto& nextStates = transitions->second;
			resultStates.insert(nextStates.begin(), nextStates.end());
		}
	}
	return resultStates;
}