
#include <SDL_timer.h>

#include "cpu.h"
#include "display.h"
#include "input.h"
#include "memory_map.h"
#include "tty.h"

bool          isDisplayRunning = false;
unsigned char ram[MAX_RAM + 1];
bool          fetch_program(int argc, char **argv);

int main(int argc, char *argv[]) {
    if (!initialize_display() || !initialize_input() || !initialize_cpu() || !initialize_tty() || !fetch_program(argc, argv)) return 1;

    write_char('g');
    write_char('g');
    write_char('g');
    write_char('\n');
    write_char('g');
    write_char('g');
    write_char('g');
    write_char('\n');
    write_char('g');
    write_char('g');
    write_char('g');
    write_char('\n');
    write_char('g');
    write_char('g');
    write_char('g');
    write_char('g');

    present_buffer();

    SDL_Delay(30 * 1000);
    return 0;
}

bool fetch_program(int argc, char **argv) {
    FILE *fhandle;

    if (argc != 2) {
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