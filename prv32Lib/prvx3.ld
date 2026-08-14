OUTPUT_ARCH( "riscv" )
ENTRY( _enter )

INCLUDE "PRVX348.ld"

PROVIDE(__global_pointer$ = __io_origin);

PROVIDE(_Exit = 0x80000000);

MEMORY
{ 
  FLASH (rx)  : ORIGIN = 0x80000000, LENGTH = FLASH_SIZE
  RAM   (rwx) : ORIGIN = 0x10000000, LENGTH = RAM_SIZE
}


SECTIONS
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 4K;
  __heap_size = DEFINED(__heap_size) ? __heap_size : 10K;

  /* Flash begins at 0x8000_0000 */
  . = ORIGIN(FLASH);
  .startup :
  {
    KEEP(*(.startup))
    KEEP(*(.startup.*))
  } > FLASH
  . = ALIGN(4);

  .vectors :
  {
    KEEP(*(.vectors))
    KEEP(*(.vectors.*))
  } >FLASH
  . = ALIGN(4);

  .text :
  {
    *(.text .text.*)
    . = ALIGN(4);
    /* Always add a nop instruction at the end for alignment
     * as the programmer expects 32-bit data size. */
    LONG(0x00000013)
  } >FLASH
  . = ALIGN(4);

  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);

  PROVIDE(INT0_handler = _Exit);
  PROVIDE(INT1_handler = _Exit);
  PROVIDE(INT2_handler = _Exit);
  PROVIDE(INT3_handler = _Exit);
  PROVIDE(INT4_handler = _Exit);
  PROVIDE(INT5_handler = _Exit);
  PROVIDE(INT6_handler = _Exit);
  PROVIDE(INT7_handler = _Exit);

  _sidata = .;
  .data :
  {
    _sdata = .;
    *(.rdata) 
    *(.data .data.*)
    *(.sdata .sdata.*)
    *(.rodata .rodata.*)  
    *(.srodata .srodata.*)
    . = ALIGN(4);
    _edata = .;
  } >RAM

  PROVIDE( _edata = . );
  PROVIDE( edata = . );
  PROVIDE( _fbss = . );
  PROVIDE( __bss_start = . );
  PROVIDE( _bss_start = .);

  .bss : ALIGN(4)
  {
    _sbss = .;
    *(.sbss*)
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM

  . = ALIGN(8);
  PROVIDE( _end = . );
  PROVIDE( end = . );
  PROVIDE( _bss_end = .);
  
  .heap :
  {
  	_heap_start = . ;
    . = . + __heap_size;
    . = ALIGN(4);
    _heap_end = . ;
  } >RAM

  .stack :
  {
    _stack_bottom = ORIGIN(RAM) + LENGTH(RAM);
    _stack_top = _stack_bottom - __stack_size;
    PROVIDE( _sp = _stack_bottom);
    PROVIDE( _stack = _sp);
  } >RAM
}
