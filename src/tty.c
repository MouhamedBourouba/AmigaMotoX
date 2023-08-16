#include "tty.h"

#include <SDL2/SDL_ttf.h>
#include <SDL_log.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display.h"

static Color         textColor = {0x00, 0x00, 0x00, 0xFF};
static SDL_Texture  *text      = NULL;
static TTF_Font     *font;
extern SDL_Renderer *renderer;

int charWidth = 0, charHight = 0;

struct CharBuffer {
    char    *buff;
    uint32_t index;
} charBuffer;

bool initialize_tty() {
    bool failed_init = (TTF_Init() < 0);
    font             = TTF_OpenFont(FONT_PATH, 40);

    if (failed_init) SDL_LogError(0, "cant init ttf");
    if (font == NULL) SDL_LogError(0, "cant open font path: %s", FONT_PATH);

    charBuffer.buff  = malloc(CHAR_BUFFER);
    charBuffer.index = 0;

    return !failed_init && font != NULL;
}

static inline SDL_Color color_to_sdl_color(Color color) {
    SDL_Color c = {color.r, color.g, color.b, color.a};
    return c;
}

static inline char *char_to_sting(char c) {
    char *s;
    s[0] = c;
    s[1] = '\0';
    return s;
}

void calulate_char_position(int *offsetX, int *offsetY) {
    int   CHARS_PER_LINE        = WINDOW_WIDTH / charWidth;
    float current_line          = ((float)charBuffer.index / CHARS_PER_LINE);
    float charsInIncompleteLine = (current_line - (int)current_line) * CHARS_PER_LINE;
    *offsetX                    = charsInIncompleteLine * charWidth;
    *offsetY                    = ((charBuffer.index / CHARS_PER_LINE)) * charHight;
}

void write_char(char c) {
    if (c == '\n') {
        int   CHARS_PER_LINE        = WINDOW_WIDTH / charWidth;
        SDL_Log("chars per line: %d, char width: %d", CHARS_PER_LINE, charWidth);
        float current_line          = ((float)charBuffer.index / CHARS_PER_LINE) + 1;
        float charsInIncompleteLine = (current_line - (int)current_line) * CHARS_PER_LINE;
        for (int i = 0; i < (CHARS_PER_LINE - charsInIncompleteLine); ++i)
        {
            charBuffer.index++;
        }
        return;
    }
    charBuffer.buff[charBuffer.index++] = c;
    SDL_Surface *textSurface            = TTF_RenderText_Solid(font, char_to_sting(c), color_to_sdl_color(textColor));
    SDL_Texture *textTexture            = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (charHight == 0 || charWidth == 0) {
        charWidth = textSurface->w;
        charHight = textSurface->h;
    }

    SDL_Rect tr;
    tr.w = textSurface->w;
    tr.h = textSurface->h;
    calulate_char_position(&tr.x, &tr.y);
    SDL_RenderCopy(renderer, textTexture, NULL, &tr);
    return;
}

void set_text_color(Color c) { textColor = c; }

void close_tty() {
    free(charBuffer.buff);
    TTF_CloseFont(font);
    TTF_Quit();
}