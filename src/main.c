
#include <curses.h>
#include <stdint.h>
#include <stdio.h>

#include "cpu.h"
#include "display.h"
#include "memory_map.h"
#include "tty.h"

#define M68K_CLOCK_SPEED 100000

unsigned char ram[MAX_RAM];
unsigned char vram[MAX_VRAM];

bool isDisplayRunning = false;

bool fetch_program(int argc, char **argv);
void cap_fps(uint32_t startTime);
void cleanup() { display_close(); }

int main(int argc, char *argv[]) {
    bool fieldToInit = !display_initialize() || !tty_initialize() || !initialize_cpu() || !fetch_program(argc, argv);

    if (fieldToInit) return 1;

    while (1) {
        uint32_t startTime = SDL_GetTicks();
        tty_handle_input();
        execute(M68K_CLOCK_SPEED);
        cap_fps(startTime);
    }

    cleanup();
    return 0;
}

void cap_fps(uint32_t startTime) {
    int frameRemaningTime = SDL_GetTicks() - startTime;
    if (frameRemaningTime > 0) {
        SDL_Delay(frameRemaningTime);
    }
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