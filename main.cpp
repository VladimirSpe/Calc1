#include "Token.h"
#include "Grammar.h"
#include "Variable.h"
#include "std_lib_facilities.h"



void clean_up_mess(Token_stream &ts) {
    ts.ignore(print);
}
void print_help(Token_stream &ts){
    cout << "Operations: +, -, *, /, %, !\n"
         << "Output: ;\n"
         << "Variable declaration: 'c'let name = term\n"
         << "Help: help \n"
         << "Exit: quit\n";
}

void calculate(Token_stream &ts, Symbol_table &variables) {
    while (std::cin) {
        try {
            std::cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();

            if (t.kind == quit)
                return;
            if (t.kind == help) {
                print_help(ts);
                t = ts.get();
            }
            else {
                ts.putback(t);
                std::cout << result << statement(ts, variables) << '\n';
            }
        }
        catch (std::runtime_error &e) {
            std::cerr << e.what() << endl;
            clean_up_mess(ts);
        }
    }
}
int main () {
    Token_stream ts;
    Symbol_table var_table;
    try {
        var_table.define_name("pi", 3.141592653589793);
        var_table.define_name("e", 2.718281828459045);

        calculate(ts, var_table);
        return 0;
    }
    catch (exception &e) {
        cerr << "exception: " << e.what() << "\n";
        return 1;
    }
    catch (...) {
        cerr << "Oops, unknown exception" << "\n";
        return 2;
    }
}
