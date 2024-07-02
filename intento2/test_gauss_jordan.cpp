//=============================================
// Proyecto Analizador aritmetico
// Archivo test_gauss_jordan.cpp
//=============================================
// Luis Diego Nuñez Mora B75473
// Deybin Garcia         B93171
// En este archivo se incluyen las funciones
// necesarias para lograr inicializar variables
// y realizar operaciones combinadas tanto con
// variables y constantes.
//===============================================
#include "test_gauss_jordan.h"
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;


// Funcion para realizar los calculos de gauss_jordan
void gauss_jordan_Solucion(std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();

    for (int i = 0; i < n; i++) {
        double maxElement = abs(matrix[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(matrix[k][i]) > maxElement) {
                maxElement = abs(matrix[k][i]);
                maxRow = k;
            }
        }

        for (int k = i; k < n + 1; k++) {
            swap(matrix[maxRow][k], matrix[i][k]);
        }

        for (int k = i + 1; k < n; k++) {
            double c = -matrix[k][i] / matrix[i][i];
            for (int j = i; j < n + 1; j++) {
                if (i == j) {
                    matrix[k][j] = 0;
                } else {
                    matrix[k][j] += c * matrix[i][j];
                }
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        matrix[i][n] /= matrix[i][i];
        matrix[i][i] = 1;

        for (int k = i - 1; k >= 0; k--) {
            double c = -matrix[k][i];
            matrix[k][n] += c * matrix[i][n];
            matrix[k][i] = 0;
        }
    }
}
void solveSystem(const std::vector<double>& coefficients) {
    // Validar que se ingresen exactamente 12 coeficientes
    if (coefficients.size() != 12) {
        std::cerr << "Error: Se deben ingresar exactamente 12 números para definir el sistema de ecuaciones." << std::endl;
        return;
    }

    // Construir la matriz de coeficientes y términos independientes
    std::vector<std::vector<double>> matrix(3, std::vector<double>(4));
    int idx = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = coefficients[idx++];
        }
    }

    // Mostrar la matriz inicial
    std::cout << "Matriz inicial:" << std::endl;
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Resolver el sistema de ecuaciones usando Gauss-Jordan
    gauss_jordan_Solucion(matrix);

    // Mostrar la solución del sistema de ecuaciones
    std::cout << "Solución del sistema de ecuaciones:" << std::endl;
    char variable = 'a';
    for (const auto& row : matrix) {
        std::cout << static_cast<char>(variable++) << " = " << row.back() << std::endl;
    }
}

