    .file "start_freertos.S"
    
    .section .startup, "ax"

    .globl	main
    .globl  __global_pointer$
    .globl  _sp
    .globl  _enter

    .globl freertos_risc_v_trap_handler
    
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
    /* ecall and ebreak would be handled by freertos_risc_v_trap_handler.
     * mtvec.MODE = 0 would be used with external interrupt as the main
     * interrupt source.
     */
    la      a5,    freertos_risc_v_trap_handler
    csrw    mtvec, a5 
#endif

    la      sp,   _sp
    jal     zero, main
    jal     zero, _Exit

/*-----------------------------------------------------------*/

_Exit:
.L2:
	j	.L2