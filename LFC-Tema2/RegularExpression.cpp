#include "RegularExpression.h"

RegularExpression::RegularExpression() : m_expression{} {}

RegularExpression::RegularExpression(const std::string& expression) : m_expression{ expression } {}

const std::string& RegularExpression::GetExpression() const { return m_expression; }

void RegularExpression::SetExpression(const std::string& expression) { m_expression = expression; }

std::istream& operator>>(std::istream& in, RegularExpression& RegularExpression) {
	return in >> RegularExpression.m_expression;
}

std::ostream& operator<<(std::ostream& out, const RegularExpression& RegularExpression) {
	return out << RegularExpression.m_expression;
}

bool RegularExpression::VerifyExpression() const {
	return VerifyNonEmpty() && VerifyValidOperandsAndOperators() && VerifyValidParentheses() && VerifyOperatorArity() && VerifyNonConsecutiveOperands();
}

bool RegularExpression::VerifyNonEmpty() const {
	if (m_expression.empty()) {
		std::cout << "Invalid regular expression: empty expression!\n";
		return false;
	}
	return true;
}

bool RegularExpression::VerifyValidOperandsAndOperators() const {
	for (char ch : m_expression) {
		if (!std::isalnum(ch) && !IsOperator(ch)) {
			std::cout << "Invalid regular expression: invalid characters or operators!\n";
			return false;
		}
	}
	return true;
}

bool RegularExpression::VerifyValidParentheses() const {
	std::stack<char> parentheses;
	for (char ch : m_expression) {
		if (ch == '(')
			parentheses.push(ch);
		else if (ch == ')') {
			if (parentheses.empty()) {
				std::cout << "Invalid regular expression: invalid parentheses!\n";
				return false;
			}
			parentheses.pop();
		}
	}
	return parentheses.empty();
}

bool RegularExpression::VerifyOperatorArity() const {
	for (size_t i = 0; i < m_expression.length(); ++i) {
		char currentChar = m_expression[i];
		if (currentChar == '*') {
			if (i == 0 || !IsValidLeftOperand(m_expression[i - 1]) || (i != m_expression.length() - 1 && !IsValidRightOperandForStar(m_expression[i + 1]))) {
				std::cout << "Invalid regular expression: invalid arity for '*' operator!\n";
				return false;
			}
		}
		else if (currentChar == '.' || currentChar == '|') {
			if (i == 0 || i == m_expression.length() - 1 || !IsValidLeftOperand(m_expression[i - 1]) || !IsValidRightOperand(m_expression[i + 1])) {
				std::cout << "Invalid regular expression: invalid arity for binary operator!\n";
				return false;
			}
		}
	}
	return true;
}

bool RegularExpression::VerifyNonConsecutiveOperands() const {
	for (size_t i = 0; i < m_expression.length() - 1; ++i)
		if (std::isalnum(m_expression[i]) && std::isalnum(m_expression[i + 1])) {
			std::cout << "Invalid regular expression: consecutive operands!\n";
			return false;
		}
	return true;
}

bool RegularExpression::IsOperator(char ch) const {
	return ch == '|' || ch == '.' || ch == '*' || ch == '(' || ch == ')';
}

bool RegularExpression::IsValidLeftOperand(char ch) const {
	return std::isalnum(ch) || ch == ')' || ch == '*';
}

bool RegularExpression::IsValidRightOperand(char ch) const {
	return std::isalnum(ch) || ch == '(';
}

bool RegularExpression::IsValidRightOperandForStar(char ch) const {
	return ch == '|' || ch == '.';
}

int RegularExpression::GetPriority(char op) const {
	switch (op) {
	case '|': return 1;
	case '.': return 2;
	case '*': return 3;
	default: return 0;
	}
}

std::string RegularExpression::ConvertToPostfixForm() const {
	if (!VerifyExpression()) {
		std::cout << "Invalid regular expression: cannot convert to postfix form!\n";
		return "";
	}
	std::stack<char> operators, postfixForm;
	for (char current : m_expression) {
		if (isspace(current))
			continue;
		if (std::isalnum(current))
			postfixForm.push(current);
		else if (current == '(')
			operators.push(current);
		else if (current == ')') {
			while (!operators.empty() && operators.top() != '(') {
				postfixForm.push(operators.top());
				operators.pop();
			}
			if (!operators.empty())
				operators.pop();
		}
		else {
			while (!operators.empty() && GetPriority(operators.top()) >= GetPriority(current)) {
				postfixForm.push(operators.top());
				operators.pop();
			}
			operators.push(current);
		}
	}
	while (!operators.empty()) {
		postfixForm.push(operators.top());
		operators.pop();
	}
	std::string result;
	while (!postfixForm.empty()) {
		result += postfixForm.top();
		postfixForm.pop();
	}
	std::reverse(result.begin(), result.end());
	return result;
}

LambdaTransitionsAutomaton RegularExpression::convertToNFA(const std::string& postfixForm) const {
	std::stack< LambdaTransitionsAutomaton> stackAutomatons;
	int nrStates = 0;
	for (char ch : postfixForm) {
		if (std::isalnum(ch))
			stackAutomatons.push(LambdaTransitionsAutomaton().CreateBasicAutomaton(ch, nrStates));
		else if (ch == '|') {
			LambdaTransitionsAutomaton B = stackAutomatons.top(); stackAutomatons.pop();
			LambdaTransitionsAutomaton A = stackAutomatons.top(); stackAutomatons.pop();
			stackAutomatons.push(LambdaTransitionsAutomaton().Union(A, B, nrStates));
		}
		else if (ch == '.') {
			LambdaTransitionsAutomaton B = stackAutomatons.top(); stackAutomatons.pop();
			LambdaTransitionsAutomaton A = stackAutomatons.top(); stackAutomatons.pop();
			stackAutomatons.push(LambdaTransitionsAutomaton().Concatenate(A, B, nrStates));
		}
		else if (ch == '*') {
			LambdaTransitionsAutomaton A = stackAutomatons.top();
			stackAutomatons.push(LambdaTransitionsAutomaton().KleeneClosure(A, nrStates));
		}
	}
	return stackAutomatons.top();
}

DeterministicFiniteAutomaton RegularExpression::convertToDFA(const LambdaTransitionsAutomaton& nfa) const {
	return DeterministicFiniteAutomaton();
}