#ifndef MEMORY_HELPER_H
#define MEMORY_HELPER_H

#include "memory_map.h"

enum MemoryBlock {
    BYTE,
    WORD,
    LONG,
};

enum SerialStatus {
    RDF,
    TXE,
    INPUT,
    OUTPUT,
    OUT_OF_RANGE,
};

uint8_t get_serial_status(uint32_t address);

#endif
