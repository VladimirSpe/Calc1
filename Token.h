#ifndef UNTITLED_TOKEN_H
#define UNTITLED_TOKEN_H
#include "std_lib_facilities.h"

struct Token {
    char kind;
    double value;
    string name;

    Token (char ch)
            : kind{ ch }, value{ 0 }
    { }

    Token(char ch, string name)
            : kind {ch}, name{name}
    { }

    Token (char ch, double val)
            : kind{ ch }, value{ val }
    { }
};


class Token_stream
{
public:
    Token_stream() = default;

    Token get ();
    void putback (Token t);
    void ignore (char);
private:
    bool full{ false };
    Token buffer{ '\0' };
};


constexpr char quit = 'q';
constexpr char print = ';';
constexpr char help = 'h';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char clet = 'C';

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string cletkey = "const";
const string quitkey = "quit";
const string helpkey = "help";



#endif //UNTITLED_TOKEN_H
