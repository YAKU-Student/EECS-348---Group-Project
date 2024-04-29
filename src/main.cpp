// Author: Caden LeCluyse

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "ast.h"
#include "parser.h"

void evaluate_expression(const std::string& expression, auto& history) {
    static Parser expression_parser;
    try {
        // Create the prefix expression and then build the tree
        const std::string prefix_expression = expression_parser.create_prefix_expression(expression);
        AST syntax_tree;
        syntax_tree.build_ast_prefix(prefix_expression);

        std::cout << "Result: ";
        if (syntax_tree.evaluate()) {
            std::cout << "True!\n\n";
            history.emplace_back(std::make_pair(expression, "True!"));
        } else {
            std::cout << "False!\n\n";
            history.emplace_back(std::make_pair(expression, "False!"));
        }
    } catch (const std::exception& error) {
        std::cerr << "\nError: " << error.what();
    }
}

void print_history(const auto& history) {
    std::ranges::for_each(history, [](const auto& expression_result) {
        std::cout << "Expression: " << expression_result.first << "\nResult: " << expression_result.second << "\n\n";
    });
}

[[nodiscard]] int program_loop(auto& program_history) {
    std::string input_expression;

    while (true) {
        std::cout << "Please enter your boolean expression, or enter history to see all prior evaluated expressions "
                  << "(enter exit, quit, or q to exit the program): ";
        // If the input fails for some reason
        if (!std::getline(std::cin, input_expression)) {
            std::cerr << "\nUnknown error ocurred in receiving input. Aborting...\n";
            return 1;
        } else if (input_expression == "history") {
            if (program_history.empty()) {
                std::cerr << "You haven't evaluated any expressions yet!\n\n";
            } else {
                print_history(program_history);
            }
            continue;
        } else if (input_expression.empty()) {
            std::cerr << "\nError: Empty expression received!\n";
            continue;
        } else if (input_expression == "quit" || input_expression == "exit" || input_expression == "q") {
            std::cout << "Exiting...\n" << std::endl;
            return 0;
        }

        evaluate_expression(input_expression, program_history);
    }
}

int main(int argc, char* const argv[]) {
    if (argc > 2) {
        std::cerr << "Expected 1 argument, received " << argc - 1
                  << ". Please pass in -c/--continuous, -v/--version, or an expression.\n"
                  << "Make sure to wrap the expression in quotes.\n\n";
        return 1;
    } else if (argc == 1) {
        std::cerr
            << "Expected an argument to be passed in. Either add the -c/--continuous flag, -v/--version flag, or an "
            << "expression to be evaluated.\n\n";
        return 1;
    }

    const std::string expression = argv[1];
    std::vector<std::pair<std::string, std::string> > program_history;
    if (expression == "-c" || expression == "--continuous") {
        return program_loop(program_history);
    } else if (expression == "-v" || expression == "--version") {
        std::cout << "Version: " << PROGRAM_VERSION << std::endl;
        return 0;
    } else if (expression[0] == '-') {
        std::cerr << "\nError: " << expression << " is an invalid flag.\n";
        return 1;
    }

    // Unnecessary adding to the program history here, but I didn't feel the need to function overload as its a
    // completely negligable performance hit
    evaluate_expression(expression, program_history);

    return 0;
}
