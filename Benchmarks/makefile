CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror

all: containment_test.o benchmark_algorithm.o benchmark_database.o create_tree.o

benchmark_algorithm.o: benchmark_algorithm.c \
                       ../XPath-Parser/xpath_tree.h \
                       ../XPath-Parser/xpath_parser.h \
                       ../The-Canonical-Model/the_canonical_model.h \
                       ../The-Homomorphism-Technique/the_homomorphism_technique.h
	$(CC) -c $(CFLAGS) benchmark_algorithm.c

benchmark_database.o: benchmark_database.c \
                      ../Set/set.h \
                      ../XML-Parser/xml_tree.h \
                      ../XML-Parser/xml_parser.h \
                      ../XPath-Parser/xpath_tree.h \
                      ../XPath-Parser/xpath_parser.h \
                      ../Query-Containment/database_system.h
	$(CC) -c $(CFLAGS) benchmark_database.c

generate_database.o: generate_database.c
	$(CC) -c $(CFLAGS) generate_database.c

create_tree.o: create_tree.c
	$(CC) -c $(CFLAGS) create_tree.c

containment_test.o: containment_test.c ../XPath-Parser/xpath_tree.h ../The-Canonical-Model/the_canonical_model.h ../The-Homomorphism-Technique/the_homomorphism_technique.h
	$(CC) -c $(CFLAGS) containment_test.c

database_containment_test.o: database_containment_test.c \
                             ../Set/set.h \
                             ../XML-Parser/xml_tree.h \
                             ../XML-Parser/xml_parser.h \
                             ../XPath-Parser/xpath_tree.h \
                             ../XPath-Parser/xpath_parser.h \
                             ../Query-Containment/database_system.h
	$(CC) -c $(CFLAGS) database_containment_test.c

clean:
	rm -f *.o 2>&1 || :
