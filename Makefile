CC = clang
OUTPUT = sim

SOURCES = $(wildcard src/*.c)
LIBS =  $(shell pkg-config --libs sdl2) -L libmusashi -lmusashi
CFLAGS = -g -Wall -I include/ -I libmusashi/include $(shell pkg-config --cflags sdl2)

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	clear
	./$(OUTPUT)
