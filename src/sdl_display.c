#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include "display.h"

SDL_Window   *window;
SDL_Renderer *renderer;
static Color  backgroundColor = {10, 50, 0, 255};

bool initialize_display() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    window           = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HIGHT, SDL_WINDOW_OPENGL);
    renderer         = SDL_CreateRenderer(window, -1, 0);
    bool success     = window != NULL && renderer != NULL;
    isDisplayRunning = success;

    set_backgroud_color(backgroundColor);

    return success;
}

void draw_pixel_to_buffer(Position pos, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

void set_backgroud_color(Color bc) {
    SDL_SetRenderDrawColor(renderer, bc.r, bc.g, bc.b, bc.a);
    SDL_RenderClear(renderer);
    present_buffer();
}

void clear_display() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void present_buffer() { SDL_RenderPresent(renderer); }

void close_display() {
    isDisplayRunning = false;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
