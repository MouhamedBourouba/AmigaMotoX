#include "tty.h"

#include <SDL_events.h>
#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "display.h"

#define QUEUE_SIZE 100

struct termios oldtio, newtio;

bool tty_initialize() {
    tcgetattr(STDIN_FILENO, &oldtio);
    tcgetattr(STDIN_FILENO, &newtio);
    newtio.c_lflag &= ~(ECHO | ECHONL | ECHOCTL | ICANON);
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN]  = 1;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newtio) < 0) {
        printf("error setting terminal");
    }
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    signal(SIGINT, SIG_IGN);

    return 1;
}
void tty_update() {}
void tty_write(char ch) { printf("%c", ch); }
void tty_close() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtio);
    signal(SIGINT, SIG_DFL);
}
