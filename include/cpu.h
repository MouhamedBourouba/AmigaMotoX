#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>

bool initialize_cpu();
void execute(uint32_t cycels);

#endif  // CPU_H
