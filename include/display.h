#pragma once

#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <stdbool.h>
#include <stdint.h>

#include "constants.h"

extern bool running;

bool display_initialize();
bool display_create_window();
void display_update();
void display_close();
