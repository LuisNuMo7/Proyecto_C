// File: main_analizador_aritmetico.cc
// the program inputs an infix expression until the user enters an empty
// string. it uses the class infix2Postfix to convert the infix expression
// to postfix, handling errors that may occur by catching the corresponding
// expressionError exception. if there is no error, the postfix string is
// correctly formatted. use the class postfixEval to evaluate the postfix
// expression and output the result. this is the value of the original
// infix expression
//+++++++++++++++++++++++++++++++++++++++++
// IE-217 Estructuras Abstractas y algoritmos para Ingenier�a
// Modificaci�n acad�mica para c�digo de UCR.
// Modificaci�n: Freddy Rojas

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <map> // Para std::map
using namespace std;
#include "enum_base.h"
#include "aritmetic_base.h"
#include "expsymbol.h"
#include "infix2postfix.h"
#include "postfixEval.h"
#include "aritmetic_expression_eval.h"
#include "d_except.h"
int main(void)
{
	_aritmetic_expression_eval expression;
	string infixExp;
	cout << "Enter an infix expression: ";
	getline(cin, infixExp);

	while (infixExp != "")
	{
		try
		{
			// convert to postfix
			expression.setInfixExp(infixExp);
			expression.makepostfix();
			cout << "Value of the expression = "
				 << expression.evaluate() << endl
				 << endl;
		}

		// catch an exception and output the error
		catch (const expressionError &ee)
		{
			cout << ee.what() << endl
				 << endl;
		}
		// input another expression
		cout << "Enter an infix expression: ";
		getline(cin, infixExp);
	}

	return 0;
}

/*
Run:

Enter an infix expression: 3 ^ 2 ^ (1+2)
The postfix form is 3 2 1 2 + ^ ^
Value of the expression = 6561

Enter an infix expression: 3 * (4 - 2 ^ 5) + 6
The postfix form is 3 4 2 5 ^ - * 6 +
Value of the expression = -78

Enter an infix expression: (7 + 8*7
infix2Postfix: Missing ')'

Enter an infix expression: (9 + 7) 4
infix2Postfix: Operator expected

Enter an infix expression: 2*4*8/
infix2Postfix: Operand expected

Enter an infix expression:
*/
