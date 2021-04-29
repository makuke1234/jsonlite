CC=gcc -std=c99 -Wall -Wextra -Wpedantic
CXX=g++ -std=c++11 -Wall -Wextra -Wpedantic

CFLAGS=-g
CFFLAGS=-O3 -Wl,--strip-all,--build-id=none -fno-ident

TARGET=jsonlite
default: release

release: jsonlite.cpp
	$(CXX) -c $^ -o $(TARGET).o $(CFLAGS)
	ar rcs lib$(TARGET).a $(TARGET).o
