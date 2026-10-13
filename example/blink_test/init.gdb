# execute from project folder: gdb build/main.elf -x init.gdb

# launch gdb-dashboard
source ../../utility/debugger/.gdbinit
# set mmio variables to access mmio registers. Use p/x *$name
source ../../utility/debugger/prvx32_mmio.gdb

directory ../../prv32Lib/src
directory ../../prv32Lib/asm
directory ../../prv32Lib/asm/interrupts
directory ../../libraries
directory ../FreeRTOS
directory ../FreeRTOS/portable/GCC/RISC-V

dashboard -layout csr registers clic peripherals breakpoints assembly source stack variables

define reset
    monitor reset halt
end

define halt
    monitor halt
end

define status
    monitor status
end

define target_flash
    monitor capture
    load build/main.elf
    monitor flash
end

define enable_break
    monitor ebreakm 1
end

define disable_break
    monitor ebreakm 0
end

target remote :3333
reset
halt
break main
continue
