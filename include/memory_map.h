#pragma once

#include <stdint.h>

#define SERIAL_INPUT_ADDRESS_LO 0x78000
#define SERIAL_INPUT_ADDRESS_HI 0x79fff

#define SERIAL_OUTPUT_ADDRESS_LO 0x7a000
#define SERIAL_OUTPUT_ADDRESS_HI 0x7bfff

#define SERIAL_STATUS_TXE_LO 0x7D000
#define SERIAL_STATUS_TXE_HI 0x7DFFF

#define SERIAL_STATUS_RDF_LO 0x7c000
#define SERIAL_STATUS_RDF_HI 0x7cfff

#define MAX_VRAM 1024 * 1
#define VRAM_LOW 0x0E00000
#define VRAM_HIGH 0x0F00000

#define MAX_RAM 0xffffff