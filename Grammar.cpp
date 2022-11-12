#include "Grammar.h"
#include "Variable.h"


double expression(Token_stream &ts, Symbol_table &var_table) {
    double left = secondary(ts, var_table);

    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
            case '+':
                left += secondary(ts, var_table);
                break;

            case '-':
                left -= secondary(ts, var_table);
                break;

            default:
                ts.putback(t);
                return left;
        }
    }
}


double declaration (Token_stream &ts, Symbol_table &var_table, bool _const)
{
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");

    string var = t.name;
    if (var_table.is_declared(var) && !var_table._const_(var) && _const)
        error(var, " already defined");
    if (var_table.is_declared(var) && var_table._const_(var) && !_const)
        error(var, " const already defined ");
    if (var_table.is_declared(var) && var_table._const_(var) && _const)
        error(var, " can't change const");

    t = ts.get();
    if (t.kind != '=')
        error("'=' missing in declaration of ", var);
    if (var_table.is_declared(var) && !_const)
        return var_table.define_name(var, expression(ts, var_table));
    return var_table.define_name (var, expression(ts, var_table), _const);
}


double statement (Token_stream &ts, Symbol_table &var_table)
{
    Token t = ts.get();
    switch (t.kind)
    {
        case let:
            return declaration(ts, var_table);
        case clet:
            return declaration(ts, var_table, true);
        default:
            ts.putback(t);
            return expression(ts, var_table);
    }
}



double primary (Token_stream &ts, Symbol_table &var_table)
{
    Token t = ts.get();
    switch (t.kind)
    {
        case '(':
        {
            double d = expression(ts, var_table);
            t = ts.get();
            if (t.kind != ')')
                error("'(' expected");
            return d;
        }

        case '-':
            return -primary(ts, var_table);
        case '+':
            return +primary(ts, var_table);

        case number:
            return t.value;

        case name:
            return var_table.get_value(t.name);

        default:
            error("primary expected");
    }
}

double secondary(Token_stream &ts, Symbol_table &var_table){
    double left = tertiary(ts, var_table);
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '*':
                left *= tertiary(ts, var_table);
                break;
            case '/': {
                double d = tertiary(ts, var_table);
                if (d == 0)
                    error("Division by zero");
                left /= d;
                break;
            }
            case '%': {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(tertiary(ts, var_table));

                if (i2 == 0)
                    error("Division by zero");

                left = i1 % i2;
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}
double tertiary (Token_stream &ts, Symbol_table &var_table){
    double left = primary(ts, var_table);
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '!':
                left = factorial(narrow_cast<int>(left));
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

int factorial(int n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

