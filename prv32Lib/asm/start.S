    .file "start.S"
    
    .section .startup, "ax"

    .globl	main
    .globl  __global_pointer$
    .globl  _sp
    .globl  _enter
    .globl  _Exit

    .globl INT0_ISR_VECTOR
    .globl INT1_ISR_VECTOR
    .globl INT2_ISR_VECTOR
    .globl INT3_ISR_VECTOR
    .globl INT4_ISR_VECTOR
    .globl INT5_ISR_VECTOR
    .globl INT6_ISR_VECTOR
    .globl INT7_ISR_VECTOR
    .globl exception_handler
    
    .type	_enter, @function
    
_enter:
    .option push
    .option norelax

    la      t0,   _bss_start
    la      t1,   _bss_end

.L0:
    /* Zero bss section */
    sw      zero, 0(t0)
    addi    t0,   t0, 4
    bltu    t0,   t1, .L0
    
    /* gp is set to io_orgin */
    la      gp,   __global_pointer$
    
    .option pop

#ifdef PRVX3IMC48SH
    la      a5,    exception_handler
    ori     a5,    a5, 2      /* MODE 2 : fast IRQ */
    csrw    mtvec, a5 
#endif

    la      sp,   _sp

    lui     a5,   %hi(__plic_origin)
    
    /* The INTx_ISR_VECTOR is always in 16 bit address from _enter. So to save code space we ignore
    the upper 16 bits of the address */
    addi    a4,   zero, %lo(INT0_ISR_VECTOR)
    sw      a4,   0x00(a5)

    addi    a4,   zero, %lo(INT1_ISR_VECTOR)
    sw      a4,   0x04(a5)

    addi    a4,   zero, %lo(INT2_ISR_VECTOR)
    sw      a4,   0x08(a5)

    addi    a4,   zero, %lo(INT3_ISR_VECTOR)
    sw      a4,   0x0c(a5)

    addi    a4,   zero, %lo(INT4_ISR_VECTOR)
    sw      a4,   0x10(a5)

    addi    a4,   zero, %lo(INT5_ISR_VECTOR)
    sw      a4,   0x14(a5)

    addi    a4,   zero, %lo(INT6_ISR_VECTOR)
    sw      a4,   0x18(a5)

    addi    a4,   zero, %lo(INT7_ISR_VECTOR)
    sw      a4,   0x1c(a5)

    jal     zero, main

    jal     zero, _Exit

    .size	_enter, .-_enter
	.ident	"GCC: (g2ee5e430018) 12.2.0"