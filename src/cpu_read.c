#include <SDL_log.h>
#include <m68k.h>
#include <stdint.h>
#include <stdio.h>

#include "display.h"
#include "memory_helper.h"
#include "memory_map.h"
#include "tty.h"

#define READ_BYTE(BASE, ADDR) (BASE)[ADDR]
#define READ_WORD(BASE, ADDR) (((BASE)[ADDR] << 8) | (BASE)[(ADDR) + 1])
#define READ_LONG(BASE, ADDR) \
    (((BASE)[ADDR] << 24) | ((BASE)[(ADDR) + 1] << 16) | ((BASE)[(ADDR) + 2] << 8) | (BASE)[(ADDR) + 3])

extern unsigned char ram[];

static inline uint32_t read_ram(uint32_t address, enum MemoryBlock size) {
    if (address > MAX_RAM) {
        SDL_Log("Attempted to read from RAM address %08x", address);
        return 0;
    }

    switch (size) {
        case BYTE:
            return READ_BYTE(ram, address);
        case WORD:
            return READ_WORD(ram, address);
        case LONG:
            return READ_LONG(ram, address);
    }

    return 0;
}

static inline uint32_t read_serial_memory(uint32_t address, enum SerialStatus status) {
    switch (status) {
        case RDF:
            return !tty_is_char_available();
        case TXE:
            return !isDisplayRunning;
        case INPUT:
            return tty_get_char();
        case OUTPUT:
            // who will read the output .... ;)
            return 0;
        case OUT_OF_RANGE:
            break;
    }
    return 0;
}

static inline uint32_t read_memory(uint32_t address, enum MemoryBlock size) {
    enum SerialStatus serialStatus = get_serial_status(address);
    if (serialStatus != OUT_OF_RANGE) {
        return read_serial_memory(address, serialStatus);
    }
    return read_ram(address, size);
}

unsigned int m68k_read_memory_8(unsigned int address) { return read_memory(address, BYTE); }

unsigned int m68k_read_memory_16(unsigned int address) { return read_memory(address, WORD); }

unsigned int m68k_read_memory_32(unsigned int address) { return read_memory(address, LONG); }
