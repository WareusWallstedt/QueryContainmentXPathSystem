CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror

all: xml_tree.o xml_parser.o

test: all print_xml

print_xml: print_xml.o xml_tree.o xml_parser.o
	$(CC) $(CFLAGS) -o print_xml print_xml.o xml_parser.o xml_tree.o

print_xml.o: print_xml.c xml_tree.h xml_parser.h
	$(CC) -c $(CFLAGS) print_xml.c

xml_tree.o: xml_tree.c xml_tree.h
	$(CC) -c $(CFLAGS) xml_tree.c

xml_parser.o: xml_parser.c xml_tree.h
	$(CC) -c $(CFLAGS) xml_parser.c

clean:
	rm -f print_xml 2>&1 || :
	rm -f *.o 2>&1 || :
