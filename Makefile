CC = gcc
CFLAGS = -Wall -g
SRC = fps-engine.c
OUT = fps-engine
LIBS = -lglfw -lGLEW -lGL -lm

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)

