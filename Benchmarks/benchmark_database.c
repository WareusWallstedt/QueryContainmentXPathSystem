#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include "../Set/set.h"
#include "../XML-Parser/xml_tree.h"
#include "../XML-Parser/xml_parser.h"
#include "../XPath-Parser/xpath_tree.h"
#include "../XPath-Parser/xpath_parser.h"
#include "../Query-Containment/database_system.h"

#define ITERATIONS 100

int main(int argc, char *argv[])
{
	size_t i;
	clock_t start, end, acc = 0;
	struct xml_tree *t;
	struct xpath_tree *q1;
	struct xpath_tree *q2;
	struct set *res1;
	struct set *res2;

	if (argc != 5) {
		fprintf(stderr,
		        "Usage: %s algorithm database query1 query2\n",
		        argv[0]);
		exit(EXIT_FAILURE);
	}

	t = xml_parser(argv[2]);
	q1 = xpath_parser(argv[3]);
	q2 = xpath_parser(argv[4]);
	res1 = new_set(NULL, NULL, NULL, NULL);
	res2 = new_set(NULL, NULL, NULL, NULL);

	for (i = 0; i < ITERATIONS; ++i) {
		start = clock();
		database_system(t, q1, q2, res1, res2, argv[1]);
		end = clock();
		acc += end - start;
	}

	delete_xml_tree(t);
	delete_xpath_tree(q1);
	delete_xpath_tree(q2);
	delete_set(res1);
	delete_set(res2);

	printf("%f\n", (double)acc / (double)ITERATIONS);

	return 0;
}
