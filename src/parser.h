// Author: Caden LeCluyse

#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <string>

class Parser {
   public:
    std::string create_prefix_expression(const std::string& infix_expression);

   private:
    bool is_operand(const char token);
    bool is_operator(const char token);
    std::stack<char> operator_stack;
    char current_token;
};

#endif
