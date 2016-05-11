CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror

all: the_homomorphism_technique.o

test: print_homomorphism

print_homomorphism: print_homomorphism.o the_homomorphism_technique.o ../XPath-Parser/xpath_parser.o ../XPath-Parser/xpath_tree.o
	$(CC) $(CFLAGS) -o print_homomorphism print_homomorphism.o the_homomorphism_technique.o ../XPath-Parser/xpath_parser.o ../XPath-Parser/xpath_tree.o

print_homomorphism.o: print_homomorphism.c the_homomorphism_technique.h
	$(CC) -c $(CFLAGS) print_homomorphism.c

the_homomorphism_technique.o: the_homomorphism_technique.c ../XPath-Parser/xpath_parser.h ../XPath-Parser/xpath_tree.h
	$(CC) -c $(CFLAGS) the_homomorphism_technique.c

../XPath-Parser/xpath_parser.o: force_look
	cd ../XPath-Parser; $(MAKE) $(MFLAGS)

../XPath-Parser/xpath_tree.o: force_look
	cd ../XPath-Parser; $(MAKE) $(MFLAGS)

clean:
	rm -f print_homomorphism 2>&1 || :
	rm -f *.o 2>&1 || :

force_look:
	true
