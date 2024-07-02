//=============================================
// Proyecto Analizador aritmetico
// Archivo functions.cpp
//=============================================
// Luis Diego Nuñez Mora B75473
// Deybin Garcia         B93171
// En este archivo se incluyen las funciones
// necesarias para lograr inicializar variables
// y realizar operaciones combinadas tanto con
// variables y constantes.
//===============================================
#include "functions.h"
#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <sstream>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <regex>
#include <unordered_map>

//==================================
// Funcion para validar que el nombre que se ingresa a las variables sea correcto
// Las variables deben empezar con el caracter $ y tener un maximo de 20 letras
// a excepcion si se incluye el caracter _ que se alarga a un maximo de 20 letras
// y el caracter.
// Utiliza regex para validar el formato correcto
bool isValidVariableName(const std::string& name) {
    const std::regex varPattern(R"(^\$[a-zA-Z]{1,10}(_[a-zA-Z]{1,10})?$|^\$[a-zA-Z]{1,20}$)");
    return std::regex_match(name, varPattern);
}

//==============================================
// Esta funcion se utiliza para eliminar espacios en blanco que causan fallas en el algoritmo
// al momento de inicializar variables, por ejemplo, $var = 9, dió problemas mientras, $var=9 no
// por lo tanto, se usa para obtener una uniformidad en las variantes para escribir variables
std::string removeSpacesAroundEquals(const std::string& input) {
    const std::regex spacePattern(R"(\s*=\s*)");
    return std::regex_replace(input, spacePattern, "=");
}

//==================================
// Función para retornar el nivel de precedencia de un simbolo operador
int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        case '(': return 0;
    }
    return -1;
}

//===============================================
// Funcion para retornar una funcion unaria en caso de ser invocada
bool isFunction(const std::string& token) {
    static const std::unordered_map<std::string, int> functions = {
        {"sin", 1}, {"cos", 1}, {"tan", 1},
        {"log", 1}, {"ln", 1}, {"exp", 1}
    };
    return functions.find(token) != functions.end();
}

//================================================
// Funcion para convertir una cadena de caracteres de un formato infix
// a postfix
std::string infixToPostfix(const std::string& infix) {
    std::stack<std::string> stack;
    std::stringstream postfix;
    bool lastWasOperand = false;
    std::string token;

    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];

        if (isspace(ch)) {
            continue;
        }

        if (isalnum(ch) || ch == '$' || (ch == '.' && !token.empty() && isdigit(token.back()))) {
            token += ch;
            lastWasOperand = true;
        } else {
            if (!token.empty()) {
                postfix << token << ' ';
                token.clear();
                lastWasOperand = true;
            }

            if (ch == '(') {
                stack.push(std::string(1, ch));
            } else if (ch == ')') {
                while (!stack.empty() && stack.top() != "(") {
                    postfix << stack.top() << ' ';
                    stack.pop();
                }
                if (!stack.empty()) {
                    stack.pop();
                }
                if (!stack.empty() && isFunction(stack.top())) {
                    postfix << stack.top() << ' ';
                    stack.pop();
                }
            } else {
                std::string op(1, ch);
                while (!stack.empty() && getPrecedence(stack.top()[0]) >= getPrecedence(ch)) {
                    postfix << stack.top() << ' ';
                    stack.pop();
                }
                stack.push(op);
            }
        }
    }

    if (!token.empty()) {
        postfix << token << ' ';
    }

    while (!stack.empty()) {
        postfix << stack.top() << ' ';
        stack.pop();
    }

    return postfix.str();
}

//==================================================
// Funcion para evaluar la cadena postfix resultante de la funcion infixtopostfix
double evaluatePostfix(const std::string& postfix, const std::map<std::string, double>& variables) {
    std::stack<double> stack;
    std::stringstream ss(postfix);
    std::string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])) || token[0] == '.') {
            stack.push(std::stod(token));
        } else if (token[0] == '$') {
            if (variables.find(token) == variables.end()) {
                throw std::runtime_error("Variable no declarada: " + token);
            }
            stack.push(variables.at(token));
        } else if (isFunction(token)) {
            double a = stack.top(); stack.pop();
            if (token == "sin") stack.push(std::sin(a));
            else if (token == "cos") stack.push(std::cos(a));
            else if (token == "tan") stack.push(std::tan(a));
            else if (token == "log") stack.push(std::log10(a));
            else if (token == "ln") stack.push(std::log(a));
            else if (token == "exp") stack.push(std::exp(a));
        } else {
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            if (token == "+") stack.push(a + b);
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else if (token == "/") stack.push(a / b);
            else if (token == "^") stack.push(std::pow(a, b));
        }
    }

    return stack.top();
}


//========================================
// Funcion para procesar lo que el usuario digite en linea de comandos
// Esta funcion llama las demas funciones y maneja el flujo de operaciones
// hasta obtener el resultado.
void processInput(const std::string& input, std::map<std::string, double>& variables) {
    std::string cleanedInput = removeSpacesAroundEquals(input);
    size_t equalPos = cleanedInput.find('=');

    if (equalPos != std::string::npos) {
        // This is an assignment
        std::string varName = cleanedInput.substr(0, equalPos);
        std::string expression = cleanedInput.substr(equalPos + 1);

        if (!isValidVariableName(varName)) {
            std::cerr << "Error: Nombre de variable no válido." << std::endl;
            return;
        }

        try {
            std::string postfix = infixToPostfix(expression);
            double value = evaluatePostfix(postfix, variables);
            variables[varName] = value;
            std::cout << varName << " = " << value << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    } else {

        try {
            std::string postfix = infixToPostfix(cleanedInput);
            double value = evaluatePostfix(postfix, variables);
            std::cout << value << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
