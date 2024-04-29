#include "parser.h"

#include <algorithm>
#include <cctype>
#include <stack>
#include <stdexcept>
#include <string>

bool Parser::is_operand(const char token) { return (token == 'T' || token == 'F'); }

bool Parser::is_operator(const char token) {
    return (token == '&' || token == '|' || token == '!' || token == '@' || token == '$');
}

std::string Parser::create_prefix_expression(const std::string& infix_expression) {
    std::string prefix_expression;
    for (auto itr = infix_expression.rbegin(); itr != infix_expression.rend(); itr++) {
        // Ignore white space
        if (isspace(*itr)) {
            continue;
        }

        // Grab the current token
        // If the token is an operand, simply add it to the string
        // if the token is an operator or a closing parentheses, add it to the stack
        // If the token is an open parentheses, pop from the stack and add to the string until a closing parentheses is
        // found
        current_token = *itr;
        if (is_operand(current_token)) {
            prefix_expression.push_back(current_token);
            continue;
        } else if (is_operator(current_token) || current_token == ')') {
            operator_stack.push(current_token);
            continue;
        } else if (current_token == '(') {
            if (*(itr - 1) == ')') {
                throw(std::runtime_error("Empty parentheses detected!\n"));
            }
            while (operator_stack.top() != ')') {
                prefix_expression.push_back(operator_stack.top());
                operator_stack.pop();
            }
            if (operator_stack.empty()) {
                throw(std::runtime_error("Mismatched parentheses detected!\n"));
            } else {
                operator_stack.pop();
                continue;
            }
        }
    }

    while (!operator_stack.empty()) {
        prefix_expression.push_back(operator_stack.top());
        operator_stack.pop();
    }
    std::ranges::reverse(prefix_expression);
    return prefix_expression;
}
