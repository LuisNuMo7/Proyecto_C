#ifndef ARITMETIC_EXPRESSION_EVAL_H_INCLUDED
#define ARITMETIC_EXPRESSION_EVAL_H_INCLUDED

class _aritmetic_expression_eval :public virtual infix2Postfix, public virtual postfixEval
{
public:
    // Dado que se esperan expresiones varias para las variables
    // se desarrolla una funcion que las valide
    bool isValidName(const string& name);
    // Esta funcion busca manejar posibles errores cuando un usuario
    // digite $v = 9 por ejemplo.
    //string removeBlankSpaces(const string& input);
};//______________________________________________________
#include"aritmetic_expression_eval.cpp"
#endif // ARITMETIC_EXPRESION_EVAL_H_INCLUDED
