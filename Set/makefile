CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror

all: set.o

set.o: set.c set.h Binary-Tree/binary_tree.h
	$(CC) -c $(CFLAGS) set.c

clean:
	rm -f set.o 2>&1 || :
