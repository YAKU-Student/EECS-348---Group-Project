#include "parser.h"

#include <algorithm>
#include <cctype>
#include <stack>
#include <stdexcept>
#include <string>

[[noreturn]] void Parser::throw_invalid_character_error(const char token) {
    if (isalnum(token)) {
        throw std::runtime_error("Expected T or F, received: " + std::string(1, token) + "\n\n");
    }
    throw std::runtime_error("Expected &, |, !, @, $, received: " + std::string(1, token) + "\n\n");
}

[[nodiscard]] bool Parser::is_operand(const char token) const noexcept { return (token == 'T' || token == 'F'); }

[[nodiscard]] bool Parser::is_operator(const char token) const noexcept {
    return (token == '&' || token == '|' || token == '!' || token == '@' || token == '$');
}

[[nodiscard]] std::string Parser::create_prefix_expression(const std::string& infix_expression) {
    std::string prefix_expression;
    int open_parentheses = 0;
    int closed_parentheses = 0;

    // Instead of reversing the string, I can simply just traverse in reverse
    for (auto itr = infix_expression.rbegin(); itr != infix_expression.rend(); ++itr) {
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

        // Check for empty parentheses
        if (current_token == '(' && previous_token == ')') {
            throw std::runtime_error("Empty parentheses detected!\n");
        }

        if (is_operand(current_token)) {
            prefix_expression.push_back(current_token);
        } else if (is_operator(current_token) || current_token == ')') {
            if (current_token == ')') {
                closed_parentheses++;
            }
            operator_stack.push(current_token);
        } else if (current_token == '(') {
            open_parentheses++;
            // Traverse backwards towards the end of the string to check for errors
            while (!operator_stack.empty() && operator_stack.top() != ')') {
                prefix_expression.push_back(operator_stack.top());
                operator_stack.pop();
            }
            if (!operator_stack.empty()) {
                operator_stack.pop();
            }
        } else {
            throw_invalid_character_error(current_token);
        }
        previous_token = current_token;
    }
    if (open_parentheses > closed_parentheses) {
        throw std::runtime_error("Missing closing parentheses!\n");
    } else if (open_parentheses < closed_parentheses) {
        throw std::runtime_error("Missing open parentheses!\n");
    }

    while (!operator_stack.empty()) {
        prefix_expression.push_back(operator_stack.top());
        operator_stack.pop();
    }
    std::ranges::reverse(prefix_expression);
    return prefix_expression;
}
