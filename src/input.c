#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

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
int input_get_char() {
    int ch = -1;
    if (kbhit()) ch = getchar();
    return ch;
}
