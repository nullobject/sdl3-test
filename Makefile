SDL_FLAGS = $(shell pkg-config --cflags --libs sdl3)

main: main.c
	cc -Wall -o main main.c $(SDL_FLAGS)

clean:
	rm main
.PHONY: clean
