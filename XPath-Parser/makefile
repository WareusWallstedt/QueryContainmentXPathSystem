CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror

all: xpath_tree.o xpath_parser.o

test: all print_xpath

print_xpath: print_xpath.o xpath_tree.o xpath_parser.o
	$(CC) $(CFLAGS) -o print_xpath print_xpath.o xpath_tree.o xpath_parser.o

print_xpath.o: print_xpath.c xpath_tree.h xpath_parser.h
	$(CC) -c $(CFLAGS) print_xpath.c

xpath_tree.o: xpath_tree.c xpath_tree.h
	$(CC) -c $(CFLAGS) xpath_tree.c

xpath_parser.o: xpath_parser.c xpath_tree.h
	$(CC) -c $(CFLAGS) xpath_parser.c

clean:
	rm -f print_xpath 2>&1 || :
	rm -f *.o 2>&1 || :
