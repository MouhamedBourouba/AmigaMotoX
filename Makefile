CC = clang
OUTPUT = sim

SOURCES = $(wildcard src/*.c)
LIBS = $(shell pkg-config --libs sdl2) -lmusashi
CFLAGS = -g -Wall -L libmusashi/  -I include/ -I libmusashi/include  $(shell pkg-config --cflags sdl2)

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCES) $(LIBS)

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	clear
	./$(OUTPUT)
