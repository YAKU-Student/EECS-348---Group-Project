// Author: Caden LeCluyse

#ifndef ERROR_H
#define ERROR_H

#include <string_view>

namespace Error {

void check_leading(const std::string_view infix_expression);
void check_trailing(const std::string_view infix_expression);
static void check_missing_parentheses(const char current_token, const char previous_token);
static void check_consecutive_operands(const char current_token, const char previous_token);
static void check_consecutive_operators(const char current_token, const char previous_token);
static void check_not_after_value(const char current_token, const char previous_token);
static void check_missing_operator(const char current_token, const char previous_token);
static void check_missing_operand(const char current_token, const char previous_token);
void error_checker(const char current_token, const char previous_token);
[[noreturn]] void throw_invalid_character_error(const char token);

}  // namespace Error

#endif
