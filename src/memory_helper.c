#include "memory_helper.h"

uint8_t get_serial_status(uint32_t address) {
    if (address <= SERIAL_INPUT_ADDRESS_HI && address >= SERIAL_INPUT_ADDRESS_LO) {
        return INPUT;
    }
    if (address <= SERIAL_OUTPUT_ADDRESS_HI && address >= SERIAL_OUTPUT_ADDRESS_LO) {
        return OUTPUT;
    }
    if (address <= SERIAL_STATUS_RDF_HI && address >= SERIAL_STATUS_RDF_LO) {
        return RDF;
    }
    if (address <= SERIAL_STATUS_TXE_HI && address >= SERIAL_STATUS_TXE_LO) {
        return TXE;
    }
    return OUT_OF_RANGE;
}