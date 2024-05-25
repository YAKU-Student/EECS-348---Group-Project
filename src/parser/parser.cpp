// Author: Caden LeCluyse

#include "parser.h"

#include <algorithm>
#include <cctype>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>

#include "error/error.h"
#include "types/types.h"

void Parser::parse(const std::string_view infix_expression, std::string& prefix_expression) {
    // Traverse the string in reverse
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
        m_current_token = *itr;

        // Check for various errors
        Error::error_checker(m_current_token, m_previous_token);

        if (Types::isoperand(m_current_token)) {
            prefix_expression.push_back(m_current_token);
        } else if (Types::isnot(m_current_token) || Types::isoperator(m_current_token) || m_current_token == ')') {
            m_operator_stack.push(m_current_token);
        } else if (m_current_token == '(') {
            while (!m_operator_stack.empty() && m_operator_stack.top() != ')') {
                prefix_expression.push_back(m_operator_stack.top());
                m_operator_stack.pop();
            }

            // Pop the closing parentheses off the stack
            if (!m_operator_stack.empty()) {
                m_operator_stack.pop();
            } else {
                throw std::runtime_error("Missing closing parentheses!\n\n");
            }
        } else {
            Error::throw_invalid_character_error(m_current_token);
        }
        m_previous_token = m_current_token;
    }
}

void Parser::clear_stack(std::string& prefix_expression) {
    while (!m_operator_stack.empty()) {
        if (m_operator_stack.top() == ')') {
            while (!m_operator_stack.empty()) {
                m_operator_stack.pop();
            }
            throw(std::runtime_error("Missing open parentheses!\n\n"));
        }
        prefix_expression.push_back(m_operator_stack.top());
        m_operator_stack.pop();
    }
}

[[nodiscard]] std::string Parser::create_prefix_expression(const std::string_view infix_expression) {
    std::string prefix_expression;
    m_current_token = '\0';
    m_previous_token = '\0';

    // Check if the string is only white space
    if (std::ranges::all_of(infix_expression, isspace)) {
        throw std::runtime_error("Expression contains only spaces!\n\n");
    }
    Error::check_leading(infix_expression);
    Error::check_trailing(infix_expression);

    parse(infix_expression, prefix_expression);
    clear_stack(prefix_expression);

    std::ranges::reverse(prefix_expression);
    return prefix_expression;
}
