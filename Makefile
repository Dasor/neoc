CC=gcc
PREFIX ?= /usr

CFLAGS=-Wall -Wextra -Werror -pedantic -fstack-protector-all -pedantic -std=c99
SANITY_FLAGS=-Wfloat-equal -Wshadow -Wpointer-arith

neoc: Makefile main.c hardware.c hardware.h software.c software.h others.c others.h intelgpu.c intelgpu.h printer.c printer.h main.h logos.c logos.h
	 $(CC) main.c hardware.c software.c others.c intelgpu.c printer.c logos.c $(CFLAGS) $(SANITY_FLAGS) -g -lpci -lX11 -lm -o neoc

install: neoc
	install -Dm755 "neoc"       "$(DESTDIR)$(PREFIX)/bin/neoc"
	install -Dm644 "LICENSE"    "$(DESTDIR)$(PREFIX)/share/licenses/neoc/LICENSE"

uninstall:
	rm -f "$(DESTDIR)$(PREFIX)/bin/neoc"
	rm -f "$(DESTDIR)$(PREFIX)/share/licenses/neoc/LICENSE"
