CC = gcc
CFLAGS = -Wall -g
SRC = main.c
OUT = insomnia 
LIBS = -lglfw -lGLEW -lGL -lm

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)

