/*
This code is an implementation of a lexer (also known as a tokenizer) for a simple expression language.
A lexer takes a string input, which is assumed to be a sequence of characters that form tokens such as numbers,
symbols, and identifiers, and it breaks the input string into these tokens.

In this code, ExprLexer::next is a function that returns the next token in the input string.
The input string is passed to the lexer as an object attribute.

The std::regex class is used to define a regular expression, which is a pattern that can be used to match and extract substrings from a string.
The regular expression defined in this code is used to match all possible token types in the input string: integers, numbers, symbols, identifiers, and whitespaces.

The function std::regex_search is used to search for matches of the regular expression in the input string.
The std::smatch class holds the results of the match, with each group in the regular expression being represented as an element in the std::smatch collection.

Based on the matched token type, the code sets the type and the corresponding value of the token in the ExprToken object and returns it.
If there are no matches, an error message is printed, and the program exits with a non-zero status code.

This lexer code will be useful in parsing and processing expressions in the expression language, as it breaks the input into tokens that can be further processed by a parser.
 */
#include <regex>
#include <cstdlib>
#include <llvm/Support/ErrorHandling.h>
#include <llvm/Support/FormatVariadic.h>
#include <llvm/Support/raw_ostream.h>
#include "lexer.h"

ExprToken ExprLexer::next()
{
    std::string::const_iterator end = input.end();

    // Create a regular expression adding numbered groups for each type of token
    //
    // Int:        int
    // Number:     0|[1-9][0-9]*
    // Symbol:     [*+-/()]
    // Identifier: [a-z]
    // Whitespace: [ \\t\\n\\r]+
    // The enum represents the index of each "()" group in the regular expression.
    // Each group will then have a corresponding entry in the 'smatch' collection that is filled by regex_search
    // Note: (?:  ) is a special notation for a group that should not appear in the 'smatch' collection

    enum { RAll, RInt, RNumber, RSymbol, RIdentifier, RWhiteSpace, RGroupCount };
    std::regex rex("(int)|(0|[1-9][0-9]*)|([*+-/(){};=])|([a-zA-Z][a-zA-Z0-9_]*)|([ \\t\\r\\n]+)");

    for(;;)
    {
        ExprToken token;
        if (pos == end)
        {
            token.type = ExprToken::EndOfData;
            return token;
        }
        // Search for all the token types at once.
        std::smatch m;
        if (std::regex_search(pos, end, m, rex, std::regex_constants::match_continuous))
        {
            if (m.size() != RGroupCount)
                llvm_unreachable("Internal error : regex has different number of numbered groups than expected");

            pos = m[RAll].second; // Skip the token that was just matched, update position for the following time next() is called

            // Number?
            if (m[RNumber].matched)
            {
                token.type = ExprToken::Number;
                token.numberValue = std::stoul(m[RNumber].str());
                return token;
            }

            // Symbol?
            if (m[RSymbol].matched)
            {
                assert(m[RSymbol].length() > 0);
                token.type = ExprToken::Symbol;
                token.symbolValue = m[RSymbol].str().at(0);
                return token;
            }

            // Identifier?
            if(m[RIdentifier].matched)
            {
                if(m[RIdentifier]=="return")
                {
                    token.type = ExprToken::Return;
                }
                else
                {
                    token.type = ExprToken::Id;
                    token.identifierValue = m[RIdentifier].str();
                }
                return token;
            }

            // int?
            if(m[RInt].matched)
            {
                token.type = ExprToken::Int;
                return token;
            }

            if (m[RWhiteSpace].matched)
                continue;
        }

        llvm::outs() << llvm::formatv("Illegal character '{0}' in input.\n", std::string(pos,pos+1).at(0));
        std::exit(1);
    }
}

