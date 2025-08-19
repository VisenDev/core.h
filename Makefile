CFLAGS= -Wall -Wextra -Wpedantic -std=c99

example: example.c core.h
	cc $(CFLAGS) example.c -o example
