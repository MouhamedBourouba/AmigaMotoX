#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

bool initialize_input();
void handel_keyboard_input();
char poll_keyboard_input();
bool is_input_queue_empty();
bool is_input_device_read();
void input_write(unsigned int);

#endif