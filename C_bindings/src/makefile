CC=gcc -std=c99 -Wall -Wextra -Wpedantic
CXX=g++ -std=c++20 -Wall -Wextra -Wpedantic

CDEBFLAGS=-g -O0
CFLAGS=-O3 -Wl,--strip-all,--build-id=none -fno-ident

DTARGET=debjsonlite
TARGET=jsonlite
default: release

debug: jsonlite.cpp
	$(CXX) -c $^ -o $(DTARGET).o $(CDEBFLAGS)
	ar rcs lib$(DTARGET).a $(DTARGET).o

release: jsonlite.cpp
	$(CXX) -c $^ -o $(TARGET).o $(CFLAGS)
	ar rcs lib$(TARGET).a $(TARGET).o
