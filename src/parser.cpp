/*
The code is part of a compiler or interpreter for a simple arithmetic expression language.
 The parser is responsible for breaking down the source code of an expression into smaller,
 manageable pieces and constructing a tree-like structure, known as an Abstract Syntax Tree (AST), from them.
 This tree represents the structure of the expression and can be used to generate code, interpret the expression, or perform other operations.

The code is using the LLVM library to generate low-level intermediate representation (IR) code.
 This IR code can then be used to produce machine code for a target platform, or it can be used to perform other analysis or optimization tasks.

The parser is using the LL(1) parsing technique, which stands for "left-to-right, leftmost derivation, using a single lookahead symbol".
 The grammar of the expression language is specified using Extended Backus-Naur Form (EBNF).
 The code defines functions to parse different parts of an expression, such as terms, factors, and expressions.
 Each function returns a value, which is a pointer to an llvm::Value object.
 The value represents the result of evaluating the corresponding expression.

In the code, the parseExpr() function is responsible for parsing an expression.
 It starts by parsing a term and then looks for optional occurrences of either '+' or '-' symbols, followed by another term.
 If found, it adds or subtracts the term from the result.

The parseTerm() function is responsible for parsing a term.
 It starts by parsing a factor and then looks for optional occurrences of either '*' or '/' symbols, followed by another factor.
 If found, it multiplies or divides the factor from the result.

The parseFact() function is responsible for parsing a factor.
 If the next token is a number, it creates a constant value for it.
 If the next token is an identifier, it looks for the identifier in two maps, one for function parameters and another for local variables.
 If it is found, it returns the corresponding value, otherwise it generates an error.
 If the next token is '(', it calls parseExpr() to parse the expression within the parentheses, and returns the result.
 If the next token is '-', it negates the result of parseFact().
 */


#include "parser.h"
#include <cstdlib>
#include <iostream>
using namespace std;

/* LL(1) grammar - EBNF

   expression : term ('+' term | '-' term)*
   term       : factor ('*' factor | '/' factor)*
   factor     : number | '(' expression ')' | '-' factor

   func: int string '(' param ')' '{' locals asgn * return '}'
   locals: int string (',' string) * ';'
   asgn: string '=' expr ';'
   return: return expr ';'

*/

static void error(const std::string &message)
{
    llvm::outs() << message << "\n";
    std::exit(1);
}

llvm::Value * ExprParser::parseExpr(std::unordered_map<std::string, llvm::Argument*> FunctionParamMap, std::unordered_map<std::string, llvm::AllocaInst*> LocalVariablesMap, llvm::LLVMContext& context)
{
    llvm::Value * val = parseTerm(FunctionParamMap,  LocalVariablesMap, context);
    while ((tk.type != ExprToken::Symbol || (tk.symbolValue != ')')) && tk.type != ExprToken::EndOfData)
    {
        if (tk.type != ExprToken::Symbol) error("Expecting + or -, found " + tk.convert_to_string());
        switch(tk.symbolValue)
        {
            case '+' : tk = lexer.next(); val = pBuilder->CreateAdd(val, parseTerm(FunctionParamMap, LocalVariablesMap, context)); break; // already had a term -> then add
            case '-' : tk = lexer.next(); val = pBuilder->CreateSub(val, parseTerm(FunctionParamMap, LocalVariablesMap, context)); break; // already had a term -> then sub
            case ';' : return val; break;
            default: error("Expecting +  or - or ;, found "+tk.convert_to_string());
        }
    }

    if(!(tk.type == ExprToken::Symbol && tk.symbolValue == ')'))
    {
        tk = lexer.next();
    }

    return val;
}

llvm::Value * ExprParser::parseTerm(std::unordered_map<std::string, llvm::Argument*> FunctionParamMap, std::unordered_map<std::string, llvm::AllocaInst*> LocalVariablesMap, llvm::LLVMContext& context)
{
    llvm::Value * val = parseFact(FunctionParamMap, LocalVariablesMap, context);
    while ((tk.type != ExprToken::Symbol || (tk.symbolValue != ')' && tk.symbolValue != '+' && tk.symbolValue != '-')) && tk.type != ExprToken::EndOfData)
    {
        if (tk.type != ExprToken::Symbol) error("Expecting * or /, found "+tk.convert_to_string());
        switch(tk.symbolValue)
        {
            case '*' : tk = lexer.next(); val = pBuilder->CreateMul(val, parseFact(FunctionParamMap,LocalVariablesMap, context)); break;
            case '/' : tk = lexer.next(); val = pBuilder->CreateSDiv(val, parseFact(FunctionParamMap, LocalVariablesMap, context)); break;
            case ';' : return val; break;
            default: error("Expecting * or / or ;, found "+tk.convert_to_string());
        }
    }
    return val;
}


llvm::Value * ExprParser::parseFact(std::unordered_map<std::string, llvm::Argument*> FunctionParamMap, std::unordered_map<std::string, llvm::AllocaInst*> LocalVariablesMap, llvm::LLVMContext& context)
{
    llvm::Value * val;
    if (tk.type == ExprToken::Number)
    {
        // create constant
        val = llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(context), tk.numberValue);
        tk = lexer.next();
    }
    else if (tk.type == ExprToken::Id){
        // search in both params and local variables
        if(FunctionParamMap.find(tk.identifierValue) != FunctionParamMap.end())
        {
            val = FunctionParamMap[tk.identifierValue];
            tk = lexer.next();
        }
        else if(LocalVariablesMap.find(tk.identifierValue) != LocalVariablesMap.end())
        {
            llvm::LoadInst* identifier_value = pBuilder->CreateLoad(llvm::IntegerType::getInt32Ty(context),
                                                                    LocalVariablesMap[tk.identifierValue],
                                                                    false);
            val = identifier_value;
            tk = lexer.next();
        }
        else
        {
            error("Couldn't find identifier in map" + tk.identifierValue);
        }

    }
    else if (tk.type == ExprToken::Symbol)
    {
        switch(tk.symbolValue)
        {
            case '(':
                tk = lexer.next();
                val = parseExpr(FunctionParamMap, LocalVariablesMap, context);
                if (tk.type == ExprToken::Symbol && tk.symbolValue == ')')
                {
                    tk = lexer.next();
                }
                else
                {
                    error("Expecting ), found " + tk.convert_to_string());
                }
                break;
            case '-':
                tk = lexer.next();
                val = pBuilder->CreateNeg(parseFact(FunctionParamMap, LocalVariablesMap, context));
                break;
            default:
                error("Expecting ( or -, found " + tk.convert_to_string());
        }
    }
    else error("Expecting number or subexpression, found: " + tk.convert_to_string());
    return val;
}

std::string ExprParser::parseFunctionName()
{
    std::string FunctionName;

    if (tk.type == ExprToken::Int)
    {
        tk = lexer.next();

        if (tk.type == ExprToken::Id)
        {
            FunctionName = tk.identifierValue; //identifierValue is a string in lexer.h
            tk = lexer.next();
            return FunctionName;
        }
        else
        {
            error("Expecting identifier, found " + tk.convert_to_string());
            return "";
        }
    }
    else
    {
        error("Expecting 'int', found " + tk.convert_to_string());
        return "";
    }
}

std::vector<std::string> ExprParser::parseFunctionParam()
{
    std::vector<std::string> ParamVector;

    if (!(tk.type == ExprToken::Symbol && tk.symbolValue == '(')) error("Expected (, found " + tk.convert_to_string());
    tk = lexer.next(); // int

    while(tk.symbolValue!=')') {

        if(tk.symbolValue == ',')
        {
            tk = lexer.next();
        }

        if (tk.type != ExprToken::Int)
        {
            error("Expecting int, found " + tk.convert_to_string());
        }
        tk = lexer.next(); // identifier

        if (tk.type != ExprToken::Id)
        {
            error("Expecting identifier, found " + tk.convert_to_string());
        }
        ParamVector.push_back(tk.identifierValue);

        tk = lexer.next(); // ','' or ')'
    }

    if (!(tk.type == ExprToken::Symbol && tk.symbolValue == ')'))
    {
        error("Expecting ), found " + tk.convert_to_string());
    }

    tk = lexer.next();
    return ParamVector;
}

// locals: int string (',' string) * ';'
std::unordered_map<std::string, llvm::AllocaInst*> ExprParser::parseLocalVariables(llvm::LLVMContext& context)
{
    std::unordered_map<std::string, llvm::AllocaInst*> localVariables;

    if(tk.type!=ExprToken::Int) return localVariables;
    tk = lexer.next();

    // primul local
    if(tk.type!=ExprToken::Id)
    {
        error("Expecting identifier, found " + tk.convert_to_string());
    }

    if(localVariables.find(tk.identifierValue) != localVariables.end())
    {
        error("Multiple declarations of local variable " + tk.identifierValue);
    }

    while(!(tk.type==ExprToken::Symbol && tk.symbolValue==';'))
    {

        if(tk.symbolValue == ',')
        {
            tk = lexer.next();
        }

        if(tk.type!=ExprToken::Id)
        {
            error("Expected identifier, found " + tk.convert_to_string());
        }

        if(localVariables.find(tk.identifierValue) != localVariables.end())
        {
            error("Multiple declarations of local variable " + tk.identifierValue);
        }


        llvm::AllocaInst * local = pBuilder->CreateAlloca(llvm::IntegerType::getInt32Ty(context),
                                                          nullptr,
                                                          tk.identifierValue);

        // align 4 ensures that the address will be a multiple of 4
        local->setAlignment(llvm::Align(4));
        localVariables[tk.identifierValue] = local;
        tk = lexer.next();
    }

    tk = lexer.next();
    return localVariables;
}

llvm::Module* ExprParser::parse(llvm::Module* Mod, llvm::LLVMContext& context)
{
    Mod->setDataLayout("e-m:e-i64:64-f80:128-n8:16:32:64-S128");
    Mod->setTargetTriple("x86_64-pc-linux-gnu");

    //Create IntType
    auto IntType = llvm::IntegerType::getInt32Ty(context);
    // Start parsing, bring first lookahead token
    tk = lexer.next();

    while(tk.type != ExprToken::EndOfData)
    {
        // IR = Intermediate Representation
        // an IRBuilder internally maintains a current basic block and a pointer inside the block’s list of instructions.
        // When a new instruction is added, it is inserted at that point, and then the pointer is advanced after the new instruction.
        pBuilder = new llvm::IRBuilder<>(context);

        std::string                 FunctionName = parseFunctionName();

        std::unordered_map<std::string, llvm::Argument*> FunctionParamMap;
        std::unordered_map<std::string, llvm::AllocaInst*> LocalVariables;
        std::vector<std::string>    FunctionParamVector = parseFunctionParam();
        std::vector<llvm::Type*>    FunctionParamTypes(FunctionParamVector.size(), IntType);


        // function type
        llvm::FunctionType*         FunctionTypes = llvm::FunctionType::get(IntType,
                                                                        FunctionParamTypes,
                                                                        false);

        // create the function prototype
        llvm::Function* func = llvm::Function::Create(FunctionTypes,
                                                      llvm::GlobalValue::ExternalLinkage,
                                                      FunctionName,
                                                      Mod);

        // set calling conversion
        func->setCallingConv(llvm::CallingConv::C);


        // function body
        llvm::BasicBlock* body = llvm::BasicBlock::Create(context,
                                                          "",
                                                          func);
        pBuilder->SetInsertPoint(body);



        // iterate through map and add the function params
        llvm::Function::arg_iterator args = func->arg_begin();
        for(std::string arg_name : FunctionParamVector)
        {
            if(FunctionParamMap.find(arg_name) != FunctionParamMap.end())
            {
                error("Multiple arguments with name " + arg_name);
            }
            llvm::Argument* curr_arg = &(*args++);
            curr_arg->setName(arg_name);
            FunctionParamMap[arg_name] = curr_arg;
        }


        if(!(tk.type == ExprToken::Symbol && tk.symbolValue == '{'))
        {
            error("Expecting {, found " + tk.convert_to_string());
        }
        tk = lexer.next();


        LocalVariables = parseLocalVariables(context);

        while(tk.type != ExprToken::Return) //&& tk.symbolValue != '{'
        {
            if(tk.type != ExprToken::Id)
            {
                error("Expecting identifier, found " + tk.convert_to_string());
            }

            if(LocalVariables.find(tk.identifierValue) == LocalVariables.end())
            {
                error("Unknown identifier "+tk.identifierValue);
            }

            std::string identifier = tk.identifierValue;

            tk = lexer.next();// ','

            if(tk.type != ExprToken::Symbol || tk.symbolValue != '=')
            {
                error("Expecting '=', found " + tk.convert_to_string());
            }
            tk = lexer.next();

            llvm::Value * val = parseExpr(FunctionParamMap, LocalVariables, context);
            pBuilder->CreateStore(val, LocalVariables[identifier]);

            tk = lexer.next();
        }

        // parse function's end
        if(tk.type != ExprToken::Return)
        {
            error("Expected return, found " + tk.convert_to_string());
        }
        tk = lexer.next();


        llvm::Value * val = parseExpr(FunctionParamMap,
                                      LocalVariables,
                                      context);


        if(tk.type != ExprToken::Symbol || tk.symbolValue != ';')
        {
            error("Expecting ;, found " + tk.convert_to_string());
        }
        tk = lexer.next();



        if(tk.type != ExprToken::Symbol || tk.symbolValue != '}')
        {
            error("Expecting }, found " + tk.convert_to_string());
        }

        pBuilder->CreateRet(val);
        tk = lexer.next();

        delete pBuilder;
        pBuilder = nullptr;
    }

    if (tk.type != ExprToken::EndOfData)
    {
        error("Extra characters after expression.\n");
    }

    return Mod;
}

