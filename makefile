CC=gcc
CFLAGS=-g -pedantic -Wall -Wextra -Werror
DIRS=Query-Containment Set Set/Binary-Tree XML-Parser XPath-Parser The-Canonical-Model The-Homomorphism-Technique Benchmarks

all: query_containment

test: all containment_test database_containment_test generate_database benchmark_algorithm benchmark_database create_tree

create_tree: Benchmarks/create_tree.o
	$(CC) $(CFLAGS) -o create_tree Benchmarks/create_tree.o

Benchmarks/create_tree.o: Benchmarks

benchmark_algorithm: Benchmarks/benchmark_algorithm.o \
                     XPath-Parser/xpath_tree.o \
                     XPath-Parser/xpath_parser.o \
                     The-Canonical-Model/the_canonical_model.o \
                     The-Homomorphism-Technique/the_homomorphism_technique.o
	$(CC) $(CFLAGS) -o benchmark_algorithm Benchmarks/benchmark_algorithm.o XPath-Parser/xpath_tree.o XPath-Parser/xpath_parser.o The-Canonical-Model/the_canonical_model.o The-Homomorphism-Technique/the_homomorphism_technique.o

benchmark_database: Benchmarks/benchmark_database.o \
                    Set/set.o \
                    Set/Binary-Tree/binary_tree.o \
                    XML-Parser/xml_tree.o \
                    XML-Parser/xml_parser.o \
                    XPath-Parser/xpath_tree.o \
                    XPath-Parser/xpath_parser.o \
                    The-Canonical-Model/the_canonical_model.o \
                    The-Homomorphism-Technique/the_homomorphism_technique.o \
                    Query-Containment/database_system.o \
                    Query-Containment/xpath_get_from_superset.o \
                    XPath-Evaluate/xpath_evaluate.o
	$(CC) $(CFLAGS) -o benchmark_database \
                           Benchmarks/benchmark_database.o \
                           Set/set.o \
                           Set/Binary-Tree/binary_tree.o \
                           XML-Parser/xml_tree.o \
                           XML-Parser/xml_parser.o \
                           XPath-Parser/xpath_tree.o \
                           XPath-Parser/xpath_parser.o \
                           The-Canonical-Model/the_canonical_model.o \
                           The-Homomorphism-Technique/the_homomorphism_technique.o \
                           Query-Containment/database_system.o \
                           Query-Containment/xpath_get_from_superset.o \
                           XPath-Evaluate/xpath_evaluate.o

Benchmarks/benchmark_algorithm.o: Benchmarks
Benchmarks/benchmark_database.o: Benchmarks

generate_database: Benchmarks/generate_database.o
	$(CC) $(CFLAGS) -o generate_database Benchmarks/generate_database.o

containment_test: Benchmarks/containment_test.o \
                  XPath-Parser/xpath_tree.o \
                  XPath-Parser/xpath_parser.o \
                  The-Canonical-Model/the_canonical_model.o \
                  The-Homomorphism-Technique/the_homomorphism_technique.o
	$(CC) $(CFLAGS) -o containment_test Benchmarks/containment_test.o XPath-Parser/xpath_tree.o XPath-Parser/xpath_parser.o The-Canonical-Model/the_canonical_model.o The-Homomorphism-Technique/the_homomorphism_technique.o

database_containment_test: Benchmarks/database_containment_test.o \
                           Set/set.o \
                           Set/Binary-Tree/binary_tree.o \
                           XML-Parser/xml_tree.o \
                           XML-Parser/xml_parser.o \
                           XPath-Parser/xpath_tree.o \
                           XPath-Parser/xpath_parser.o \
                           Query-Containment/database_system.o \
                           Query-Containment/xpath_get_from_superset.o \
                           XPath-Evaluate/xpath_evaluate.o \
                           The-Canonical-Model/the_canonical_model.o \
                           The-Homomorphism-Technique/the_homomorphism_technique.o
	$(CC) $(CFLAGS) -o database_containment_test Benchmarks/database_containment_test.o Set/set.o Set/Binary-Tree/binary_tree.o XML-Parser/xml_tree.o XML-Parser/xml_parser.o XPath-Parser/xpath_tree.o XPath-Parser/xpath_parser.o Query-Containment/database_system.o Query-Containment/xpath_get_from_superset.o XPath-Evaluate/xpath_evaluate.o The-Canonical-Model/the_canonical_model.o The-Homomorphism-Technique/the_homomorphism_technique.o

Benchmarks/containment_test.o: Benchmarks
Benchmarks/generate_database.o: Benchmarks
Benchmarks: force_look
	cd Benchmarks; $(MAKE) $(MFLAGS)

query_containment: Query-Containment/query_containment.o \
                   Query-Containment/database_system.o \
                   Query-Containment/xpath_get_from_superset.o \
                   Set/set.o \
                   Set/Binary-Tree/binary_tree.o \
                   XML-Parser/xml_tree.o \
                   XML-Parser/xml_parser.o \
                   XPath-Parser/xpath_tree.o \
                   XPath-Parser/xpath_parser.o \
                   XPath-Evaluate/xpath_evaluate.o \
                   The-Canonical-Model/the_canonical_model.o \
                   The-Homomorphism-Technique/the_homomorphism_technique.o
	$(CC) $(CFLAGS) -o query_containment Query-Containment/query_containment.o Query-Containment/database_system.o Query-Containment/xpath_get_from_superset.o Set/set.o Set/Binary-Tree/binary_tree.o XML-Parser/xml_tree.o XML-Parser/xml_parser.o XPath-Parser/xpath_tree.o XPath-Parser/xpath_parser.o XPath-Evaluate/xpath_evaluate.o The-Canonical-Model/the_canonical_model.o The-Homomorphism-Technique/the_homomorphism_technique.o

Query-Containment/query_containment.o: Query-Containment
Query-Containment/database_system.o: Query-Containment
Query-Containment/xpath_get_from_superset.o: Query-Containment
Query-Containment: force_look
	cd Query-Containment; $(MAKE) $(MFLAGS)

Set/set.o: force_look
	cd Set; $(MAKE) $(MFLAGS)

Set/Binary-Tree/binary_tree.o: force_look
	cd Set/Binary-Tree; $(MAKE) $(MFLAGS)

XML-Parser/xml_tree.o: XML-Parser
XML-Parser/xml_parser.o: XML-Parser
XML-Parser: force_look
	cd XML-Parser; $(MAKE) $(MFLAGS)

XPath-Parser/xpath_tree.o: XPath-Parser
XPath-Parser/xpath_parser.o: XPath-Parser
XPath-Parser: force_look
	cd XPath-Parser; $(MAKE) $(MFLAGS)

The-Canonical-Model/the_canonical_model.o: force_look
	cd The-Canonical-Model; $(MAKE) $(MFLAGS)

The-Homomorphism-Technique/the_homomorphism_technique.o: force_look
	cd The-Homomorphism-Technique; $(MAKE) $(MFLAGS)

clean:
	rm -f create_tree 2>&1 || :
	rm -f benchmark_algorithm 2>&1 || :
	rm -f benchmark_database 2>&1 || :
	rm -f query_containment 2>&1 || :
	rm -f generate_database 2>&1 || :
	rm -f containment_test 2>&1 || :
	rm -f database_containment_test 2>&1 || :
	rm -f *.o 2>&1 || :
	for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

force_look:
	true
