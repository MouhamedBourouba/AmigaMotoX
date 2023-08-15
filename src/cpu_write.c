#include <SDL_log.h>
#include <m68k.h>

#include "memory_map.h"

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

void m68k_write_memory_8(unsigned int address, unsigned int value) {
    if (address > MAX_RAM) {
        SDL_Log("invalid memory address: %d", address);
    } else {
        WRITE_BYTE(ram, address, value);
    }
}
void m68k_write_memory_16(unsigned int address, unsigned int value) {
     if (address > MAX_RAM) {
        SDL_Log("invalid memory address: %d", address);
    } else {
        WRITE_WORD(ram, address, value);
    }
}
void m68k_write_memory_32(unsigned int address, unsigned int value) {
     if (address > MAX_RAM) {
        SDL_Log("invalid memory address: %d", address);
    } else {
        WRITE_LONG(ram, address, value);
    }
}
