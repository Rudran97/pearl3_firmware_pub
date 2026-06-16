  .file	  "vectors.S"

  .section .vectors, "ax"
  .option  norvc
  
  .global  INT0_ISR_VECTOR
  .global  INT1_ISR_VECTOR
  .global  INT2_ISR_VECTOR
  .global  INT3_ISR_VECTOR
  .global  INT4_ISR_VECTOR
  .global  INT5_ISR_VECTOR
  .global  INT6_ISR_VECTOR
  .global  INT7_ISR_VECTOR
  .global  exception_handler

  .global  INT0_handler
  .global  INT1_handler
  .global  INT2_handler
  .global  INT3_handler
  .global  INT4_handler
  .global  INT5_handler
  .global  INT6_handler
  .global  INT7_handler

#define IRQID_REG_OFFSET (17 << 2)

/* Exception codes */
#define EXC_ILL_INSN 2
#define EXC_BREAK    3
#define EXC_ECALL    11 
#define EXC_UNKWN    0xff

/* ------------------------------ */
/* Vectors in fast interrupt mode */

  .balign 4
INT0_ISR_VECTOR:
    call INT0_handler
    mret

  .balign 64
INT1_ISR_VECTOR:
    call INT1_handler
    mret

  .balign 64
INT2_ISR_VECTOR:
    call INT2_handler
    mret

  .balign 64
INT3_ISR_VECTOR:
    call INT3_handler
    mret

  .balign 64
INT4_ISR_VECTOR:
    call INT4_handler
    mret

  .balign 64
INT5_ISR_VECTOR:
    call INT5_handler
    mret

  .balign 64
INT6_ISR_VECTOR:
    call INT6_handler
    mret

  .balign 64
INT7_ISR_VECTOR:
    call INT7_handler
    mret

/* ------------------------------ */
/* Calls to interrupt handlers when mtvec.MODE = 0 */

call_INT0:
    call INT0_handler
    j    end_handler_ret

call_INT1:
    call INT1_handler
    j    end_handler_ret

call_INT2:
    call INT2_handler
    j    end_handler_ret

call_INT3:
    call INT3_handler
    j    end_handler_ret

call_INT4:
    call INT4_handler
    j    end_handler_ret

call_INT5:
    call INT5_handler
    j    end_handler_ret

call_INT6:
    call INT6_handler
    j    end_handler_ret

call_INT7:
    call INT7_handler
    j    end_handler_ret

/* ------------------------------ */
/* Exception handler. Also handles interrupts when mtvec.MODE = 0 */

  .balign 64
  .weak  exception_handler

exception_handler:
    addi    sp,   sp, -64
	sw      ra,   0(sp)
	sw      a0,   4(sp)
	sw      a1,   8(sp)
	sw      a2,   12(sp)
	sw      a3,   16(sp)
	sw      a4,   20(sp)
	sw      a5,   24(sp)
	sw      a6,   28(sp)
	sw      a7,   32(sp)
	sw      t0,   36(sp)
	sw      t1,   40(sp)
	sw      t2,   44(sp)
	sw      t3,   48(sp)
	sw      t4,   52(sp)
	sw      t5,   56(sp)
	sw      t6,   60(sp)

	csrr    t0,   mcause
    bge     t0,   zero, sync_exceptions    /* for async exceptions i.e. interrupts
                                            * t0 would evaluate to -ve (bit 31 is set)
                                            */
interrupts:
    lui     a5,   %hi(__plic_origin)
    lw      t0,   IRQID_REG_OFFSET(a5)     /* read the irq id from the clic module to
                                            * manually determine which isr routine to
                                            * execute.
                                            */
    li      t1,   0
    beq     t0,   t1, call_INT0
    li      t1,   1
    beq     t0,   t1, call_INT1
    li      t1,   2
    beq     t0,   t1, call_INT2
    li      t1,   3
    beq     t0,   t1, call_INT3
    li      t1,   4
    beq     t0,   t1, call_INT4
    li      t1,   5
    beq     t0,   t1, call_INT5
    li      t1,   6
    beq     t0,   t1, call_INT6
    li      t1,   7
    beq     t0,   t1, call_INT7

    j       end_handler_ret
    
sync_exceptions:
	li      t1,   EXC_ILL_INSN
	beq     t0,   t1, handle_illegal_insn
	li      t1,   EXC_ECALL
	beq     t0,   t1, handle_ecall
	li      t1,   EXC_BREAK
	beq     t0,   t1, handle_ebreak
	j       handle_unknown

    /* Output the EXC code on on-board LEDs */

handle_illegal_insn:
    li      a0,   EXC_ILL_INSN
    la      a5,   __latd
    sw      a0,   0(a5)
	j       end_handler_incr_mepc

handle_ecall:
    li      a0,   EXC_ECALL
    la      a5,   __latd
    sw      a0,   0(a5)
	j       end_handler_incr_mepc

handle_ebreak:
    li      a0,   EXC_BREAK
    la      a5,   __latd
    sw      a0,   0(a5)
	j       end_handler_incr_mepc


handle_unknown:
    li      a0,   EXC_UNKWN
    la      a5,   __latd
    sw      a0,   0(a5)
	j       end_handler_ret

end_handler_incr_mepc:
	csrr    t0,   mepc
    csrr    t2,   mtval   /* mtval contains the exception instruction */ 
    andi    t3,   t2, 1
	/* Increment mepc by 2 or 4 depending on whether the instruction at mepc
	   is compressed or not.  */
    beqz    t3,   end_handler_incr_mepc2
	addi    t0,   t0, 2
end_handler_incr_mepc2:
	addi    t0,   t0, 2
	csrw    mepc, t0
end_handler_ret:
	lw      ra,   0(sp)
	lw      a0,   4(sp)
	lw      a1,   8(sp)
	lw      a2,   12(sp)
	lw      a3,   16(sp)
	lw      a4,   20(sp)
	lw      a5,   24(sp)
	lw      a6,   28(sp)
	lw      a7,   32(sp)
	lw      t0,   36(sp)
	lw      t1,   40(sp)
	lw      t2,   44(sp)
	lw      t3,   48(sp)
	lw      t4,   52(sp)
	lw      t5,   56(sp)
	lw      t6,   60(sp)
	addi    sp,   sp, 64
#ifdef HLT_ON_EXCEPTION
    j       _Exit
#else
	mret
#endif


