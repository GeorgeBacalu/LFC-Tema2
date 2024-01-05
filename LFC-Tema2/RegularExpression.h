#pragma once

#include <iostream>
#include <string>

class RegularExpression {
	std::string m_expression;

	bool VerifyNonEmpty() const;
	bool VerifyValidCharAndOperators() const;
	bool VerifyValidParentheses() const;
public:
	RegularExpression();
	RegularExpression(const std::string& expression);
	friend std::istream& operator>>(std::istream& in, RegularExpression& RegularExpression);
	friend std::ostream& operator<<(std::ostream& out, const RegularExpression& RegularExpression);

	const std::string& GetExpression() const;
	void SetExpression(const std::string& expression);

	bool VerifyExpression() const;
};