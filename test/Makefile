TEST_ARGS:=0
TEST_LOCALS:=0

TEST_SRC=testbasic.c 
ifeq (${TEST_ARGS},1)
TEST_SRC+=testfunc.c
endif
ifeq (${TEST_LOCALS},1)
TEST_SRC+=testlocals.c
endif
TEST_ASM=$(TEST_SRC:.c=.s)

test:
	gcc -o testgcc -DTEST_ARGS=${TEST_ARGS} -DTEST_LOCALS=${TEST_LOCALS} ${TEST_SRC} testmain.c
	./testgcc > testgcc.result
	@echo
	@echo === TEST GCC ===
	@echo
	@cat testgcc.result
	@echo
	../src/compiler testbasic.c
ifeq (${TEST_ARGS},1)
	../src/compiler testfunc.c
endif
ifeq (${TEST_LOCALS},1)
	../src/compiler testlocals.c
endif
	@echo
	@echo === GENERATED CODE ===
	@echo
	@cat testbasic.ll
ifeq (${TEST_ARGS},1)
	@cat testfunc.ll
endif
ifeq (${TEST_LOCALS},1)
	@cat testlocals.ll
endif
	@echo
	llc testbasic.ll
ifeq (${TEST_ARGS},1)
	llc testfunc.ll
endif
ifeq (${TEST_LOCALS},1)
	llc testlocals.ll
endif
	gcc -o testcompiler -DTEST_ARGS=${TEST_ARGS} -DTEST_LOCALS=${TEST_LOCALS} ${TEST_ASM} testmain.c
	./testcompiler > testcompiler.result
	@echo
	@echo === TEST COMPILER ===
	@echo
	@cat testcompiler.result
	@echo
	-@diff -q testgcc.result testcompiler.result && echo PASSED || echo FAILED
	@echo
	@echo === ERROR TESTING ===
ifeq (${TEST_ARGS},1)
	-../src/compiler err_duplicateargs.c
	-../src/compiler err_missingsymbol.c
endif
ifeq (${TEST_LOCALS},1)
	-../src/compiler err_missingvariable.c
endif
	
clean:
	rm -f *.result *.o testgcc testcompiler *.s *.ll

