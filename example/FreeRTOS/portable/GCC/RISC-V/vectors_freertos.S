  .file	  "vectors_freertos.S"

#include "portContext.h"

  .section .vectors, "ax"
  .option  norvc
  
  .extern  INT0_handler
  .extern  INT1_handler
  .extern  INT2_handler
  .extern  INT3_handler
  .extern  INT4_handler
  .extern  INT5_handler
  .extern  INT7_handler
  .extern  processed_source

  .global  call_INT0
  .global  call_INT1
  .global  call_INT2
  .global  call_INT3
  .global  call_INT4
  .global  call_INT5
  .global  call_INT7

/* ------------------------------ */
/* Calls to interrupt handlers when mtvec.MODE = 0 */

call_INT0:
    call INT0_handler
    j    processed_source

call_INT1:
    call INT1_handler
    j    processed_source

call_INT2:
    call INT2_handler
    j    processed_source

call_INT3:
    call INT3_handler
    j    processed_source

call_INT4:
    call INT4_handler
    j    processed_source

call_INT5:
    call INT5_handler
    j    processed_source

call_INT7:
    call INT7_handler
    j    processed_source