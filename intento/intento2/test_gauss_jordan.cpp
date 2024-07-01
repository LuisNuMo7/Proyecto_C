#include "test_gauss_jordan.h"
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

// Funcion para realizar los calculos de gauss_jordan
void test_gauss_jordan::gauss_jordan_Solucion(double matrix[3][4]) {
    int n = 3;

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

// Funcion exec sobreescrita para la clase test_gauss_jordan
void test_gauss_jordan::exec() {
    cout << "Resolviendo sistema de ecuaciones usando el método Gauss-Jordan." << endl;

    double matrix[3][4] = {{2, 3, -1, 1},
                           {4, 1, 2, 2},
                           {-2, 2, 3, 3}};

    gauss_jordan_Solucion(matrix);

    double x = matrix[0][3];
    double y = matrix[1][3];
    double z = matrix[2][3];

    cout << "Solución: x = " << x << ", y = " << y << ", z = " << z << endl;
}
