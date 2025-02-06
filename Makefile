CC=gcc
CFLAGS=-Wall -pedantic
DEBUG=-g
LIBS=-lm
SRC=${PWD}/src
TEST_DIR=${PWD}/tests
BINS = libdumbastro.so testdumbastro

SOURCES = $(wildcard ${SRC}/*.c)

all: $(BINS)

# -fPIC: Position-Independent Code
libdumbastro.so: src/*.c src/dumbastro.h
	$(CC) $(CFLAGS) $(DEBUG) -fPIC -shared -o $@ $(SOURCES) $(LIBS)

testdumbastro: testdumbastro.c
	$(CC) $(WARN) $(DEBUG) -o testdumbastro testdumbastro.c $(LIBS) -L. -ldumbastro

clean:
	rm $(BINS)

# vim:noexpandtab list
