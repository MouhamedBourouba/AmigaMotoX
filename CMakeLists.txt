cmake_minimum_required(VERSION 3.25.1)
project(M68K_EMU)

add_compile_options(-Wall -Wextra -DDEBUG)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
    include
    libmusashi/include
)

set(SOURCES
    src/main.c
    src/sdl_display.c
    src/tty.c
    src/cpu_read.c
    src/cpu_write.c
    src/cpu.c
    src/memory_helper.c
    src/queue.c
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${SDL2_LIBRARIES}
    -lSDL2_ttf
    -lncurses
    ${CMAKE_SOURCE_DIR}/libmusashi/libmusashi.a
)

