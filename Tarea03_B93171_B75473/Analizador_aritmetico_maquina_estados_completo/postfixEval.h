#ifndef POSTFIX_H_INCLUDED
#define POSTFIX_H_INCLUDED
class postfixEval : public virtual _aritmetic_base{
private:
  stack<float> operandStack;
    void getOperand(float &right);
	void getOperands(float& left, float& right, t_aritmeticExpression op);
	float compute(float left, float right,t_aritmeticExpression op);

public:
  postfixEval();
	float evaluate();
};//___________________________________________________________
#endif
