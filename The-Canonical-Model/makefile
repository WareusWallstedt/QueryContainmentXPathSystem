CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror

all: the_canonical_model.o

test: print_canonical

print_canonical: print_canonical.o the_canonical_model.o ../The-Homomorphism-Technique/the_homomorphism_technique.o ../XPath-Parser/xpath_parser.o ../XPath-Parser/xpath_tree.o
	 $(CC) $(CFLAGS) -o print_canonical print_canonical.o the_canonical_model.o ../The-Homomorphism-Technique/the_homomorphism_technique.o ../XPath-Parser/xpath_parser.o ../XPath-Parser/xpath_tree.o

the_canonical_model.o: the_canonical_model.c ../XPath-Parser/xpath_tree.h
	$(CC) -c $(CFLAGS) the_canonical_model.c

print_canonical.o: print_canonical.c the_canonical_model.h
	$(CC) -c $(CFLAGS) print_canonical.c

../XPath-Parser/xpath_parser.o: force_look
	cd ../XPath-Parser; $(MAKE) $(MFLAGS)

../XPath-Parser/xpath_tree.o: force_look
	cd ../XPath-Parser; $(MAKE) $(MFLAGS)

../The-Homomorphism-Technique/the_homomorphism_technique.o: force_look
	cd ../The-Homomorphism-Technique; $(MAKE) $(MFLAGS)

clean:
	rm -f *.o 2>&1 || :
	rm -f print_canonical 2>&1 || :

force_look:
	true
