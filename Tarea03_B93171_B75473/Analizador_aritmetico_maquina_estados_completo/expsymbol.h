//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//IE-217 Estructuras Abstractas y algoritmos para Ingeniería
//Modificación académica para código de UCR.
//Modificación: Freddy Rojas
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef EXPSYMBOL
#define EXPSYMBOL
class expressionSymbol{
private:
  _enum_base::t_aritmeticExpression op;
  int inputPrecedence;
	int stackPrecedence;

public:
  expressionSymbol();
	expressionSymbol(_enum_base::t_aritmeticExpression ch);
	friend bool operator>= (const expressionSymbol& left,const expressionSymbol& right);
	_enum_base::t_aritmeticExpression getOp() const;
};//__________________________________________________________________________________________
#endif

