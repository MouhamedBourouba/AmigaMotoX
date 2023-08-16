#include "memory_helper.h"

uint8_t get_serial_status(uint32_t address) {
    if (address >= SERIAL_INPUT_ADDRESS_LO && address <= SERIAL_INPUT_ADDRESS_HI) {
        return INPUT;
    } else if (address >= SERIAL_OUTPUT_ADDRESS_LO && address <= SERIAL_OUTPUT_ADDRESS_HI) {
        return OUTPUT;
    } else if (address >= SERIAL_STATUS_RDF_LO && address <= SERIAL_STATUS_RDF_HI) {
        return RDF;
    } else if (address >= SERIAL_STATUS_TXE_LO && address <= SERIAL_STATUS_TXE_HI) {
        return TXE;
    } else {
        return OUT_OF_RANGE;
    }
}