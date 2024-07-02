//=============================================
// Proyecto Analizador aritmetico
// Archivo functions.h
//=============================================
// Luis Diego Nuñez Mora B75473
// Deybin Garcia         B93171
// En este archivo se incluyen las funciones
// necesarias para lograr inicializar variables
// y realizar operaciones combinadas tanto con
// variables y constantes.
//===============================================
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
// Librerias para dar soporte
#include <vector>
#include <string>
#include <map>

// Funciones para resolver ecuaciones combinadas
bool isValidVariableName(const std::string& name);
std::string removeSpacesAroundEquals(const std::string& input);
int getPrecedence(char op);
bool isFunction(const std::string& token);
std::string infixToPostfix(const std::string& infix);
double evaluatePostfix(const std::string& postfix, const std::map<std::string, double>& variables);
void processInput(const std::string& input, std::map<std::string, double>& variables);


#include"functions.cpp"

#endif // FUNCTIONS_H_INCLUDED
