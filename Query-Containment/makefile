CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror

all: database_system.o query_containment.o xpath_get_from_superset.o

query_containment.o: query_containment.c \
                     ../Set/set.h \
                     ../XML-Parser/xml_tree.h \
                     ../XML-Parser/xml_parser.h \
                     ../XPath-Parser/xpath_tree.h \
                     ../XPath-Parser/xpath_parser.h \
                     database_system.h
	$(CC) -c $(CFLAGS) query_containment.c

database_system.o: database_system.c \
                   ../Set/set.h \
                   ../XML-Parser/xml_tree.h \
                   ../XML-Parser/xml_parser.h \
                   ../XPath-Parser/xpath_tree.h \
                   ../XPath-Parser/xpath_parser.h \
                   ../XPath-Evaluate/xpath_evaluate.h \
                   ../The-Canonical-Model/the_canonical_model.h \
                   ../The-Homomorphism-Technique/the_homomorphism_technique.h \
                   xpath_get_from_superset.h
	$(CC) -c $(CFLAGS) database_system.c

xpath_get_from_superset.o: xpath_get_from_superset.c \
                           ../Set/set.h \
                           ../XPath-Parser/xpath_tree.h \
                           ../XML-Parser/xml_tree.h
	$(CC) -c $(CFLAGS) xpath_get_from_superset.c

clean:
	rm -f query_containment.o 2>&1 || :
	rm -f database_system.o 2>&1 || :
	rm -f xpath_get_from_superset.o 2>&1 || :
