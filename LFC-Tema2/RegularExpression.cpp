#include "RegularExpression.h"
#include <stack>

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
	return VerifyNonEmpty() && VerifyValidCharAndOperators() && VerifyValidParentheses();
}

bool RegularExpression::VerifyNonEmpty() const {
	if (m_expression.empty()) {
		std::cout << "Invalid regular expression: empty expression!\n";
		return false;
	}
	return true;
}

bool RegularExpression::VerifyValidCharAndOperators() const {
	for (char ch : m_expression) {
		if (!(std::isalnum(ch) || ch == '|' || ch == '.' || ch == '*' || ch == '(' || ch == ')')) {
			std::cout << "Invalid regular expression: invalid characters!\n";
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