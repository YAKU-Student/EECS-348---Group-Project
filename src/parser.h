// Author: Caden LeCluyse

#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <string>

class Parser {
   public:
    [[nodiscard]] std::string create_prefix_expression(const std::string& infix_expression);

   private:
    [[nodiscard]] bool is_operand(const char token) const noexcept;
    [[nodiscard]] bool is_operator(const char token) const noexcept;
    [[noreturn]] void throw_invalid_character_error(const char token);
    void check_parentheses(std::string::const_reverse_iterator itr, std::string::const_reverse_iterator string_end);
    std::stack<char> operator_stack;
    char current_token;
    char previous_token;
};

#endif