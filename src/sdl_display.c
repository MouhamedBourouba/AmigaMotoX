#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include "display.h"

SDL_Window   *window;
SDL_Renderer *renderer;

bool initialize_display() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    window       = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HIGHT, SDL_WINDOW_OPENGL);
    renderer     = SDL_CreateRenderer(window, -1, 0);
    bool success = window != NULL && renderer != NULL;
    isDisplayRunning    = success;

    return success;
}

void draw_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void clear_display() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void present_display() {
    SDL_RenderPresent(renderer);
}

void close_display() {
    isDisplayRunning = false;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
