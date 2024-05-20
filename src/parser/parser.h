// Author: Caden LeCluyse

#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <string>
#include <string_view>

class Parser {
   public:
    [[nodiscard]] std::string create_prefix_expression(const std::string_view infix_expression);

   private:
    [[nodiscard]] bool is_operand(const auto token) const noexcept;
    [[nodiscard]] bool is_operator(const auto token) const noexcept;
    [[nodiscard]] bool is_not(const auto token) const noexcept;
    void parse(const std::string_view infix_expression, std::string& prefix_expression);
    void clear_stack(std::string& prefix_expression);
    std::stack<char> m_operator_stack;
    char m_current_token;
    char m_previous_token;
};

#endif
