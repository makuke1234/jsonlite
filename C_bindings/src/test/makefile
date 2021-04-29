CC=gcc -std=c99 -Wall -Wextra -Wpedantic
CXX=g++ -std=c++11 -Wall -Wextra -Wpedantic

CFLAGS=-g
CFFLAGS=-O3 -Wl,--strip-all,--build-id=none -fno-ident

TARGET=jsonlite
default: test

test: test.c ../lib$(TARGET).a
	$(CC) -c test.c -o test.o $(CFLAGS)
	$(CXX) test.o -o test.exe -l$(TARGET) -L".." $(CFLAGS)
