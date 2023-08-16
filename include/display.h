#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

typedef struct {
    uint32_t x;
    uint32_t y;
} Position;

// Constants for display
#define WINDOW_TITLE "m68k emu"
#define WINDOW_WIDTH 800
#define WINDOW_HIGHT 600

extern bool isDisplayRunning;

bool initialize_display();
void close_display();
void draw_pixel_to_buffer(Position pos, Color c);
void present_buffer();
void set_backgroud_color(Color bc);

#endif
