
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <ctype.h>
#include <map>
#include <stdlib.h>
using namespace std;
#include "enum_base.h"
#include "aritmetic_base.h"
#include "expsymbol.h" // expressionSymbol class
#include "d_except.h"  // for expressionError exception
#include "infix2postfix.h"

//+++++++++++++++++++
// infix2postfix
//+++++++++++++++++++
bool infix2Postfix::evaluate_int(int &i)
{
    bool salida = false;
    enum e_int_state
    {
        inicial,
        espera_ultimo_digito
    } estado = inicial;
    string valor = "";
    while (!salida)
    {
        if (!infixExpression[i])
            break;
        char car = infixExpression[i];
        switch (estado)
        {
        case inicial:
            switch (car)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                valor += car;
                estado = espera_ultimo_digito;
                i++;
                break;

            default:
                return false;
            }
            break;

        case espera_ultimo_digito:
            switch (car)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                valor += car;
                i++;
                break;

            default:
                salida = true;
                break;
            }
            break;
        }
    }
    t_infixExpression.push(token_numero);
    float val = atoi(valor.c_str());
    DataQueue.push(val);
    return true;
} //______________________________________________________________

bool infix2Postfix::resolveLex(void)
{
    bool salida = false;
    int i = 0;
    while (!t_infixExpression.empty())
        t_infixExpression.pop();
    while (!DataQueue.empty())
        DataQueue.pop();

    while (!salida)
    {
        if (i == (int)infixExpression.length())
            break;
        if (!infixExpression[i])
            break;
        char ch = infixExpression[i];
        switch (ch)
        {
        case '+':
            t_infixExpression.push(token_mas);
            i++;
            break;
        case '-':
            t_infixExpression.push(token_menos);
            i++;
            break;
        case '*':
            t_infixExpression.push(token_por);
            i++;
            break;
        case '/':
            t_infixExpression.push(token_div);
            i++;
            break;
        case '%':
            t_infixExpression.push(token_resto);
            i++;
            break;
        case '^':
            t_infixExpression.push(token_pot);
            i++;
            break;
        case '(':
            t_infixExpression.push(token_pizq);
            i++;
            break;
        case ')':
            t_infixExpression.push(token_pder);
            i++;
            break;
        // Se incluyen los casos para seno, coseno, tangente
        case 's':
            if (infixExpression.substr(i, 3) == "sen" || infixExpression.substr(i, 3) == "sin")
            {
                t_infixExpression.push(token_seno);
                i += 3; //
            }
            else
            {
                return false;
            }
            break;
        case 'c':
            if (infixExpression.substr(i, 3) == "cos")
            {
                t_infixExpression.push(token_coseno);
                i += 3;
            }
            else
            {
                return false;
            }
            break;
        case 't':
            if (infixExpression.substr(i, 3) == "tan")
            {
                t_infixExpression.push(token_tangente);
                i += 3; //
            }
            else
            {
                return false;
            }
            break;
        case 'l': // Para 'lnat' o 'log'
            if (infixExpression.substr(i, 2) == "ln")
            {
                t_infixExpression.push(token_ln);
                i += 2; // Avanzar más allá del token 'ln'
            }
            else if (infixExpression.substr(i, 3) == "log")
            {
                t_infixExpression.push(token_log);
                i += 3; // Avanzar más allá del token 'log'
            }
            else
            {
                return false; // Error si no es 'ln' ni 'log'
            }
            break;
        case 'e': // Para 'exponencial'
            if (infixExpression.substr(i, 3) == "exp")
            {
                t_infixExpression.push(token_exp);
                i += 3; // Avanzar más allá del token 'exp'
            }
            else
            {
                return false; // Error si no es 'exp'
            }
            break;
        case '#':
        {
            // Es un comando especial
            ++i; // Avanzar al siguiente carácter después del #
            if (i < infixExpression.length() && infixExpression.substr(i, 6) == "values")
            {
                // Es #values, imprimir todas las variables
                std::cout << "Variables in map:" << std::endl;
                for (const auto &pair : variables)
                {
                    std::cout << pair.first << " = " << pair.second << std::endl;
                }
                // Avanzar el índice para salir del caso #values
                i += 6;
            }
            else
            {
                // Comando no reconocido
                return false;
            }
            break;
        }

        case '$':
        {
            // Es una variable
            std::string variableName;
            ++i; // Avanzar al siguiente carácter después del $
            while (i < infixExpression.length() && (isalnum(infixExpression[i]) || infixExpression[i] == '_'))
            {
                variableName += infixExpression[i];
                ++i;
            }
            if (variableName.empty())
            {
                // Error: nombre de variable vacío después de $
                return false;
            }

            if (i < infixExpression.length() && infixExpression[i] == '=')
            {
                ++i; // Avanzar más allá del =
                // Buscar el número después del =
                std::string numberValue;
                while (i < infixExpression.length() && (isdigit(infixExpression[i]) || infixExpression[i] == '.'))
                {
                    numberValue += infixExpression[i];
                    ++i;
                }

                if (numberValue.empty())
                {
                    // Error: después del = no se encontró un número válido
                    return false;
                }

                // Guardar el valor numérico en el mapa
                float numericValue = std::stof(numberValue); // Convertir el string a float
                variables[variableName] = numericValue;

                if (!evaluate_int(i))
                    i++;
            }
            else
            {
                // Error: falta el signo = después del nombre de la variable
                return false;
            }
            break;
        }

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (!evaluate_int(i))
                i++;
            break;
        default:
            return false;
        }
    }
    return true;
}

bool isUnaryOperator(_enum_base::t_aritmeticExpression token)
{
    return token == _enum_base::token_exp ||
           token == _enum_base::token_ln ||
           token == _enum_base::token_log ||
           token == _enum_base::token_seno ||
           token == _enum_base::token_coseno ||
           token == _enum_base::token_tangente;
}
void infix2Postfix::outputHigherOrEqual(const expressionSymbol &op)
{
    expressionSymbol op2;

    while (!operatorStack.empty() &&
           (op2 = operatorStack.top()) >= op)
    {
        operatorStack.pop();
        t_postfixExpression.push(op2.getOp());
    }
} //_______________________________________________________

infix2Postfix::infix2Postfix()
{
} //_______________________________________________________

infix2Postfix::infix2Postfix(const string &infixExp) : infixExpression(infixExp)
{
} //_______________________________________________________

void infix2Postfix::setInfixExp(const string &infixExp)
{
    infixExpression = infixExp;
    while (!t_postfixExpression.empty())
        t_postfixExpression.pop();
    while (!t_infixExpression.empty())
        t_infixExpression.pop();
    while (!DataQueue.empty())
        DataQueue.pop();
} //_______________________________________________________

bool infix2Postfix::makepostfix()
{
    if (!resolveLex())
        return false;
    show_tokenlist("Infix:", t_infixExpression);

    expressionSymbol op;

    int rank = 0;
    t_aritmeticExpression token;

    // process until end of the expression
    while (!t_infixExpression.empty())
    {
        token = t_infixExpression.front();
        t_infixExpression.pop();

        // CAMBIO: Manejar números
        if (token == token_numero)
        {
            t_postfixExpression.push(token);
            rank++;
            if (rank > 1)
                throw expressionError("infix2Postfix: Operator expected");
        }
        // CAMBIO: Manejar operadores unarios
        else if (isUnaryOperator(token)) // Asegúrate de implementar esta función
        {
            op = expressionSymbol(token);
            outputHigherOrEqual(op);
            operatorStack.push(op);
        }
        // CAMBIO: Procesar un operador o '('
        else if (isOperator(token) || token == token_pizq)
        {
            if (token != token_pizq && !isUnaryOperator(token)) // No decrementar para unarios
                rank--;

            if (rank < 0)
                throw expressionError("infix2Postfix: Operand expected");
            else
            {
                op = expressionSymbol(token);
                outputHigherOrEqual(op);
                operatorStack.push(op);
            }
        }
        // CAMBIO: Procesar ')'
        else if (token == token_pder)
        {
            op = expressionSymbol(token);
            outputHigherOrEqual(op);
            if (operatorStack.empty())
                throw expressionError("infix2Postfix: Missing '('");
            else
                operatorStack.pop(); // get rid of '('
        }
        else
            throw expressionError("infix2Postfix: Invalid input");
    }

    // CAMBIO: Verificar el rango al final del procesamiento
    if (rank != 1)
        throw expressionError("infix2Postfix: Operand expected");
    else
    {
        while (!operatorStack.empty())
        {
            op = operatorStack.top();
            operatorStack.pop();
            if (op.getOp() == token_pizq)
                throw expressionError("infix2Postfix: Missing ')'");
            else
            {
                t_postfixExpression.push(op.getOp());
            }
        }
    }
    return true;
} //_______________________________________________________
