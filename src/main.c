#include <stdio.h>

#include "constants.h"
#include "display.h"
#include "m68k.h"
#include "memory_map.h"
#include "tty.h"

unsigned char ram[MAX_RAM];
unsigned char vram[WINDOW_HIGHT * WINDOW_WIDTH];

bool running = false;

bool fetch_program(int argc, char **argv);
void testFB();

extern void execute(uint32_t cycels);
extern bool initialize_cpu();

int main(int argc, char *argv[]) {
    if (!initialize_cpu() || !display_initialize() || !tty_initialize() || !fetch_program(argc, argv)) {
        fprintf(stderr, "ERROR: initializing\n");
        return 1;
    }

    display_create_window();

    while (running) {
        execute(M68K_CLOCK_SPEED);
        display_update();
    }

    display_close();
    tty_close();
    return 0;
}

bool fetch_program(int argc, char **argv) {
    FILE *fhandle;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return false;
    }

    if ((fhandle = fopen(argv[1], "rb")) == NULL) {
        printf("Unable to open %s\n", argv[1]);
        return false;
    }

    if (fread(ram, 1, MAX_RAM + 1, fhandle) <= 0) {
        printf("Error reading %s\n", argv[1]);
        fclose(fhandle);
        return false;
    }
    fclose(fhandle);
    return 1;
}