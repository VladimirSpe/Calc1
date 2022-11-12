#ifndef UNTITLED_VARIABLE_H
#define UNTITLED_VARIABLE_H


#include "std_lib_facilities.h"


struct Variable
{
    string name;
    double value;

    Variable (string n, double v)
            : name{ n }, value{ v }, _const{false} {};
    Variable(string n, double v, bool _c) : name{n}, value{v}, _const{_c} {};
    bool _const_() const {return _const;};
private:
    bool _const{false};
};

class Symbol_table {
public:
    Symbol_table() : var_table{{}} {};

    double get_value(string);
    void set_value(string, double);
    double define_name(string, double, bool = false);
    bool is_declared(string);
    bool _const_(string);

private:
    vector<Variable> var_table;
};


#endif //UNTITLED_VARIABLE_H
