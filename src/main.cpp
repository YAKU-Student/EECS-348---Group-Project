#include <iostream>
#include <string>

#include "ast.h"
#include "parser.h"

bool evaluate_expression(const std::string& expression) {
    try {
        Parser expression_parser;
        AST syntax_tree;
        std::cout << "\n\nInput: " << expression;
        std::cout << "\n\nPrefix: " << expression_parser.create_prefix_expression(expression);
        std::cout << "\n\n";
        syntax_tree.build_ast_prefix(expression_parser.create_prefix_expression(expression));
        const bool result = syntax_tree.evaluate();
        std::cout << "Result: ";
        if (result) {
            std::cout << "True!\n\n";
        } else {
            std::cout << "False!\n\n";
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what();
        return false;
    }
    return true;
}

[[nodiscard]] int program_loop() {
    std::string input_expression;
    while (true) {
        std::cout << "Please enter your boolean expression (enter exit, quit, or q to exit the program): ";
        // If the input fails for some reason
        if (!std::getline(std::cin, input_expression)) {
            std::cerr << "Unknown error ocurred in recieving input. Aborting...\n";
            return 1;
        } else if (input_expression.empty()) {
            std::cerr << "Error: Empty expression recieved!\n";
            return 1;
        } else if (input_expression == "quit" || input_expression == "exit" || input_expression == "q") {
            std::cout << "Exiting..." << std::endl;
            return 0;
        }
        if (!evaluate_expression(input_expression)) {
            return 1;
        }
    }
}

int main(int argc, char* const argv[]) {
    if (argc > 2) {
        std::cerr << "Expected 1 argument, recieved " << argc - 1
                  << ". Please pass in -c/--continuous, -v/--version, or an expression.\n";
        return 1;
    } else if (argc == 1) {
        std::cerr
            << "Expected an argument to be passed in. Either add the -c/--continuous flag, -v/--version flag, or an "
            << "expression to be evaluated.\n";
        return 1;
    }

    // Potentially might not be const, depending how we actually parse the input
    const std::string expression = argv[1];
    if (expression == "-c" || expression == "--continuous") {
        return program_loop();
    } else if (expression == "-v" || expression == "--version") {
        std::cout << "Version: " << PROGRAM_VERSION << std::endl;
        return 0;
    } else if (expression[0] == '-') {
        std::cerr << "Error: " << expression << " is an invalid flag.\n";
        return 1;
    }

    // Placeholder for whatever the actual function is
    // doInput(expression);

    return 0;
}
