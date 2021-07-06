CC=gcc

CFLAGS=-Wall -Wextra -Werror -pedantic -fstack-protector-all -pedantic -std=c99
SANITY_FLAGS=-Wfloat-equal -Wshadow -Wpointer-arith

neoc: Makefile main.c hardware.c hardware.h software.c software.h others.c others.h intelgpu.c intelgpu.h
	 $(CC) main.c hardware.c software.c others.c intelgpu.c -g -lpci -lX11 -lm -o neoc
