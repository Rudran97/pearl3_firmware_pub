# execute from project folder: gdb build/main.elf -x init.gdb

# launch gdb-dashboard
source ../../Utility/debugger/.gdbinit
# set mmio variables to access mmio registers. Use p/x *$name
source ../../Utility/debugger/prvx32_mmio.gdb

directory ../../prv32Lib/src
directory ../../prv32Lib/asm
directory ../../prv32Lib/asm/interrupts
directory ../../libraries
directory ../FreeRTOS
directory ../FreeRTOS/portable/GCC/RISC-V

dashboard -layout csr registers breakpoints assembly source stack variables

define reset
    monitor reset halt
end

define halt
    monitor halt
end

define status
    monitor status
end

target remote :3333
reset
halt
break main
continue
