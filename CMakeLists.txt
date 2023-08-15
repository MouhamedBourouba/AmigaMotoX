cmake_minimum_required(VERSION 3.25.1)
project(M68K_EMU)

find_package(SDL2 REQUIRED)
include_directories(include libmusashi/include)

set(SOURCES
   src/main.c
   src/sdl_display.c
   src/sdl_input.c
   src/cpu_read.c
   src/cpu_write.c
   src/cpu.c
   src/tty.c
   src/memory_helper.c
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libmusashi/libmusashi.a)
