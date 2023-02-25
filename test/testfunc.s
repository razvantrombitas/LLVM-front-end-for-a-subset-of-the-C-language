	.text
	.file	"testfunc.ll"
	.globl	circleArea100                   # -- Begin function circleArea100
	.p2align	4, 0x90
	.type	circleArea100,@function
circleArea100:                          # @circleArea100
	.cfi_startproc
# %bb.0:
	imull	%edi, %edi
	imull	$314, %edi, %eax                # imm = 0x13A
	retq
.Lfunc_end0:
	.size	circleArea100, .Lfunc_end0-circleArea100
	.cfi_endproc
                                        # -- End function
	.globl	mac                             # -- Begin function mac
	.p2align	4, 0x90
	.type	mac,@function
mac:                                    # @mac
	.cfi_startproc
# %bb.0:
                                        # kill: def $esi killed $esi def $rsi
                                        # kill: def $edi killed $edi def $rdi
	imull	%edx, %esi
	leal	(%rsi,%rdi), %eax
	retq
.Lfunc_end1:
	.size	mac, .Lfunc_end1-mac
	.cfi_endproc
                                        # -- End function
	.globl	f                               # -- Begin function f
	.p2align	4, 0x90
	.type	f,@function
f:                                      # @f
	.cfi_startproc
# %bb.0:
	movl	%esi, %eax
	imull	%esi, %eax
	imull	%edx, %edi
	shll	$2, %edi
	subl	%edi, %eax
	retq
.Lfunc_end2:
	.size	f, .Lfunc_end2-f
	.cfi_endproc
                                        # -- End function
	.globl	pnd                             # -- Begin function pnd
	.p2align	4, 0x90
	.type	pnd,@function
pnd:                                    # @pnd
	.cfi_startproc
# %bb.0:
	imull	%edx, %edi
	movl	$100, %eax
	subl	%edx, %eax
	imull	%esi, %eax
	addl	%edi, %eax
	imull	%ecx, %eax
	retq
.Lfunc_end3:
	.size	pnd, .Lfunc_end3-pnd
	.cfi_endproc
                                        # -- End function
	.globl	rcubed                          # -- Begin function rcubed
	.p2align	4, 0x90
	.type	rcubed,@function
rcubed:                                 # @rcubed
	.cfi_startproc
# %bb.0:
	movl	%edi, %eax
	imull	%edi, %eax
	imull	%edi, %eax
	retq
.Lfunc_end4:
	.size	rcubed, .Lfunc_end4-rcubed
	.cfi_endproc
                                        # -- End function
	.globl	volume                          # -- Begin function volume
	.p2align	4, 0x90
	.type	volume,@function
volume:                                 # @volume
	.cfi_startproc
# %bb.0:
	movl	%edi, %eax
	imull	%esi, %eax
	imull	%edx, %eax
	imull	%esi, %eax
	retq
.Lfunc_end5:
	.size	volume, .Lfunc_end5-volume
	.cfi_endproc
                                        # -- End function
	.globl	Taylor_1_div_x                  # -- Begin function Taylor_1_div_x
	.p2align	4, 0x90
	.type	Taylor_1_div_x,@function
Taylor_1_div_x:                         # @Taylor_1_div_x
	.cfi_startproc
# %bb.0:
	decl	%edi
	movl	%edi, %ecx
	imull	%edi, %ecx
	movl	%ecx, %eax
	subl	%edi, %eax
	imull	%edi, %ecx
	subl	%ecx, %eax
	incl	%eax
	retq
.Lfunc_end6:
	.size	Taylor_1_div_x, .Lfunc_end6-Taylor_1_div_x
	.cfi_endproc
                                        # -- End function
	.globl	xx                              # -- Begin function xx
	.p2align	4, 0x90
	.type	xx,@function
xx:                                     # @xx
	.cfi_startproc
# %bb.0:
                                        # kill: def $esi killed $esi def $rsi
                                        # kill: def $edi killed $edi def $rdi
	subl	%esi, %edi
	leal	(%rdi,%rdi,4), %eax
	subl	%edx, %esi
	leal	(%rsi,%rsi,4), %esi
	subl	%ecx, %edx
	movl	%edx, %ecx
	shll	$5, %ecx
	movl	%edx, %edi
	subl	%ecx, %edi
	addl	%edx, %edi
	leal	(%rdi,%rsi,4), %ecx
	leal	(%rcx,%rax,2), %eax
	negl	%eax
	retq
.Lfunc_end7:
	.size	xx, .Lfunc_end7-xx
	.cfi_endproc
                                        # -- End function
	.globl	deepExp                         # -- Begin function deepExp
	.p2align	4, 0x90
	.type	deepExp,@function
deepExp:                                # @deepExp
	.cfi_startproc
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
                                        # kill: def $ecx killed $ecx def $rcx
                                        # kill: def $edx killed $edx def $rdx
                                        # kill: def $esi killed $esi def $rsi
                                        # kill: def $edi killed $edi def $rdi
	leal	(%rsi,%rsi), %r8d
	leal	(%rdx,%rdx,2), %r9d
	leal	(%rdi,%rdi,4), %r10d
	leal	(,%rsi,4), %r11d
	movl	%edx, %ebx
	shll	$5, %ebx
	addl	%edx, %ebx
	movl	%ecx, %eax
	shll	$5, %eax
	leal	(%rax,%rcx,2), %eax
	subl	%eax, %ebx
	leal	(%rsi,%rsi,4), %eax
	leal	(%rsi,%rax,4), %eax
	addl	%esi, %eax
	shll	$5, %esi
	subl	%esi, %ebx
	movl	%edi, %esi
	shll	$5, %esi
	subl	%edi, %esi
	addl	%esi, %ebx
	leal	(,%rcx,8), %esi
	leal	(%rsi,%rsi,2), %esi
	subl	%esi, %ebx
	leal	(,%r9,8), %esi
	subl	%edx, %esi
	addl	%esi, %ebx
	movl	%ecx, %esi
	shll	$4, %esi
	subl	%eax, %ebx
	leal	(%rdi,%r10,4), %eax
	addl	%eax, %ebx
	movl	%ecx, %eax
	subl	%esi, %eax
	addl	%ecx, %eax
	addl	%ebx, %eax
	leal	(%rdx,%r9,4), %edx
	addl	%edx, %eax
	leal	(%r11,%r11,2), %edx
	subl	%edx, %eax
	leal	(%rdi,%r10,2), %edx
	addl	%edx, %eax
	leal	(,%rcx,4), %ecx
	subl	%ecx, %eax
	addl	%r9d, %eax
	subl	%r8d, %eax
	addl	%edi, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end8:
	.size	deepExp, .Lfunc_end8-deepExp
	.cfi_endproc
                                        # -- End function
	.globl	scalarProd_3d                   # -- Begin function scalarProd_3d
	.p2align	4, 0x90
	.type	scalarProd_3d,@function
scalarProd_3d:                          # @scalarProd_3d
	.cfi_startproc
# %bb.0:
                                        # kill: def $esi killed $esi def $rsi
                                        # kill: def $edi killed $edi def $rdi
	imull	%ecx, %edi
	imull	%r8d, %esi
	leal	(%rsi,%rdi), %eax
	imull	%r9d, %edx
	addl	%edx, %eax
	retq
.Lfunc_end9:
	.size	scalarProd_3d, .Lfunc_end9-scalarProd_3d
	.cfi_endproc
                                        # -- End function
	.globl	point_cross_diff                # -- Begin function point_cross_diff
	.p2align	4, 0x90
	.type	point_cross_diff,@function
point_cross_diff:                       # @point_cross_diff
	.cfi_startproc
# %bb.0:
	movl	%esi, %eax
	imull	%r9d, %eax
	imull	%r8d, %edx
	subl	%edx, %eax
	retq
.Lfunc_end10:
	.size	point_cross_diff, .Lfunc_end10-point_cross_diff
	.cfi_endproc
                                        # -- End function
	.globl	det3                            # -- Begin function det3
	.p2align	4, 0x90
	.type	det3,@function
det3:                                   # @det3
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset %rbx, -24
	.cfi_offset %rbp, -16
	movl	24(%rsp), %r10d
	movl	32(%rsp), %eax
	movl	40(%rsp), %r11d
	movl	%r8d, %ebx
	imull	%r11d, %ebx
	movl	%r9d, %ebp
	imull	%eax, %ebp
	subl	%ebp, %ebx
	imull	%edi, %ebx
	imull	%ecx, %r11d
	imull	%r10d, %r9d
	subl	%r9d, %r11d
	imull	%esi, %r11d
	subl	%r11d, %ebx
	imull	%ecx, %eax
	imull	%r10d, %r8d
	subl	%r8d, %eax
	imull	%edx, %eax
	addl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end11:
	.size	det3, .Lfunc_end11-det3
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
