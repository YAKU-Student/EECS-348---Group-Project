// Author: Caden LeCluyse

#include "test.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "ast.h"
#include "parser.h"

namespace Test {

static std::vector<std::string> get_expressions() {
    std::vector<std::string> expressions;
    std::ifstream input_file("expressions.txt");
    std::string current_expression;
    if (input_file.is_open()) {
        while (std::getline(input_file, current_expression)) {
            if (!current_expression.empty()) {
                expressions.push_back(current_expression);
            }
        }
    } else {
        std::cout << "Couldn't find expressions.txt for tests!\n";
    }

    return expressions;
}

void initiate_tests() {
    const std::vector<std::string> expressions = get_expressions();
    std::ofstream output_file("results.txt");

    for (const auto& expression : expressions) {
        try {
            Parser expression_parser;
            const std::string prefix_expression = expression_parser.create_prefix_expression(expression);
            std::unique_ptr<AST> syntax_tree = std::make_unique<AST>();
            syntax_tree->build_ast_prefix(prefix_expression);

            output_file << "Expression: " << expression << "\nResult:";
            if (syntax_tree->evaluate()) {
                output_file << "True!\n";
            } else {
                output_file << "False!\n";
            }
        } catch (const std::exception& error) {
            output_file << "Expression: " << expression << "\nResult:";
            output_file << error.what();
        }
    }
}

}  // namespace Test
