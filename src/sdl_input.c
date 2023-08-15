#include <SDL.h>
#include <SDL_events.h>
#include <stdbool.h>

#include "display.h"
#include "input.h"

bool initialize_input() {
    return SDL_WasInit(SDL_INIT_EVENTS) ? true : SDL_Init(SDL_INIT_EVENTS);
}

void handel_keyboard_input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                close_display();
        }
    }
}

char poll_keyboard_input() {
    return false;
}

bool is_queue_keyboard_empty() {
    return true;
}