CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror

all: binary_tree.o

binary_tree.o: binary_tree.c binary_tree.h
	$(CC) -c $(CFLAGS) binary_tree.c

clean:
	rm -f binary_tree.o 2>&1 || :
