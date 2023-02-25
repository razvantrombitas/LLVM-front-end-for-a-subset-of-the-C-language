#include <string>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/FormatVariadic.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include "parser.h"


// Print standardized error messages and exit the program
// error("Syntax error", "test.c", 10) prints "test.c:10:error: Syntax error"

void error(const std::string &message, const char *sourceFile = nullptr, int lineNumber = 0)
{
	if (sourceFile)
	{
		llvm::outs() << sourceFile << ":";
		if (lineNumber)
			llvm::outs() << lineNumber << ":";
	}

	llvm::outs() << "error: " << message << "\n";
	exit(1);
}

llvm::LLVMContext llvmContext;

// Parse input and generate code into a LLVM Module
llvm::Module *compile(const std::string &input, const char *llFileName)
{
    // Create the module
    llvm::Module* mod = new llvm::Module(llFileName, llvmContext);
    ExprParser p(input);
    mod = p.parse(mod, llvmContext);

    return mod;
}

int main(int argc, char** argv) {

	// Read arguments and copmute output file name
	if (argc != 2)
	{
		llvm::outs() << "Usage: compiler <file>.c\n";
		return 1;
	}

	std::string cFileName(argv[1]);
	if (cFileName.rfind(".c", cFileName.size()-2) == std::string::npos)
		error(llvm::formatv("File name {0} does not end with .c", cFileName));
	std::string llFileName = cFileName.substr(0,cFileName.size()-2) + ".ll";

	// Read the contents of the input C file into a std::string, then pass it to the compile() function

	// Read file into a llvm memory buffer
	auto inFile = llvm::MemoryBuffer::getFile(cFileName);
	if (inFile.getError())
		error("Cannot read input file", cFileName.c_str());

	// Read the memory buffer into a std::string, the pass it to compile()
	llvm::Module *module = compile((*inFile)->getBuffer().str(), llFileName.c_str());

	// Write the LLVM Module as assembler into the output .ll file

	// Open .ll file for reading
	std::error_code err;
	llvm::raw_fd_ostream output(module->getName(), err, llvm::sys::fs::OF_Text);
	if (err)
		error(err.message(), cFileName.c_str());

	// print module into .ll file
	module->print(output, nullptr);

	return 0;

}
