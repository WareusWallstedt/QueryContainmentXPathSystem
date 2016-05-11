CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror

all: xpath_evaluate.o

test: all print_xpath_evaluate

print_xpath_evaluate: print_xpath_evaluate.o xpath_evaluate.o ../XML-Parser/xml_parser.o ../XML-Parser/xml_tree.o ../XPath-Parser/xpath_parser.o ../XPath-Parser/xpath_tree.o ../Set/set.o ../Set/Binary-Tree/binary_tree.o
	$(CC) $(CFLAGS) -o print_xpath_evaluate print_xpath_evaluate.o xpath_evaluate.o ../XML-Parser/xml_parser.o ../XML-Parser/xml_tree.o ../XPath-Parser/xpath_parser.o ../XPath-Parser/xpath_tree.o ../Set/set.o ../Set/Binary-Tree/binary_tree.o

print_xpath_evaluate.o: print_xpath_evaluate.c xpath_evaluate.h ../XML-Parser/xml_parser.h ../XML-Parser/xml_tree.h ../XPath-Parser/xpath_parser.h ../XPath-Parser/xpath_tree.h ../Set/set.h
	$(CC) -c $(CFLAGS) print_xpath_evaluate.c

xpath_evaluate.o: xpath_evaluate.c ../XML-Parser/xml_tree.h ../XPath-Parser/xpath_tree.h ../Set/set.h
	$(CC) -c $(CFLAGS) xpath_evaluate.c

../XML-Parser/xml_parser.o: force_look
	cd ../XML-Parser; $(MAKE) $(MFLAGS)

../XML-Parser/xml_tree.o: force_look
	cd ../XML-Parser; $(MAKE) $(MFLAGS)

../XPath-Parser/xpath_parser.o: force_look
	cd ../XPath-Parser; $(MAKE) $(MFLAGS)

../XPath-Parser/xpath_tree.o: force_look
	cd ../XPath-Parser; $(MAKE) $(MFLAGS)

../Set/set.o: force_look
	cd ../Set; $(MAKE) $(MFLAGS)

../Set/Binary-Tree/binary_tree.o: force_look
	cd ../Set/Binary-Tree; $(MAKE) $(MFLAGS)

clean:
	rm -f print_xpath_evaluate 2>&1 || :
	rm -f *.o 2>&1 || :

force_look:
	true
