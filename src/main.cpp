#include <iostream>

[[nodiscard]] int programLoop() {
    std::string inputExpression;
    while (true) {
        std::cout << "Please enter your boolean expression (enter exit, quit, or q to exit the program): ";
        // If the input fails for some reason
        if (!std::getline(std::cin, inputExpression)) {
            std::cerr << "Unknown error ocurred in recieving input. Aborting...\n";
            return 1;
        } else if (inputExpression == "quit" || inputExpression == "exit" || inputExpression == "q") {
            std::cout << "Exiting..." << std::endl;
            return 0;
        }
        // doinput(expression);
    }
}

int main(int argc, char* const argv[]) {
    if (argc > 2) {
        std::cerr << "Expected 1 argument, recieved " << argc - 1
                  << ". Please pass in -c/--continuous or an expression.\n";
        return 1;
    } else if (argc == 1) {
        std::cerr << "Expected an argument to be passed in. Either add the flag -c/--continuous or an expression to be "
                  << "evaluated.\n";
        return 1;
    }

    const std::string expression = argv[1];
    if (expression == "-c" || expression == "--continuous") {
        return programLoop();
    } else if (expression[0] == '-') {
        std::cerr << "Error:\n\t" << expression << " is an invalid flag.\n";
        return 1;
    }

    // Placeholder for whatever the actual function is
    // doInput(expression);

    return 0;
}
