#include <m68k.h>
#include <stdio.h>

#include "display.h"
#include "input_linux.h"
#include "memory_map.h"
#include "tty.h"

#define READ_BYTE(BASE, ADDR) (BASE)[ADDR]
#define READ_WORD(BASE, ADDR) (((BASE)[ADDR] << 8) | (BASE)[(ADDR) + 1])
#define READ_LONG(BASE, ADDR) (((BASE)[ADDR] << 24) | ((BASE)[(ADDR) + 1] << 16) | ((BASE)[(ADDR) + 2] << 8) | (BASE)[(ADDR) + 3])
#define WRITE_BYTE(BASE, ADDR, VAL) (BASE)[ADDR] = (VAL)&0xff
#define WRITE_WORD(BASE, ADDR, VAL)           \
    (BASE)[ADDR]       = ((VAL) >> 8) & 0xff; \
    (BASE)[(ADDR) + 1] = (VAL)&0xff
#define WRITE_LONG(BASE, ADDR, VAL)            \
    (BASE)[ADDR]       = ((VAL) >> 24) & 0xff; \
    (BASE)[(ADDR) + 1] = ((VAL) >> 16) & 0xff; \
    (BASE)[(ADDR) + 2] = ((VAL) >> 8) & 0xff;  \
    (BASE)[(ADDR) + 3] = (VAL)&0xff

enum MemoryBlock {
    BYTE,
    WORD,
    LONG,
};

typedef enum {
    RAM,
    VRAM,
    SERIAL_RDF,
    SERIAL_TXE,
    SERIAL_IN,
    SERIAL_OUT,
} MemoryArea;

static inline MemoryArea get_memory_area(uint32_t address) {
    if (address >= SERIAL_INPUT_ADDRESS_LO && address <= SERIAL_INPUT_ADDRESS_HI) {
        return SERIAL_IN;
    } else if (address >= SERIAL_OUTPUT_ADDRESS_LO && address <= SERIAL_OUTPUT_ADDRESS_HI) {
        return SERIAL_OUT;
    } else if (address >= SERIAL_STATUS_RDF_LO && address <= SERIAL_STATUS_RDF_HI) {
        return SERIAL_RDF;
    } else if (address >= SERIAL_STATUS_TXE_LO && address <= SERIAL_STATUS_TXE_HI) {
        return SERIAL_TXE;
    } else if (address >= VRAM_LOW && address <= VRAM_HIGH) {
        return VRAM;
    } else {
        return RAM;
    }
}

extern uint8_t ram[];
extern uint8_t vram[];

bool initialize_cpu() {
    m68k_set_cpu_type(M68K_CPU_TYPE_68000);
    m68k_init();
    m68k_pulse_reset();
    return 1;
}
void                   execute(uint32_t cycels) { m68k_execute(cycels); }
static inline uint32_t read_memory(uint32_t address, enum MemoryBlock size) {
    MemoryArea memoryArea = get_memory_area(address);
    switch (memoryArea) {
        case RAM:
            switch (size) {
                case BYTE:
                    return READ_BYTE(ram, address);
                case WORD:
                    return READ_WORD(ram, address);
                case LONG:
                    return READ_LONG(ram, address);
            }
        case VRAM:
            switch (size) {
                case BYTE:
                    return READ_BYTE(vram, address);
                case WORD:
                    return READ_WORD(vram, address);
                case LONG:
                    return READ_LONG(vram, address);
            }
        case SERIAL_RDF:
            return !kbhit();
        case SERIAL_IN:
            return input_get_char();
        case SERIAL_TXE:
            return !running;
        case SERIAL_OUT:
            break;
    }
    return 0;
}

static inline void write_memory(uint32_t address, uint32_t value, enum MemoryBlock size) {
    MemoryArea memoryArea = get_memory_area(address);
    switch (memoryArea) {
        case RAM:
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
            break;
        case VRAM:
            switch (size) {
                case BYTE:
                    WRITE_BYTE(vram, address, value);
                    break;
                case WORD:
                    WRITE_WORD(vram, address, value);
                    break;
                case LONG:
                    WRITE_LONG(vram, address, value);
                    break;
            }
            break;
        case SERIAL_OUT:
            tty_write(value);
            break;
        case SERIAL_RDF:
        case SERIAL_TXE:
        case SERIAL_IN:
            break;
    }
}

unsigned int m68k_read_memory_8(unsigned int address) { return read_memory(address, BYTE); }
unsigned int m68k_read_memory_16(unsigned int address) { return read_memory(address, WORD); }
unsigned int m68k_read_memory_32(unsigned int address) { return read_memory(address, LONG); }
void         m68k_write_memory_8(unsigned int address, unsigned int value) { write_memory(address, value, BYTE); }
void         m68k_write_memory_16(unsigned int address, unsigned int value) { write_memory(address, value, WORD); }
void         m68k_write_memory_32(unsigned int address, unsigned int value) { write_memory(address, value, LONG); }