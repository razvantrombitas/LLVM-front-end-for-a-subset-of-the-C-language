#ifndef _LEXER_H_
#define _LEXER_H_
#include <string>

class ExprToken
{
public:
    enum Type { Int, Return, Number, Symbol, Id, EndOfData } type;
    unsigned long numberValue;  // The numerical value of token. Valid if type==Number
    char symbolValue;    // The symbol character : '+' , '-', '*', '/', '(' or ')' . Valid if type==Symbol
    std::string identifierValue;

    // for debugging process: convert the enum type into a string
    std::string convert_to_string(){
        std::string string_return;
        switch(type)
        {
            case Int:       string_return = "int"; break;
            case Return:    string_return = "return"; break;
            case Number:    string_return = "number " + std::to_string(numberValue); break;
            case Symbol:    string_return = "symbol "; 
                            string_return.push_back(symbolValue); break;
            case Id:        string_return = "identifier " + identifierValue; break;
            case EndOfData: string_return = "EndOfData"; break;
        }
        return string_return;
    }
};

class ExprLexer
{
    std::string input;               // String to be parsed
    std::string::const_iterator pos; // Current position in the string
public:
    ExprLexer(const std::string &aInput) : input(aInput), pos(input.begin()) {}

    // Parse the next token in the string and return it
    ExprToken next();
};

#endif

