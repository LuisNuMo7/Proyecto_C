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

    std::cout << "Seleccione el tipo de operaci�n:\n";
    std::cout << "1. Resolver una ecuaci�n combinada\n";
    std::cout << "2. Resolver un sistema de ecuaciones (M�todo Gauss-Jordan)\n";
    std::cout << "Ingrese su opci�n (1 o 2): ";
    std::cin >> option;
    std::cin.ignore(); // Ignorar el salto de l�nea despu�s de la opci�n

    if (option == 1) {
        while (true) {
            std::cout << "Ingrese una declaraci�n o expresi�n: ";
            std::getline(std::cin, input);

            if (input == "exit") break;

            processInput(input, variables);
        }
    } else if (option == 2) {
        test_gauss_jordan solver;
        solver.exec();
    } else {
        std::cerr << "Opci�n no v�lida." << std::endl;
    }

    return 0;
}
