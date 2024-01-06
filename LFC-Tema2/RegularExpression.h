#pragma once

#include <iostream>
#include <string>

class RegularExpression {
	std::string m_expression;

	bool VerifyNonEmpty() const;
	bool VerifyValidOperandsAndOperators() const;
	bool VerifyValidParentheses() const;
	bool VerifyOperatorArity() const;
	bool VerifyNonConsecutiveOperands() const;

	bool IsOperator(char ch) const;
	bool IsValidLeftOperand(char ch) const;
	bool IsValidRightOperand(char ch) const;
	bool IsValidRightOperandForStar(char ch) const;
	int GetPriority(char op) const;
public:
	RegularExpression();
	RegularExpression(const std::string& expression);
	friend std::istream& operator>>(std::istream& in, RegularExpression& RegularExpression);
	friend std::ostream& operator<<(std::ostream& out, const RegularExpression& RegularExpression);

	const std::string& GetExpression() const;
	void SetExpression(const std::string& expression);

	bool VerifyExpression() const;
	std::string ConvertToPostfix() const;
};