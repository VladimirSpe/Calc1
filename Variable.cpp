#include "Variable.h"
double Symbol_table::define_name (string var, double val, bool _const)
{
    if (is_declared(var) && _const_(var))
        error(var, " constdeclared twice");
    else if (is_declared(var) && !_const_(var))
        set_value(var, val);

    var_table.push_back (Variable{ var, val, _const});

    return val;
}

bool Symbol_table::is_declared (string s)
{
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s) return true;

    return false;
}

void Symbol_table::set_value (string s, double d)
{
    for (int i = 0; i <= var_table.size(); ++i)
    {
        if (var_table[i].name == s)
        {
            var_table[i].value = d;
            return;
        }
    }

    error("set: undefined name ", s);
}

double Symbol_table::get_value (string s)
{
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    error("get: undefined name ", s);
}

bool Symbol_table::_const_(string var) {
    for (int i = 0; i < var_table.size(); ++i){
        if (var_table[i].name == var && var_table[i]._const_())
            return true;
    }
    return false;
}

