	.text
	.file	"testbasic.ll"
	.globl	pi100                           # -- Begin function pi100
	.p2align	4, 0x90
	.type	pi100,@function
pi100:                                  # @pi100
	.cfi_startproc
# %bb.0:
	movl	$314, %eax                      # imm = 0x13A
	retq
.Lfunc_end0:
	.size	pi100, .Lfunc_end0-pi100
	.cfi_endproc
                                        # -- End function
	.globl	e1000                           # -- Begin function e1000
	.p2align	4, 0x90
	.type	e1000,@function
e1000:                                  # @e1000
	.cfi_startproc
# %bb.0:
	movl	$2718, %eax                     # imm = 0xA9E
	retq
.Lfunc_end1:
	.size	e1000, .Lfunc_end1-e1000
	.cfi_endproc
                                        # -- End function
	.globl	ref17k                          # -- Begin function ref17k
	.p2align	4, 0x90
	.type	ref17k,@function
ref17k:                                 # @ref17k
	.cfi_startproc
# %bb.0:
	movl	$17460, %eax                    # imm = 0x4434
	retq
.Lfunc_end2:
	.size	ref17k, .Lfunc_end2-ref17k
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
