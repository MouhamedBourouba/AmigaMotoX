#include "tty.h"

#include <SDL2/SDL_ttf.h>
#include <SDL_log.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display.h"

SDL_Color            textColor        = {0xFF, 0xFF, 0xFF, 0xFF};
SDL_Rect             currentCursorPos = {0, 0, CHAR_WIDTH, CHAR_HIGHT};
int                  maxCharPerLine   = WINDOW_WIDTH / CHAR_WIDTH;
static TTF_Font     *font;
extern SDL_Renderer *renderer;
bool                 isTtyBufferChanged = false;

struct CharBuffer {
    char    *buff;
    uint32_t index;
} charBuffer;

Uint32 cursor_blink_callback(Uint32 interval, void *p) {
    blinkCursor();
    return interval;
}

SDL_TimerID cursorBlinkCallbackID;

bool initialize_tty() {
    bool failed_init = (TTF_Init() < 0);
    font             = TTF_OpenFont(FONT_PATH, 40);

    if (failed_init) SDL_LogError(0, "cant init ttf");
    if (font == NULL) SDL_LogError(0, "cant open font path: %s", FONT_PATH);

    charBuffer.buff  = malloc(CHAR_BUFFER);
    charBuffer.index = 0;

    cursorBlinkCallbackID = SDL_AddTimer(CURSOR_BLINK_RATE, cursor_blink_callback, NULL);

    return !failed_init && font != NULL;
}

void inline blinkCursor() {
    static bool blink = false;
    SDL_SetRenderDrawColor(renderer, blink ? 255 : 0, blink ? 255 : 0, blink ? 255 : 0, blink ? 255 : 0);
    SDL_RenderFillRect(renderer, &currentCursorPos);
    blink              = !blink;
    isTtyBufferChanged = true;
}

void write_char(char c) {
    isTtyBufferChanged              = true;
    uint16_t currentCharIndexInLine = (charBuffer.index % maxCharPerLine);

    if (c == '\n') {
        currentCursorPos.y = +currentCursorPos.y + CHAR_HIGHT;
        currentCursorPos.x = 0;
        charBuffer.index   = charBuffer.index + (maxCharPerLine - currentCharIndexInLine);
        return;
    }
    charBuffer.buff[charBuffer.index++] = c;
    char         str[2]                 = {c, '\0'};
    SDL_Surface *surface                = TTF_RenderText_Solid(font, str, textColor);
    SDL_Texture *texture                = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &currentCursorPos);

    currentCursorPos.x = currentCursorPos.x + CHAR_WIDTH;

    if (currentCharIndexInLine >= (maxCharPerLine - 1)) {
        currentCursorPos.y = currentCursorPos.y + CHAR_HIGHT;
        currentCursorPos.x = 0;
    }
}

void set_text_color(SDL_Color c) { textColor = c; }

void close_tty() {
    free(charBuffer.buff);
    TTF_CloseFont(font);
    TTF_Quit();
}