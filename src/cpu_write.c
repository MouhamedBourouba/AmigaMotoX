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

static inline void write_serial_memory(enum SerialStatus serialStatus, uint32_t value) {
    switch (serialStatus) {
        case OUTPUT:
            write_char(value);
            break;
        case INPUT:
            break;
        case RDF:
            SDL_Log("TRING TO WRITE SERIAL FLAGS");
            break;
        case TXE:
            SDL_Log("TRING TO WRITE SERIAL FLAGS");
            break;
        case OUT_OF_RANGE:
            break;
    }
}

static inline void write_ram(uint32_t address, uint32_t value, enum MemoryBlock size) {
    if (address > MAX_RAM) {
        SDL_Log("Attempted to write to RAM address %08x", address);
        return;
    }
    switch (size) {
        case BYTE:
            WRITE_BYTE(ram, address, value);
            break;
        case WORD:
            WRITE_WORD(ram, address, value);
            break;
        case LONG:
            WRITE_LONG(ram, address, value);
            break;
    }
}

static inline void write_memory(uint32_t address, uint32_t value, enum MemoryBlock size) {
    enum SerialStatus ss = get_serial_status(address);
    if (ss != OUT_OF_RANGE) {
        write_serial_memory(ss, value);
        return;
    }
    write_ram(address, value, size);
}

void m68k_write_memory_8(unsigned int address, unsigned int value) {
    write_memory(address, value, BYTE);
}
void m68k_write_memory_16(unsigned int address, unsigned int value) {
    write_memory(address, value, WORD);
}
void m68k_write_memory_32(unsigned int address, unsigned int value) {
    write_memory(address, value, LONG);
}