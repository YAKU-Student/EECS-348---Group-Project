// Author: Caden LeCluyse

#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <string>

class Parser {
   public:
    [[nodiscard]] std::string create_prefix_expression(const std::string_view infix_expression);

   private:
    [[nodiscard]] bool is_operand(const auto token) const noexcept;
    [[nodiscard]] bool is_operator(const auto token) const noexcept;
    [[nodiscard]] bool is_not(const auto token) const noexcept;
    std::stack<char> m_operator_stack;
    char m_current_token;
    char m_previous_token;
};

#endif
