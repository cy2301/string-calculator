#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

/*
returns precedence of the operator
input: c - a character representing an operator, e.g. '+'
output: the corresponding value of that operator's precedence, e.g. 2
throws: none
*/
int precedence (char c);

/*
checks if a char is an operator
input: c - any character
output: true if the character is one of the four operators, false otherwise
throws: none
*/
bool isOperator (char c);

/*
checks if the expression is valid
input: s - a string representing an expression, e.g. '(1+2)'
output: true if the expression is valid, false otherwise
throws: none.
*/
bool validate (std::string s);

/*
changes an infix expression to its postfix form
input: s - a string representing an expression, e.g. '(1+2)'
output: postfix form of the expression, e.g. '1 2 +
throws: none.
*/
std::string postfix (std::string s);

/*
standardizes input
input: s - a string representing an expression, e.g. '(1 + 2)'
output: the string expression without any spaces, e.g. '(1+2)'
throws: none.
*/
std::string standardize (std::string s);

/*
computes the result of an expression
input: s - a string representing an expression, e.g. '(1+2)'
output: the result of the arithmetic expression, e.g. '3'
throws: std::invalid_argument if the expression is incomplete, e.g. '(1+)'
*/
std::string calculate (std::string s);

#endif  // CALCULATOR_H
