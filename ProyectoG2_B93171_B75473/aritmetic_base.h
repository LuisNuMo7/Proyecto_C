//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IE-217 Estructuras Abstractas y algoritmos para Ingeniería
// Modificación académica para código de UCR.
// Modificación: Freddy Rojas
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef ARITMETIC_BASE_INCLUDED
#define ARITMETIC_BASE_INCLUDED

class _aritmetic_base : public _enum_base
{
protected:
  queue<t_aritmeticExpression> t_infixExpression;
  queue<t_aritmeticExpression> t_postfixExpression;
  queue<float> DataQueue;
  inline void show_tokenlist(char *msg, queue<t_aritmeticExpression> copy)
  {
    // queue<t_aritmeticExpression> copy(t_infixExpression);
    int length = copy.size();
    cout << msg << " ";
    for (int i = 0; i < length; i++)
    {
      cout << "<TOKEN:" << copy.front() << ">";
      copy.pop();
    }
    cout << endl;
  } //_______________________________________________________

  inline void show_data(void)
  {
    // queue<t_aritmeticExpression> copy(t_infixExpression);
    queue<float> copy(DataQueue);
    int length = copy.size();
    cout << "DATA QUEUE ";
    for (int i = 0; i < length; i++)
    {
      cout << "<DATA:" << copy.front() << ">";
      copy.pop();
    }
    cout << endl;
  } //_______________________________________________________

  inline bool isOperator(t_aritmeticExpression token) const
  {
    switch (token)
    {
    case token_mas:
    case token_menos:
    case token_por:
    case token_resto:
    case token_div:
    case token_exp:
    case token_ln:
    case token_log:
    // Se incluyen los casos para los tokens seno, coseno, tangente
    case token_seno:
    case token_coseno:
    case token_tangente:
    case token_pot:
      return true;
    default:
      return false;
    }
  } //_______________________________________________________
}; //______________________________________________________

#endif // ARITMETIC_BASE_INCLUDED
