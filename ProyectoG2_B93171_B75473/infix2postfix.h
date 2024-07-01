//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//IE-217 Estructuras Abstractas y algoritmos para Ingeniería
//Modificación académica para código de UCR.
//Modificación: Freddy Rojas
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef INFIX2POSTFIX
#define INFIX2POSTFIX

// labels designating the parentheses characters
const char lParen  = '(', rParen = ')';

class infix2Postfix :public virtual _aritmetic_base{
private:
	string infixExpression;
	stack<expressionSymbol> operatorStack;
	std::map<std::string, float> variables; // Mapa para almacenar variables y sus valores

  void outputHigherOrEqual(const expressionSymbol& op);
  bool evaluate_int(int&);
  bool resolveLex(void);

public:
  infix2Postfix();
	infix2Postfix(const string& infixExp);
	void setInfixExp(const string& infixExp);
	bool makepostfix();
};//_____________________________________________________________________________________
#endif
