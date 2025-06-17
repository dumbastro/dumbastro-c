CC=gcc
CFLAGS=-Wall -pedantic
INCLUDE=-Iinclude
DEBUG=-g
LIBS=-lm
SRC=${PWD}/src
TEST_DIR=${PWD}/tests
BIN_DIR = $(PWD)/bin
BINS = $(BIN_DIR)/testdumbastro $(BIN_DIR)/libdumbastro.so

SOURCES = $(wildcard ${SRC}/*.c)

all: $(BINS)

# -fPIC: Position-Independent Code
$(BIN_DIR)/libdumbastro.so: $(SOURCES) $(PWD)/include/dumbastro.h
	$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) -fPIC -shared -o $@ $(SOURCES) $(LIBS)

$(BIN_DIR)/testdumbastro: $(TEST_DIR)/testdumbastro.c
	$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) -o $(PWD)/bin/testdumbastro $(TEST_DIR)/testdumbastro.c $(LIBS) -L. -ldumbastro

.PHONY clean:
	rm $(BINS)

# vim:noexpandtab list
