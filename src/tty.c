#include "tty.h"

#include <SDL_log.h>
#include <stdio.h>

void write_char(char c) {
    printf("%c", c);
    fflush(stdout);
}