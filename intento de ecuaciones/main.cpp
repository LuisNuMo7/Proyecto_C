#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

std::string infixToPostfix(const std::string &infix)
{
    std::stack<char> stack;
    std::string postfix;
    for (char c : infix)
    {
        if (std::isspace(c))
            continue;
        if (std::isdigit(c) || c == '.')
        {
            postfix += c;
        }
        else if (isOperator(c))
        {
            postfix += ' ';
            while (!stack.empty() && precedence(stack.top()) >= precedence(c))
            {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
        else if (c == '(')
        {
            stack.push(c);
        }
        else if (c == ')')
        {
            while (!stack.empty() && stack.top() != '(')
            {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop();
        }
    }
    while (!stack.empty())
    {
        postfix += stack.top();
        stack.pop();
    }
    return postfix;
}

double evaluatePostfix(const std::string &postfix)
{
    std::stack<double> stack;
    std::stringstream ss(postfix);
    std::string token;
    while (ss >> token)
    {
        if (std::isdigit(token[0]) || (token.size() > 1 && std::isdigit(token[1])))
        {
            stack.push(std::stod(token));
        }
        else if (isOperator(token[0]))
        {
            double b = stack.top();
            stack.pop();
            double a = stack.top();
            stack.pop();
            switch (token[0])
            {
            case '+':
                stack.push(a + b);
                break;
            case '-':
                stack.push(a - b);
                break;
            case '*':
                stack.push(a * b);
                break;
            case '/':
                stack.push(a / b);
                break;
            }
        }
    }
    return stack.top();
}

const double EPSILON = 1e-10;

void printMatrix(const std::vector<std::vector<double>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (double value : row)
        {
            std::cout << std::setw(10) << value << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<double> gaussJordan(std::vector<std::vector<double>> matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; ++i)
    {
        // Find the pivot row
        int maxRow = i;
        for (int k = i + 1; k < n; ++k)
        {
            if (fabs(matrix[k][i]) > fabs(matrix[maxRow][i]))
            {
                maxRow = k;
            }
        }

        // Swap the maximum row with the current row
        std::swap(matrix[maxRow], matrix[i]);

        // Make sure the matrix is not singular
        if (fabs(matrix[i][i]) < EPSILON)
        {
            throw std::runtime_error("The matrix is singular or nearly singular.");
        }

        // Normalize the pivot row
        for (int j = i + 1; j <= n; ++j)
        {
            matrix[i][j] /= matrix[i][i];
        }
        matrix[i][i] = 1.0;

        // Eliminate the current column
        for (int k = 0; k < n; ++k)
        {
            if (k != i)
            {
                double factor = matrix[k][i];
                for (int j = i + 1; j <= n; ++j)
                {
                    matrix[k][j] -= factor * matrix[i][j];
                }
                matrix[k][i] = 0.0;
            }
        }
    }

    // Extract the solution
    std::vector<double> solution(n);
    for (int i = 0; i < n; ++i)
    {
        solution[i] = matrix[i][n];
    }
    return solution;
}

int main()
{
    std::string input;
    std::cout << "Introduce el sistema de ecuaciones en el formato @[ a1, b1, c1, d1;a2, b2, c2, d2; a3, b3, c3, d3; a4, b4, c4, d4]: ";
    std::getline(std::cin, input);

    std::string infix = input.substr(2, input.size() - 3);
    std::replace(infix.begin(), infix.end(), ',', ' ');
    std::replace(infix.begin(), infix.end(), ';', ' ');

    std::stringstream ss(infix);
    std::vector<std::vector<double>> matrix(4, std::vector<double>(5));
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            std::string token;
            ss >> token;
            std::string postfix = infixToPostfix(token);
            matrix[i][j] = evaluatePostfix(postfix);
        }
    }

    try
    {
        std::vector<double> solution = gaussJordan(matrix);
        std::cout << "Solución: [";
        for (size_t i = 0; i < solution.size(); ++i)
        {
            std::cout << solution[i];
            if (i != solution.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
