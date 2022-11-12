#ifndef UNTITLED_GRAMMAR_H
#define UNTITLED_GRAMMAR_H
#include "Token.h"
#include "Variable.h"


double expression (Token_stream &ts, Symbol_table &var_table);
double declaration (Token_stream &ts, Symbol_table &var_table, bool = false);
double statement (Token_stream &ts, Symbol_table &var_table);
double primary(Token_stream &ts, Symbol_table &var_table);
double secondary(Token_stream &ts, Symbol_table &var_table);
double tertiary(Token_stream &ts, Symbol_table &var_table);
int factorial(int n);

#endif //UNTITLED_GRAMMAR_H
