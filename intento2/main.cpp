//=============================================
// Proyecto Analizador aritmetico
// Archivo main.cpp
//=============================================
// Luis Diego Nuñez Mora B75473
// Deybin Garcia         B93171
// En este archivo se incluyen las funciones
// necesarias para lograr inicializar variables
// y realizar operaciones combinadas tanto con
// variables y constantes.
//===============================================
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

    std::cout << "Seleccione el tipo de operacion:\n";
    std::cout << "1. Resolver una ecuacion combinada\n";
    std::cout << "2. Resolver un sistema de ecuaciones (Metodo Gauss-Jordan)\n";
    std::cout << "Ingrese su opcion (1 o 2): ";
    std::cin >> option;
    std::cin.ignore(); // Ignorar el salto de línea después de la opción

    if (option == 1) {
        while (true) {
            std::cout << "Ingrese una declaracion o expresion: ";
            std::getline(std::cin, input);

            if (input == "exit") break;

            processInput(input, variables);
        }
    } else if (option == 2) {
        std::vector<double> coefficients(12);

    std::cout << "Ingrese los 12 coeficientes del sistema de ecuaciones en el orden a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3:" << std::endl;
    for (int i = 0; i < 12; ++i) {
        std::cout << "Ingrese el coeficiente " << (i + 1) << ": ";
        std::cin >> coefficients[i];
    }

    // Resolver el sistema de ecuaciones
    solveSystem(coefficients);
        /*
        test_gauss_jordan solver;
        solver.exec();*/
    } else {
        std::cerr << "Opcion no valida." << std::endl;
    }

    return 0;
}
