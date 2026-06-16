# Include device specific settings
include prv_device.mk

# GCC toolchain programs.
RISCV_PREFIX = riscv32-unknown-elf-
CC = $(RISCV_PREFIX)gcc
OC = $(RISCV_PREFIX)objcopy
OD = $(RISCV_PREFIX)objdump
OS = $(RISCV_PREFIX)size
DB = gdb

ifeq ($(DEVICE_ID), PRV32IMX1515)
architecture = rv32im
else ifeq ($(DEVICE_ID), PRVX3IMC48SH)
architecture = rv32imc_zicsr
endif

# Python.
PY = python3

PROGRAM_CONFIGS += $(UTILITY_PATH)/$(LOADER_NAME)
PROGRAM_CONFIGS += -f $(UPLOAD_FILE_PATH)
PROGRAM_CONFIGS += -p $(PORT_NAME)
PROGRAM_CONFIGS += -s $(PROGRAM_SPEED)
PROGRAM_CONFIGS += --device $(DEVICE_ID)

OBJDIR = ./build

# Assembly directives.
ASFLAGS += -c
ASFLAGS += -O0
ASFLAGS += -Wall
ASFLAGS += -g3 -ggdb
ASFLAGS += -fmessage-length=0
ASFLAGS += -march=$(architecture)
ASFLAGS += -mabi=ilp32
ASFLAGS += -mcmodel=medlow
ASFLAGS += -D $(DEVICE_ID)

# C compilation directives
CFLAGS += -c
CFLAGS += -Wall
CFLAGS += -O2
CFLAGS += -g3 -ggdb
CFLAGS += -fmessage-length=0
CFLAGS += --specs=nosys.specs
CFLAGS += -march=$(architecture)
CFLAGS += -mabi=ilp32
CFLAGS += -mcmodel=medlow
CFLAGS += -D $(DEVICE_ID)
# CFLAGS += -S

# Linker directives.
LFLAGS += -Wall
LFLAGS += -Wl,--relax
LFLAGS += -Wl,--gc-sections
# LFLAGS += -Wl,--verbose
LFLAGS += -nostdlib
LFLAGS += -nostartfiles
LFLAGS += -lc
LFLAGS += -lgcc
LFLAGS += --specs=nosys.specs
LFLAGS += -march=$(architecture)
LFLAGS += -mabi=ilp32
LFLAGS += -mcmodel=medlow
LFLAGS += -T$(LINKER)
LFLAGS += -L$(PRV_LIB_PATH)

# Source files.
AS_SRC  = $(wildcard $(PROJECT_PATH)/*.S)
ifeq ($(DEVICE_ID), PRVX3IMC48SH)
AS_SRC  += $(wildcard $(PRV_LIB_PATH)/asm/*.S)
AS_SRC  += $(PRV_LIB_PATH)/asm/interrupts/vectors.S
endif

C_SRC   = $(wildcard $(PROJECT_PATH)/*.c)
C_SRC  += $(wildcard $(PRV_LIB_PATH)/common/*.c)

ifndef PRV_LIB_FILES
C_SRC  += $(wildcard $(PRV_LIB_SRC)/*.c)
else
C_SRC  += $(foreach files, $(PRV_LIB_FILES), $(addprefix $(PRV_LIB_SRC)/,$(files)).c)
endif

C_SRC  += $(wildcard $(LIBRARY_PATH)/lcd1602/*.c)

# Header file directories.
INCLUDE += -I$(PRV_LIB_PATH)/include
INCLUDE += -I$(PRV_LIB_PATH)/common
INCLUDE += -I$(LIBRARY_PATH)/lcd1602
# INCLUDE += -I./

# Object files to build.
# OBJS  = $(addprefix $(OBJDIR)/,$(AS_SRC:.S=.o))
FILENAMES += $(foreach files, $(AS_SRC), $(shell basename $(files) .S))
FILENAMES += $(foreach files, $(C_SRC), $(shell basename $(files) .c))
OBJS += $(addprefix $(OBJDIR)/,$(addsuffix .o,$(FILENAMES)))

ifeq ($(DEVICE_ID), PRV32IMX1515)
COMMONOBJS += $(wildcard $(PRV_LIB_PATH)/asm/interrupts/objects/*.o)
COMMONOBJS += $(PRV_LIB_PATH)/asm/objects/start.o $(PRV_LIB_PATH)/asm/objects/end.o
endif

ALLOBJS = $(OBJS) $(COMMONOBJS)

# Rule to build project - compile and upload .PHONY: project
project: all program

program_and_debug: program_and_halt prv-debug

# Default rule to build the whole project.
.PHONY: all
all: create_build $(OBJDIR)/main.bin

create_build:
	mkdir -p $(OBJDIR)

# Rule to build assembly files.
# $(OBJDIR)/%.o: $(AS_SRC)
# 	@cd $(PROJECT_PATH)/$(OBJDIR)
# 	$(CC) -x assembler-with-cpp $(ASFLAGS) $(INCLUDE) $(AS_SRC)
# 	@cp *.o $(OBJDIR)
# 	@rm *.o

# Rule to compile C files in Project directory.
$(OBJDIR)/%.o: $(C_SRC)
	@cd $(PROJECT_PATH)/$(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(C_SRC)
	$(CC) -x assembler-with-cpp $(ASFLAGS) $(INCLUDE) $(AS_SRC)
	@cp *.o $(OBJDIR)
	@rm *.o

# Rule to create an ELF file from the compiled object files.
$(OBJDIR)/main.elf: $(ALLOBJS)
	$(CC) $^ $(LFLAGS) -o $@

# Rule to create a raw binary file from an ELF file.
$(OBJDIR)/main.bin: $(OBJDIR)/main.elf
	$(OC) -S -O binary $< $@
	$(OC) -S -O ihex $< $(OBJDIR)/main.hex
	$(OS) $<
	@$(OD) -D $< > $(OBJDIR)/main.lst
	@$(PY) $(UTILITY_PATH)/makehex.py $(OBJDIR)/main.hex 0x80000000 5000 0x10000000 200

# Rule to upload the program
.PHONY: program
program:
	$(PY) $(PROGRAM_CONFIGS) -a p

# Rule to program and halt 
.PHONY: program_and_halt
program_and_halt:
	$(PY) $(PROGRAM_CONFIGS) -a ph

# Rule to enter Pearl TUI based debug
.PHONY: prv-debug
prv-debug:
	$(PY) $(UTILITY_PATH)/debugger/debug_shell.py --device $(DEVICE_ID)

# Rule to launch server for gdb based debugging
.PHONY: prv-gdbserver
prv-gdbserver:
	$(PY) $(UTILITY_PATH)/debugger/server.py --device $(DEVICE_ID) --xml $(UTILITY_PATH)/debugger/prvx32_target.xml

# Rule to soft reset 
.PHONY: reset
reset:
	$(PY) $(PROGRAM_CONFIGS) -a r

# Rule to soft reset and halt
.PHONY: reset_halt
reset_halt:
	$(PY) $(PROGRAM_CONFIGS) -a rh

# Rule to view ports
.PHONY: ports
ports:
	$(PY) $(UTILITY_PATH)/ports.py

# Rule to launch sparrow terminal
.PHONY: terminal
terminal:
	$(PY) $(UTILITY_PATH)/sparrow_terminal.py $(PORT_NAME) $(PROGRAM_SPEED) $(TTYPE)

.PHONY: help
help:
	@echo "Options : [PORT_NAME=] [DEVICE_ID=] [PROGRAM_SPEED=] [TTYPE=]"
	@echo "Usage   : make [Rules] [Options]"
	@echo "Rules   : "
	@echo "          all                  Compile all source files"
	@echo "          clean                Delete all files in build folder"
	@echo "          help                 Shows this document"
	@echo "          ports                Shows all connected serial devices"
	@echo "          program              Upload the program"
	@echo "          program_and_halt     Upload the program and halt"
	@echo "          program_and_debug    Upload the program and enter debug mode"
	@echo "          reset                Execute a soft reset of the microcontroller"
	@echo "          reset_halt           Execute a soft reset of the microcontroller and halt execution"
	@echo "          prv-debug            Launch Pearl TUI based debugging"
	@echo "          prv-gdbserver        Launch Pearl gdbserver to debug using gdb"
	@echo "          project              Compile all sources and upload the program"
	@echo "          terminal             Launch sparrow terminal"

# Rule to clear out generated build files.
.PHONY: clean
clean:
	rm -f $(OBJS) $(OBJLIB)
	rm -f $(OBJDIR)/main.elf
	rm -f $(OBJDIR)/main.bin
	rm -f $(OBJDIR)/main.lst
	rm -f $(OBJDIR)/main.hex
	rm -f $(OBJDIR)/main_hex_dump.txt
	rm -f $(OBJDIR)/{ram.txt,rom.txt}
