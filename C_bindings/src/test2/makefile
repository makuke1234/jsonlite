CC=gcc
CDEFFLAGS=-std=c99 -Wall -Wextra -Wpedantic
CFLAGS=-O3 -Wl,--strip-all,--build-id=none,--gc-sections -fno-ident
CDEBFLAGS=-g -O0
LIB=-L.. -ljsonlite -static -lstdc++

default: debug

debug: test.c
	$(CC) $^ -o $@.exe $(CDEFFLAGS) $(CDEBFLAGS) $(LIB)

release: test.c
	$(CC) $^ -o $@.exe $(CDEFFLAGS) $(CFLAGS) $(LIB)
