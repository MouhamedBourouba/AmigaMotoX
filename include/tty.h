#pragma once
#include <stdbool.h>

bool tty_initialize();
void tty_update();
void tty_write(char ch);
void tty_close();
