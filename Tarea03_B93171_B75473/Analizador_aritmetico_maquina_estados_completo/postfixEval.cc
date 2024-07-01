//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IE-217 Estructuras Abstractas y algoritmos para Ingeniería
// Modificación académica para código de UCR.
// Modificación: Freddy Rojas
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <ctype.h>
#include <stdlib.h>
using namespace std;
#include "enum_base.h"
#include "aritmetic_base.h"
#include "postfixEval.h"
#include "d_except.h"

// Función para obtener un operando para operadores unarios
void postfixEval::getOperand(float &operand)
{
    if (operandStack.empty())
        throw expressionError("postfixEval: Not enough operands,aqui");

    operand = operandStack.top();
    operandStack.pop();
}

// Función original para obtener dos operandos para operadores binarios
void postfixEval::getOperands(float &left, float &right, t_aritmeticExpression op)
{
    getOperand(right); // Utiliza la nueva función para obtener el operando derecho

    // Verifica si el operador es unario
    if (op == token_exp || op == token_log || op == token_ln ||op == token_seno || op == token_coseno || op == token_tangente)
    {
        // Para operadores unarios, 'left' y 'right' serán el mismo
        left = right;
    }
    else
    {
        // Para operadores binarios, obtén el siguiente operando
        if (operandStack.empty())
            throw expressionError("postfixEval: Not enough operands");

        left = operandStack.top();
        operandStack.pop();
    }
}



float postfixEval::compute(float left, float right, t_aritmeticExpression op)
{
	float value, radianes;
    int lefti,righi;
    lefti=left;
    righi=right;
	switch (op)
	{
	case token_mas:
		value = left + right;
		break;
	case token_menos:
		value = left - right;
		break;
	case token_por:
		value = left * right;
		break;
	case token_resto:
		if (right == 0)
			throw expressionError("postfixEval: divide by 0");
		value = lefti % righi;
		break;
	case token_div:
		if (right == 0)
			throw expressionError("postfixEval: divide by 0");
		value = left / right;
		break;

	case token_pot:
		if (left == 0 && right == 0)
			throw expressionError("postfixEval: 0^0 undefined");

		value = 1;
		while (right > 0)
		{
			value *= left;
			right--;
		}
		break;
	case token_exp:
	value = exp(right);
	break;
	case token_log:
	value = log10(right);
	break;
	case token_ln:
	value = log(right);
	break;
	// Se incluyen los casos para seno, coseno, tangente.
    case token_seno:
             // Convertir ángulo a radianes
            radianes = (right * M_PI) / 180.0;
            value = sin(right);
            break;
    case token_coseno: value = cos(right); break;
    case token_tangente: value = tan(right); break;
	default:
		throw expressionError("postfixEval:token lost");
	}
	return value;
} //________________________________________________________________

postfixEval::postfixEval()
{
} //________________________________________________________________

// Función para evaluar la expresión postfija
float postfixEval::evaluate()
{
    float left, right;
    float expValue;
    show_tokenlist("Postfix:", t_postfixExpression);
    show_data();
    while (!t_postfixExpression.empty())
    {
        t_aritmeticExpression token = t_postfixExpression.front();
        t_postfixExpression.pop();

        if (token == token_numero)
        {
            if (DataQueue.empty())
                throw expressionError("postfixEval: DataQueue fail");
            operandStack.push(DataQueue.front());
            DataQueue.pop();
        }
        else
        {
            getOperands(left, right, token); // Asegúrate de pasar el token actual
            operandStack.push(compute(left, right, token));
        }
    }

    expValue = operandStack.top();
    operandStack.pop();

    if (!operandStack.empty())
        throw expressionError("postfixEval: Too many operands");
    return expValue;
}
