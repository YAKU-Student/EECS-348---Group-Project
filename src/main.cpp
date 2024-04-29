// Author: Caden LeCluyse

#include <iostream>
#include <string>

#include "ast.h"
#include "parser.h"

void evaluate_expression(const std::string& expression) {
    try {
        Parser expression_parser;
        const std::string prefix_expression = expression_parser.create_prefix_expression(expression);
        AST syntax_tree;
        syntax_tree.build_ast_prefix(prefix_expression);
        const bool result = syntax_tree.evaluate();
        std::cout << "Result: ";
        if (result) {
            std::cout << "True!\n\n";
        } else {
            std::cout << "False!\n\n";
        }
    } catch (const std::exception& error) {
        std::cerr << "\nError: " << error.what();
    }
}

[[nodiscard]] int program_loop() {
    std::string input_expression;
    while (true) {
        std::cout << "Please enter your boolean expression (enter exit, quit, or q to exit the program): ";
        // If the input fails for some reason
        if (!std::getline(std::cin, input_expression)) {
            std::cerr << "\nUnknown error ocurred in receiving input. Aborting...\n";
            return 1;
        } else if (input_expression.empty()) {
            std::cerr << "\nError: Empty expression received!\n";
            continue;
        } else if (input_expression == "quit" || input_expression == "exit" || input_expression == "q") {
            std::cout << "Exiting...\n" << std::endl;
            return 0;
        }
        evaluate_expression(input_expression);
    }
}

int main(int argc, char* const argv[]) {
    if (argc > 2) {
        std::cerr << "Expected 1 argument, received " << argc - 1
                  << ". Please pass in -c/--continuous, -v/--version, or an expression.\n";
        return 1;
    } else if (argc == 1) {
        std::cerr
            << "Expected an argument to be passed in. Either add the -c/--continuous flag, -v/--version flag, or an "
            << "expression to be evaluated.\n";
        return 1;
    }

    const std::string expression = argv[1];
    if (expression == "-c" || expression == "--continuous") {
        return program_loop();
    } else if (expression == "-v" || expression == "--version") {
        std::cout << "Version: " << PROGRAM_VERSION << std::endl;
        return 0;
    } else if (expression[0] == '-') {
        std::cerr << "\nError: " << expression << " is an invalid flag.\n";
        return 1;
    }
    evaluate_expression(expression);

    return 0;
}
