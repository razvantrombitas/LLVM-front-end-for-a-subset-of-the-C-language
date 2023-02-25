# LLVM front-end for a subset of the C language

Create a front-end for LLVM that
* understands a small subset of the C language
* receives the name of the C file as a command line argument
* generates LLVM IR code for the x86_64 architecture / Linux ABI using the IRBuilder library in LLVM

The C language support is limited to simple C functions like:

```c
int pi100() {
   return 314;
}

int f(int a, int b, int c) {
  return b * b - 4 * a * c;
}

int f(int a, int b, int c) {
  int x, y;
  x = b * b;
  y = 4 * a * c;
  x = x - y;
  return x;
}
```
## Step 1 - functions that evaluate an integer expression
Limitations:
- functions do not have any parameters;
- the return value is int;
- only one statement in function (return)
- only math expressions: + , - , * and parenthees
- all operands in the expression are int constants

## Step 2 - functions that evaluate an expression, including parameters
Limitations:
- all parameters are int;
- the return value is int;
- only one statement in function (return)
- only math expressions: + , - , *
- no local variables - just parameters, int constants and parentheses

## Step 3 - functions with local variables
Limitations:
- all local variables are int
- all local variables are declared on one line
- variables are not initialized when they are declared
- incoming arguments cannot be assigned new values; only local variables can be on the left side of an assigment (lvalues)
- the last instruction in the function is return
- all other instructions are assignments


## Prerequisites

The assigment requires LLVM development libraries, version 10 to 15 .

Recent Linux distributions should already contain one of these LLVM versions; for example in Ubuntu, LLVM can be installed by:
```
sudo apt install llvm llvm-dev
```

To check the version of LLVM use the command: `llvm-config --version`

## Resources
- [LLVM Programmer’s Manual](https://llvm.org/docs/ProgrammersManual.html)
- [LLVM Intermediate Language Reference Manual](https://llvm.org/docs/LangRef.html)

## Examples of C functions and generated code

The `test` directory contains three test C files

- `testbasic.c` - Step 1: Simple C functions computing arithmetic expressions
- `testfunc.c` - Step 2: Simple to more complex C functions
- `testlocals.c` - Step 3: C functions with local variables

The `reference-output` directory contains the output of a correct reference implementation for the following scenarios:
- `test1.output` - Expected output from running step 1.
- `test2.output` - Expected output from running step 2.
- `test3.output` - Expected output from running step 3.


## How to build and run the program

To build: `make`

To build and run only step 1: `make test1`

To build and run steps 1 and 2: `make test2`

To build and run all steps: `make test3`

To clean up: `make clean`

Use `make -n` to list the commands required to build and run the code

