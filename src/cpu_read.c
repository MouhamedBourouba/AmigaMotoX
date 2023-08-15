#include <SDL_log.h>

#include "display.h"
#include "input.h"
#include "memory_map.h"

#define READ_BYTE(BASE, ADDR) (BASE)[ADDR]
#define READ_WORD(BASE, ADDR) (((BASE)[ADDR] << 8) | (BASE)[(ADDR) + 1])
#define READ_LONG(BASE, ADDR) (((BASE)[ADDR] << 24) | ((BASE)[(ADDR) + 1] << 16) | ((BASE)[(ADDR) + 2] << 8) | (BASE)[(ADDR) + 3])

#include <m68k.h>

extern unsigned char ram[];

unsigned int m68k_read_memory_8(unsigned int address) {
    if (address > MAX_RAM) {
        SDL_Log("trying to read invalid memory address: %d", address);
        return 0;
    } else if (address <= SERIAL_INPUT_ADDRESS_HI && address >= SERIAL_INPUT_ADDRESS_LO) {
        return poll_keyboard_input();
    } else if (address <= SERIAL_STATUS_RDF_HI && address >= SERIAL_STATUS_RDF_HI) {
        return is_queue_keyboard_empty() ? 1 : 0;
    } else if (address <= SERIAL_STATUS_TXE_LO && address >= SERIAL_STATUS_TXE_HI) {
        return isDisplayRunning;
    } else {
        return READ_BYTE(ram, address);
    }
}
unsigned int m68k_read_memory_16(unsigned int address) {
    if (address > MAX_RAM) {
        SDL_Log("trying to read nvalid memory address: %d", address);
        return 0;
    } else {
        return READ_WORD(ram, address);
    }
}
unsigned int m68k_read_memory_32(unsigned int address) {
    if (address > MAX_RAM) {
        SDL_Log("trying to read nvalid memory address: %d", address);
        return 0;
    } else {
        return READ_LONG(ram, address);
    }
}