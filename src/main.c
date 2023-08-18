
#include <SDL_timer.h>
#include <stdint.h>

#include "cpu.h"
#include "display.h"
#include "input.h"
#include "memory_map.h"
#include "tty.h"

#define M68K_CLOCK_SPEED 100000

bool          isDisplayRunning = false;
unsigned char ram[MAX_RAM + 1];
bool          fetch_program(int argc, char **argv);
extern bool   isTtyBufferChanged;

void cap_fps(uint32_t startTime) {
    int frameRemaningTime = SDL_GetTicks() - startTime;
    if (frameRemaningTime > 0) {
        SDL_Delay(frameRemaningTime);
    }
}

void present_renderer_if_changed() {
    if (isTtyBufferChanged) {
        isTtyBufferChanged = false;
        present_renderer();
    }
}

void cleanup() {
    close_tty();
    close_display();
}

int main(int argc, char *argv[]) {
    bool fieldToInit = !initialize_display() || !initialize_input() || !initialize_cpu() || !initialize_tty() ||
                       !fetch_program(argc, argv);

    if (fieldToInit) return 1;

    while (isDisplayRunning) {
        uint32_t startTime = SDL_GetTicks();
        handel_keyboard_input();
        execute(M68K_CLOCK_SPEED);
        SDL_Log("time: %d", startTime);
        cap_fps(startTime);
        present_renderer_if_changed();
    }

    cleanup();

    return 0;
}

bool fetch_program(int argc, char **argv) {
    FILE *fhandle;

    if ((fhandle = fopen("basic.bin", "rb")) == NULL) {
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