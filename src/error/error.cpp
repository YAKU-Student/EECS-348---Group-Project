// Author: Caden LeCluyse

#include "error.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <string_view>

namespace Error {

[[nodiscard]] static bool is_operand(const char token) noexcept { return (token == 'T' || token == 'F'); }

[[nodiscard]] static bool is_operator(const char token) noexcept {
    return (token == '&' || token == '|' || token == '@' || token == '$');
}

[[nodiscard]] static bool is_not(const char token) noexcept { return token == '!'; }

void check_leading(const std::string_view infix_expression) {
    for (const auto i : infix_expression) {
        if (isspace(i)) {
            continue;
        } else if (is_operator(i)) {
            throw std::runtime_error("Expression begins with an operator!\n\n");
        } else if (i == ')') {
            throw std::runtime_error("Expression begins with closed parentheses!\n\n");
        } else {
            break;
        }
    }
}

void check_trailing(const std::string_view infix_expression) {
    // I originally was just checking for the last value, but then I realized white space messed it all up
    for (auto itr = infix_expression.rbegin(); itr != infix_expression.rend(); ++itr) {
        if (isspace(*itr)) {
            continue;
        } else if (is_not(*itr)) {
            throw std::runtime_error("Expression ends with NOT!\n\n");
        } else if (is_operator(*itr)) {
            throw std::runtime_error("Expression ends with an operator!\n\n");
        } else if (*itr == '(') {
            throw std::runtime_error("Expression ends with open parentheses!\n\n");
        } else {
            break;
        }
    }
}

static void check_missing_parentheses(const char current_token, const char previous_token) {
    if (current_token == '(' && previous_token == ')') {
        throw std::runtime_error("Empty parentheses detected!\n\n");
    }
}

static void check_consecutive_operands(const char current_token, const char previous_token) {
    if (is_operator(current_token) && is_operator(previous_token)) {
        throw std::runtime_error("Two consecutive operators detected: " + std::string(1, current_token) + " and " +
                                 std::string(1, previous_token) + "\n\n");
    }
}

static void check_consecutive_operators(const char current_token, const char previous_token) {
    if (is_operand(current_token) && is_operand(previous_token)) {
        throw std::runtime_error("Two consecutive operands detected: " + std::string(1, current_token) + " and " +
                                 std::string(1, previous_token) + "\n\n");
    }
}

static void check_not_after_value(const char current_token, const char previous_token) {
    if (is_not(current_token) && (is_operator(previous_token) || previous_token == ')')) {
        throw std::runtime_error("NOT applied after value!\n\n");
    }
}

static void check_missing_operator(const char current_token, const char previous_token) {
    if ((current_token == ')' && (is_not(previous_token) || is_operand(previous_token))) ||
        (is_operand(current_token) && (previous_token == '(' || is_not(previous_token))) ||
        (current_token == ')' && previous_token == '(')) {
        throw std::runtime_error("Missing operator!\n\n");
    }
}

static void check_missing_operand(const char current_token, const char previous_token) {
    if ((current_token == '(' && is_operator(previous_token)) ||
        (is_operator(current_token) && previous_token == ')')) {
        throw std::runtime_error("Missing an operand!\n\n");
    }
}

void error_checker(const char current_token, const char previous_token) {
    check_missing_parentheses(current_token, previous_token);
    check_consecutive_operands(current_token, previous_token);
    check_consecutive_operators(current_token, previous_token);
    check_not_after_value(current_token, previous_token);
    check_missing_operator(current_token, previous_token);
    check_missing_operand(current_token, previous_token);
}

[[noreturn]] void throw_invalid_character_error(const char token) {
    if (isalnum(token)) {
        throw std::runtime_error("Expected T or F, received: " + std::string(1, token) + "\n\n");
    } else if (token == ']' || token == '[') {
        throw std::runtime_error("Invalid use of brackets detected! Just use parentheses please.\n\n");
    }
    throw std::runtime_error("Expected &, |, !, @, $, received: " + std::string(1, token) + "\n\n");
}

}  // namespace Error
