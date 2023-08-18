#ifndef TTY_H
#define TTY_H

#include "display.h"

#define FONT_PATH "../data/bit-font/bitOperatorPlus-Regular.ttf"
#define CHAR_BUFFER 1024 * 4 /* 4 MB */
#define CHAR_WIDTH 15
#define CHAR_HIGHT 30
#define CURSOR_BLINK_RATE 500

#include <stdbool.h>

bool initialize_tty();
void write_char(char c);
void close_tty();
void blinkCursor();

#endif