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
bool display_create_window();
void display_update();
void display_close();

#endif
