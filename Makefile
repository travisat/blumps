CC=gcc
CFLAGS = -c -Wall
LDFLAGS = -I/usr/include/SDL -lSDL_image -lGLU -lftgl -lconfig
SOURCES = src/blumps.c src/init.c src/draw.c src/collision.c src/keypress.c src/movement.c src/menu.c src/game.c src/pause.c src/load_level.c src/death.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = blumps

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
		rm -rf src/*.o $(EXECUTABLE)	
