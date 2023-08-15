#include "cpu.h"

#include <m68k.h>

bool initialize_cpu() {
    m68k_set_cpu_type(M68K_CPU_TYPE_68000);
    m68k_init();
    m68k_pulse_reset();
    return 1;
}