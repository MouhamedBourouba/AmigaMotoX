#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <stdint.h>

// Constants for display dimensions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define WINDOW_TITLE "m68k emu"
#define WINDOW_WIDTH 640
#define WINDOW_HIGHT 260

extern bool isDisplayRunning;

bool initialize_display();
void close_display();
void draw_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void present_display();

#endif
