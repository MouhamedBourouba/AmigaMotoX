
#_________________________________________________________________________
# Configuration

BOARD = BOARD_KATY68k

#build for the 68010 microprocessor
#CFLAGS_ARCH  = -m68010
#ASFLAGS_ARCH = -m68010 --defsym __mc68010__=1

CFLAGS_ARCH  = -m68000
ASFLAGS_ARCH = -m68000 --defsym __mc68010__=0

BUILD = build

CROSS_BIN = /opt/m68k-elf/bin

AS      = $(CROSS_BIN)/m68k-elf-as
AR      = $(CROSS_BIN)/m68k-elf-ar
CC      = $(CROSS_BIN)/m68k-elf-gcc
OBJDUMP = $(CROSS_BIN)/m68k-elf-objdump
OBJCOPY = $(CROSS_BIN)/m68k-elf-objcopy
RANLIB  = $(CROSS_BIN)/m68k-elf-ranlib
INCLUDE = $(ROOT)/include
ASFLAGS = $(ASFLAGS_ARCH)
CFLAGS  = -I$(INCLUDE) $(CFLAGS_ARCH) -D$(BOARD) -nostartfiles -nostdlib -fno-zero-initialized-in-bss -g -Os
LDFLAGS = -Wl,--build-id=none

# reduce the elf output size by reducing the alignment
CFLAGS += -z max-page-size=0x10


#_________________________________________________________________________
# VBCC Configuration

VBCC_BIN = /opt/vbcc/bin

VASM68      = $(VBCC_BIN)/vasmm68k_mot
VLINK       = $(VBCC_BIN)/vlink
VBCC68      = $(VBCC_BIN)/vbccm68k
