#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <m68k.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_TITLE "m68k emu"
#define WINDOW_WIDTH 640
#define WINDOW_HIGHT 260

#define MAX_ROM 0xfff
#define MAX_RAM 0xff

unsigned int  FUN_CODE; /* Current function code from CPU */
unsigned char rom[MAX_ROM];
unsigned char ram[MAX_RAM];

bool isRunning = true;

// Function prototypes
SDL_Window *initialize();
void        cleanup();

int main(int argc, char *argv[]) {
    FILE         *fhandle;
    unsigned char rom[MAX_ROM + 1];

    // Check command-line arguments
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open and read the ROM file
    if ((fhandle = fopen(argv[1], "rb")) == NULL) {
        printf("Unable to open %s\n", argv[1]);
        return 1;
    }

    if (fread(rom, 1, MAX_ROM + 1, fhandle) <= 0) {
        printf("Error reading %s\n", argv[1]);
        fclose(fhandle);
        return 1;
    }

    fclose(fhandle);

    // Initialize components
    initialize();

    // Main loop
    SDL_Event event;
    while (isRunning) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
            }
        }
        m68k_execute(100000);
    }

    // Clean up and exit
    cleanup();
    return 0;
}

// Initialize components
SDL_Window *initialize() {
    m68k_set_cpu_type(M68K_CPU_TYPE_68000);
    m68k_pulse_reset();
    m68k_init();

    SDL_Init(SDL_INIT_VIDEO);
    return SDL_CreateWindow(
        WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HIGHT, SDL_WINDOW_OPENGL);
}

// Clean up resources
void cleanup() {
    SDL_Quit();
}

void cpu_set_fc(unsigned int fc) {
    FUN_CODE = fc;
}

/* Read/write macros */
#define READ_BYTE(BASE, ADDR) (BASE)[ADDR]
#define READ_WORD(BASE, ADDR) (((BASE)[ADDR] << 8) | (BASE)[(ADDR) + 1])
#define READ_LONG(BASE, ADDR) \
    (((BASE)[ADDR] << 24) | ((BASE)[(ADDR) + 1] << 16) | ((BASE)[(ADDR) + 2] << 8) | (BASE)[(ADDR) + 3])

#define WRITE_BYTE(BASE, ADDR, VAL) (BASE)[ADDR] = (VAL)&0xff
#define WRITE_WORD(BASE, ADDR, VAL)           \
    (BASE)[ADDR]       = ((VAL) >> 8) & 0xff; \
    (BASE)[(ADDR) + 1] = (VAL)&0xff
#define WRITE_LONG(BASE, ADDR, VAL)            \
    (BASE)[ADDR]       = ((VAL) >> 24) & 0xff; \
    (BASE)[(ADDR) + 1] = ((VAL) >> 16) & 0xff; \
    (BASE)[(ADDR) + 2] = ((VAL) >> 8) & 0xff;  \
    (BASE)[(ADDR) + 3] = (VAL)&0xff

unsigned int m68k_read_memory_8(unsigned int address) {
    if (FUN_CODE & 2) {
        if (address > MAX_ROM) {
            SDL_Log("out of boundry ROM address %d", address);
            return 0;
        }
        return READ_BYTE(rom, address);
    }
    if (address > MAX_RAM) {
        SDL_Log("out of boundry RAM address %d", address);
        return 0;
    }
    return READ_BYTE(ram, address);
};
unsigned int m68k_read_memory_16(unsigned int address) {
    if (FUN_CODE & 2) {
        if (address > MAX_ROM) {
            SDL_Log("out of boundry ROM address %d", address);
            return 0;
        }
        return READ_WORD(rom, address);
    }
    if (address > MAX_RAM) {
        SDL_Log("out of boundry RAM address %d", address);
        return 0;
    }
    return READ_WORD(ram, address);
}
unsigned int m68k_read_memory_32(unsigned int address) {
    if (FUN_CODE & 2) {
        if (address > MAX_ROM) {
            SDL_Log("out of boundry ROM address %d", address);
            return 0;
        }
        return READ_LONG(rom, address);
    }
    if (address > MAX_RAM) {
        SDL_Log("out of boundry RAM address %d", address);
        return 0;
    }
    return READ_LONG(ram, address);
}
void m68k_write_memory_8(unsigned int address, unsigned int value) {
    if (FUN_CODE & 2) {
        if (address > MAX_ROM) {
            SDL_Log("out of boundry ROM address %d", address);
            return;
        }
        WRITE_BYTE(rom, address, value);
    }
    if (address > MAX_RAM) {
        SDL_Log("out of boundry RAM address %d", address);
        return;
    }
    WRITE_BYTE(ram, address, value);
}
void m68k_write_memory_16(unsigned int address, unsigned int value) {
    if (FUN_CODE & 2) {
        if (address > MAX_ROM) {
            SDL_Log("out of boundry ROM address %d", address);
            return;
        }
        WRITE_WORD(rom, address, value);
    }
    if (address > MAX_RAM) {
        SDL_Log("out of boundry RAM address %d", address);
        return;
    }
    WRITE_WORD(ram, address, value);
}
void m68k_write_memory_32(unsigned int address, unsigned int value) {
    if (FUN_CODE & 2) {
        if (address > MAX_ROM) {
            SDL_Log("out of boundry ROM address %d", address);
            return;
        }
        WRITE_LONG(rom, address, value);
    }
    if (address > MAX_RAM) {
        SDL_Log("out of boundry RAM address %d", address);
        return;
    }
    WRITE_LONG(ram, address, value);
}
