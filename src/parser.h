#ifndef _PARSER_H_
#define _PARSER_H_

#include "lexer.h"
#include <string>
#include <unordered_map>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

class ExprParser
{
    ExprLexer lexer;
    ExprToken tk;
    llvm::IRBuilder<> *pBuilder=nullptr;
    llvm::Value*                parseExpr(std::unordered_map<std::string, llvm::Argument*> FunctionParamMap, std::unordered_map<std::string, llvm::AllocaInst*> LocalVariablesMap, llvm::LLVMContext& context);
    llvm::Value*                parseTerm(std::unordered_map<std::string, llvm::Argument*> FunctionParamMap, std::unordered_map<std::string, llvm::AllocaInst*> LocalVariablesMap, llvm::LLVMContext& context);
    llvm::Value*                parseFact(std::unordered_map<std::string, llvm::Argument*> FunctionParamMap, std::unordered_map<std::string, llvm::AllocaInst*> LocalVariablesMap, llvm::LLVMContext& context);
    std::string                 parseFunctionName();
    std::vector<std::string>    parseFunctionParam();
    std::unordered_map<std::string, llvm::AllocaInst*> parseLocalVariables(llvm::LLVMContext& context);

public:
    ExprParser(const std::string& expression) : lexer(expression) {}
    llvm::Module* parse(llvm::Module* Mod, llvm::LLVMContext& context) ;
};

#endif

