CC = gcc
CFLAGS = -Wall -g
SRC = src/*.c
OUT = insomnia 
LIBS = -lglfw -lGLEW -lGL -lm

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)

