#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../XPath-Parser/xpath_tree.h"
#include "../XPath-Parser/xpath_parser.h"

#include "../The-Canonical-Model/the_canonical_model.h"
#include "../The-Homomorphism-Technique/the_homomorphism_technique.h"

#define ITERATIONS 10000

int main(int argc, char *argv[])
{
	size_t i;
	int (*alg)(struct xpath_tree *, struct xpath_tree *);
	clock_t start, end, acc = 0;
	struct xpath_tree *q1, *q2;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s algorithm query1 query2\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "canonical") == 0) {
		alg = the_canonical_model;
	} else if (strcmp(argv[1], "homomorphism") == 0) {
		alg = the_homomorphism_technique;
	} else {
		fprintf(stderr, "Error: Invalid algorithm \"%s\".\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	q1 = xpath_parser(argv[2]);
	q2 = xpath_parser(argv[3]);

	for (i = 0; i < ITERATIONS; ++i) {
		start = clock();
		alg(q1, q2);
		end = clock();
		acc += end - start;
	}

	delete_xpath_tree(q1);
	delete_xpath_tree(q2);

	printf("%f\n", (double)acc / (double)ITERATIONS);

	return 0;
}
