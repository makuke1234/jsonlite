CC=gcc -std=c99 -Wall -Wextra -Wpedantic
CXX=g++ -std=c++20 -Wall -Wextra -Wpedantic

CDEBFLAGS=-g -O0
CFLAGS=-O3 -Wl,--strip-all,--build-id=none -fno-ident

BIN=bin
SRC=src
DTARGET=debjsonlite
TARGET=jsonlite
default: release

debug: $(SRC)/jsonlite.cpp
	$(CXX) -c $^ -o $(BIN)/$(DTARGET).o $(CDEBFLAGS)
	ar rcs $(BIN)/lib$(DTARGET).a $(BIN)/$(DTARGET).o

release: $(SRC)/jsonlite.cpp
	$(CXX) -c $^ -o $(BIN)/$(TARGET).o $(CFLAGS)
	ar rcs $(BIN)/lib$(TARGET).a $(BIN)/$(TARGET).o
