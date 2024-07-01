#include "aritmetic_expression_eval.h"
#include<iostream>
#include<string>
using namespace std;
bool _aritmetic_expression_eval::isValidName(const string& name){
    // Mediante el uso de expresiones regulares se busca cubrir
    // la variedad de distintas formas de variables que se puedan
    // llegar a digitar.
    // El patron elegido es una extension maxima de 20 letras
    // o 10 letras iniciales luego '_' y 10 letras finales
    // como limite
    const regex Pattern(R"(^\$[a-zA-Z]{1,10}(_[a-zA-Z]{1,10})?$|^\$[a-zA-Z]{1,20}$)");
    return regex_match(name, varPattern);
}
//string _aritmetic_expression_eval::
