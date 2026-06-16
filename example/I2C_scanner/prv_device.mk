### Device specific Makefile ###

PROJECT_ROOT = $(CURDIR)
REPO_ROOT = $(PROJECT_ROOT)/../..

# Library Paths
PRV_LIB_PATH = $(REPO_ROOT)/prv32Lib
PRV_LIB_SRC = $(PRV_LIB_PATH)/src

# UNCOMMENT THE FOLLOWING LINE AND ADD THE NAMES OF THE INDIVIDUAL FILES TAHT MUST BE INCLUDED FROM LIBRARY
PRV_LIB_FILES = prv_i2c prv_i2c_master prv_plic prv_gpio prv_ict prv_dct prv_plic prv_timer0 prv_serial prv_uart

LIBRARY_PATH = $(REPO_ROOT)/libraries

# Project Configs
PROJECT_PATH = $(PROJECT_ROOT)
LINKER = $(PRV_LIB_PATH)/prvx3.ld
UTILITY_PATH = $(REPO_ROOT)/Utility
LOADER_NAME = Loader.py
UPLOAD_FILE_PATH = $(PROJECT_PATH)/$(OBJDIR)/main.hex
DEVICE_ID ?= PRVX3IMC48SH
PORT_NAME ?= /dev/cu.usbserial-0078EE22
PROGRAM_SPEED ?= 115200
TTYPE ?= i