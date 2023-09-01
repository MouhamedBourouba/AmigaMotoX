#include "tty.h"

#include <SDL_events.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

#include "display.h"
#include "queue.h"

#define QUEUE_SIZE 100

struct Queue* inputQueue;

struct termios oldtio, newtio;

bool initialize_tty() {
    tcgetattr(STDIN_FILENO, &oldtio);
    tcgetattr(STDIN_FILENO, &newtio);
    newtio.c_lflag &= ~(ECHO | ECHONL | ECHOCTL | ICANON);
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN]  = 1;
    // cfmakeraw(&newtio); // use this instead of the three lines above if you want the VM to be able to output CR and
    // LF independently
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newtio) < 0) {
        printf("error setting terminal");
    }

    // remove buffers from stdin & stdout
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    // ignore SIGINT
    signal(SIGINT, SIG_IGN);
    inputQueue = newQueue(QUEUE_SIZE);

    return 1;
}

int kbhit(void) {
    struct timeval tv;
    fd_set         rdfs;

    tv.tv_sec  = 0;
    tv.tv_usec = 0;

    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);

    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}

void tty_input_write(char ch) {
    if (ch == 10) {
        return;
    }
    printf("%c", ch);
    fflush(stdout);
}

void tty_handle_input() {
    if (kbhit()) {
        char* ch = malloc(sizeof(char));
        *(ch)    = getchar();
        enqueue(inputQueue, ch);
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isDisplayRunning = false;
        }
    }
}

char tty_get_char() { return *((char*)dequeue(inputQueue)); }

bool tty_is_char_available() { return !isQueueEmpty(inputQueue); }

bool tty_is_input_device_ready() { return 1; }
