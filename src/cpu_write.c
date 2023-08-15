#include <SDL_log.h>
#include <m68k.h>
#include <stdint.h>

#include "cpu.h"
#include "display.h"
#include "input.h"
#include "memory_helper.h"
#include "tty.h"

#define WRITE_BYTE(BASE, ADDR, VAL) (BASE)[ADDR] = (VAL)&0xff
#define WRITE_WORD(BASE, ADDR, VAL)           \
    (BASE)[ADDR]       = ((VAL) >> 8) & 0xff; \
    (BASE)[(ADDR) + 1] = (VAL)&0xff
#define WRITE_LONG(BASE, ADDR, VAL)            \
    (BASE)[ADDR]       = ((VAL) >> 24) & 0xff; \
    (BASE)[(ADDR) + 1] = ((VAL) >> 16) & 0xff; \
    (BASE)[(ADDR) + 2] = ((VAL) >> 8) & 0xff;  \
    (BASE)[(ADDR) + 3] = (VAL)&0xff

extern unsigned char ram[];



void write_ram(uint32_t address, uint32_t value, enum RamSize size) {
    if (address > MAX_RAM) {
        SDL_Log("Attempted to write to RAM address %08x", address);
        return;
    }
    switch (size) {
        case BYTE:
            WRITE_BYTE(ram, address, value);
        case WORD:
            WRITE_WORD(ram, address, value);
        case LONG:
            WRITE_LONG(ram, address, value);
    }
}

void m68k_write_memory_8(unsigned int address, unsigned int value) {}
void m68k_write_memory_16(unsigned int address, unsigned int value) {}
void m68k_write_memory_32(unsigned int address, unsigned int value) {}