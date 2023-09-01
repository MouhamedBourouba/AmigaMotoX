#ifndef TTY_H
#define TTY_H

#include <stdbool.h>

bool initialize_tty();
void tty_handle_input();
char tty_get_char();
bool tty_is_char_available();
bool tty_is_input_device_ready();
void tty_input_write(char ch);

#endif
