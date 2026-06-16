	.file	"end.S"
	.option nopic
	.attribute arch, "rv32i2p0"
	
	.text
	.align	4
	.globl	_Exit
	.type	_Exit, @function

_Exit:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
.L2:
	j	.L2
	
	.size	_Exit, .-_Exit
	.ident	"GCC: (g2ee5e430018) 12.2.0"
