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

bool initialize_display();
void close_display();
void draw_pixel_to_buffer(Position pos, SDL_Color c);
void set_backgroud_color(SDL_Color bc);
void present_renderer();

#endif
