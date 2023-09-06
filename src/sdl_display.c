#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include "SDL_events.h"
#include "display.h"

SDL_Window   *window;
SDL_Renderer *renderer;

extern void close_emu();

bool display_initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    return 1;
}
bool display_create_window() {
    window = SDL_CreateWindow(
        WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HIGHT, SDL_WINDOW_OPENGL);
    renderer         = SDL_CreateRenderer(window, -1, 0);
    bool success     = window != NULL && renderer != NULL;
    isDisplayRunning = success;
    return success;
}
void display_close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void display_update() {
    SDL_Event *event = NULL;
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                close_emu();
        }
    }
}
