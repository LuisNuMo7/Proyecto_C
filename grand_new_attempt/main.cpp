#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <sstream>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <regex>

//==================================
bool isValidVariableName(const std::string& name) {
    const std::regex varPattern(R"(^\$[a-zA-Z]{1,10}(_[a-zA-Z]{1,10})?$|^\$[a-zA-Z]{1,20}$)");
    return std::regex_match(name, varPattern);
}

std::string removeSpacesAroundEquals(const std::string& input) {
    const std::regex spacePattern(R"(\s*=\s*)");
    return std::regex_replace(input, spacePattern, "=");
}

//==================================
int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        case '(': return 0;
        case ')': return 0;
    }
    return -1;
}

std::string infixToPostfix(const std::string& infix) {
    std::stack<char> stack;
    std::stringstream postfix;
    bool lastWasOperand = false;

    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];

        if (isspace(ch)) {
            continue;
        }

        if (isalnum(ch) || ch == '$') {
            postfix << ch;
            lastWasOperand = true;
        } else {
            if (lastWasOperand) {
                postfix << ' ';
                lastWasOperand = false;
            }

            if (ch == '(') {
                stack.push(ch);
            } else if (ch == ')') {
                while (!stack.empty() && stack.top() != '(') {
                    postfix << stack.top() << ' ';
                    stack.pop();
                }
                if (!stack.empty()) {
                    stack.pop();
                }
            } else {
                while (!stack.empty() && getPrecedence(stack.top()) >= getPrecedence(ch)) {
                    postfix << stack.top() << ' ';
                    stack.pop();
                }
                stack.push(ch);
            }
        }
    }

    if (lastWasOperand) {
        postfix << ' ';
    }

    while (!stack.empty()) {
        postfix << stack.top() << ' ';
        stack.pop();
    }

    return postfix.str();
}

//============================
double evaluatePostfix(const std::string& postfix, const std::map<std::string, double>& variables) {
    std::stack<double> stack;
    std::stringstream ss(postfix);
    std::string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            stack.push(std::stod(token));
        } else if (token[0] == '$') {
            if (variables.find(token) == variables.end()) {
                throw std::runtime_error("Variable no declarada: " + token);
            }
            stack.push(variables.at(token));
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
        // This is just an expression
        try {
            std::string postfix = infixToPostfix(cleanedInput);
            double value = evaluatePostfix(postfix, variables);
            std::cout << value << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

//=============================================
int main() {
    std::map<std::string, double> variables;
    std::string input;

    while (true) {
        std::cout << "Ingrese una declaración o expresión: ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        processInput(input, variables);
    }

    return 0;
}

