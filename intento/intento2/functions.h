#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <vector>
#include <string>
#include <map>

// Funciones para resolver ecuaciones combinadas
bool isValidVariableName(const std::string& name);
std::string removeSpacesAroundEquals(const std::string& input);
int getPrecedence(char op);
std::string infixToPostfix(const std::string& infix);
double evaluatePostfix(const std::string& postfix, const std::map<std::string, double>& variables);
void processInput(const std::string& input, std::map<std::string, double>& variables);

// Clase para resolver sistemas de ecuaciones usando Gauss-Jordan
/*class test_gauss_jordan {
public:
    void exec();
private:
    void gauss_jordan_Solucion(double matrix[3][4]);
};*/



#include"functions.cpp"

#endif // FUNCTIONS_H_INCLUDED
