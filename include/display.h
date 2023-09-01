#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <stdbool.h>
#include <stdint.h>

#define WINDOW_TITLE "m68k emu"
#define WINDOW_WIDTH 800
#define WINDOW_HIGHT 600
#define MAX_FPS 30

typedef struct {
    uint32_t x;
    uint32_t y;
} Position;

extern bool isDisplayRunning;

bool display_initialize();
void display_close();
void display_draw_pixel(Position pos, SDL_Color c);
void display_change_bc(SDL_Color bc);
void display_present_frame_buffer();

#endif
