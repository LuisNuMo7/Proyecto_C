#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "functions.h"
#include "test_gauss_jordan.h"

int main() {
    std::map<std::string, double> variables;
    std::string input;
    int option;

    std::cout << "Seleccione el tipo de operación:\n";
    std::cout << "1. Resolver una ecuación combinada\n";
    std::cout << "2. Resolver un sistema de ecuaciones (Método Gauss-Jordan)\n";
    std::cout << "Ingrese su opción (1 o 2): ";
    std::cin >> option;
    std::cin.ignore(); // Ignorar el salto de línea después de la opción

    if (option == 1) {
        while (true) {
            std::cout << "Ingrese una declaración o expresión: ";
            std::getline(std::cin, input);

            if (input == "exit") break;

            processInput(input, variables);
        }
    } else if (option == 2) {
        test_gauss_jordan solver;
        solver.exec();
    } else {
        std::cerr << "Opción no válida." << std::endl;
    }

    return 0;
}
