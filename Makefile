CC=gcc

CFLAGS=-Wall -Wextra -Werror -pedantic -fstack-protector-all -pedantic -std=c99
SANITY_FLAGS=-Wfloat-equal -Wshadow -Wpointer-arith
#Im not using the falgs since they say some varaibles form unistd.h are no defined will fix it

neoc: Makefile main.c hardware.c hardware.h software.c software.h others.c others.h
	 $(CC) main.c hardware.c software.c others.c -g -o neoc
