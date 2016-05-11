#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../XPath-Parser/xpath_tree.h"
#include "../The-Canonical-Model/the_canonical_model.h"
#include "../The-Homomorphism-Technique/the_homomorphism_technique.h"

void create_tree(char *dest, size_t *pos, size_t *num, size_t depth, size_t arity)
{
	size_t i;

	if (*num & 1) {
		*pos += sprintf(&dest[*pos], "//a%lu", *num);
		++*num;
	} else {
		*pos += sprintf(&dest[*pos], "/a%lu", *num);
		++*num;
	}

	if (depth == 1) {
		return;
	}

	for (i = 0; i < arity; ++i) {
		*pos += sprintf(&dest[*pos], "[");
		create_tree(dest, pos, num, depth - 1, arity);
		*pos += sprintf(&dest[*pos], "]");
	}
}

int main(int argc, char *argv[])
{
	int (*algorithm)(const char *, const char *);
	clock_t start, end;
	size_t i, j, k;
	unsigned long test_length;
	char query1[4096];
	size_t query1_i;
	char query2[4096];
	size_t query2_i;
	int containment;

	if (argc < 4) {
		fprintf(stderr,
		        "Usage: %s algorithm test (test_length | (depth arity))\n",
		        argv[0]);
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "canonical") == 0) {
		algorithm = the_canonical_model_str;
	} else if (strcmp(argv[1], "homomorphism") == 0) {
		algorithm = the_homomorphism_technique_str;
	} else {
		fprintf(stderr, "Error: Invalid algorithm \"%s\"\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[2], "child") == 0) {
		test_length = strtoul(argv[3], NULL, 0);

		for (i = 1; i <= test_length; ++i) {
			query1_i = 0;

			for (k = 0; k < i; ++k) {
				query1_i += sprintf(&query1[query1_i], "/a%lu", i);
			}
	
			for (j = 1; j <= test_length; ++j) {
				query2_i = 0;

				for (k = 0; k < j; ++k) {
					query2_i += sprintf(&query2[query2_i], "/a%lu", j);
				}

				start = clock();
				containment = algorithm(query1, query2);
				end = clock();

				printf("T(%lu, %lu) = {%lu, %s}\n",
				       i,
				       j,
				       end - start,
				       containment ? "'T'" : "'F'");
			}
		}
	} else if (strcmp(argv[2], "descendant") == 0) {
		test_length = strtoul(argv[3], NULL, 0);

		for (i = 1; i <= test_length; ++i) {
			query1_i = 0;

			for (k = 0; k < i; ++k) {
				query1_i += sprintf(&query1[query1_i], "//a%lu", i);
			}
	
			for (j = 1; j <= test_length; ++j) {
				query2_i = 0;

				for (k = 0; k < j; ++k) {
					query2_i += sprintf(&query2[query2_i], "//a%lu", j);
				}

				start = clock();
				containment = algorithm(query1, query2);
				end = clock();

				printf("T(%lu, %lu) = {%lu, %s}\n",
				       i,
				       j,
				       end - start,
				       containment ? "'T'" : "'F'");
			}
		}
	} else if (strcmp(argv[2], "predicate") == 0) {
		test_length = strtoul(argv[3], NULL, 0);

		for (i = 1; i <= test_length; ++i) {
			query1_i = 0;
			query1_i += sprintf(&query1[query1_i], "//a");

			for (k = 0; k < i; ++k) {
				query1_i += sprintf(&query1[query1_i], "[//a%lu]", i);
			}
	
			for (j = 1; j <= test_length; ++j) {
				query2_i = 0;
				query2_i += sprintf(&query2[query2_i], "//a");

				for (k = 0; k < j; ++k) {
					query2_i += sprintf(&query2[query2_i], "[//a%lu]", j);
				}

				start = clock();
				containment = algorithm(query1, query2);
				end = clock();

				printf("T(%lu, %lu) = {%lu, %s}\n",
				       i,
				       j,
				       end - start,
				       containment ? "'T'" : "'F'");
			}
		}
	} else if (strcmp(argv[2], "child-wildcard") == 0) {
		test_length = strtoul(argv[3], NULL, 0);

		for (i = 1; i <= test_length; ++i) {
			query1_i = 0;

			for (k = 0; k < i; ++k) {
				query1_i += sprintf(&query1[query1_i], "/*");
			}
	
			for (j = 1; j <= test_length; ++j) {
				query2_i = 0;

				for (k = 0; k < j; ++k) {
					query2_i += sprintf(&query2[query2_i], "/*");
				}

				start = clock();
				containment = algorithm(query1, query2);
				end = clock();

				printf("T(%lu, %lu) = {%lu, %s}\n",
				       i,
				       j,
				       end - start,
				       containment ? "'T'" : "'F'");
			}
		}
	} else if (strcmp(argv[2], "descendant-wildcard") == 0) {
		test_length = strtoul(argv[3], NULL, 0);

		for (i = 1; i <= test_length; ++i) {
			query1_i = 0;

			for (k = 0; k < i; ++k) {
				query1_i += sprintf(&query1[query1_i], "//*");
			}
	
			for (j = 1; j <= test_length; ++j) {
				query2_i = 0;

				for (k = 0; k < j; ++k) {
					query2_i += sprintf(&query2[query2_i], "//*");
				}

				start = clock();
				containment = algorithm(query1, query2);
				end = clock();

				printf("T(%lu, %lu) = {%lu, %s}\n",
				       i,
				       j,
				       end - start,
				       containment ? "'T'" : "'F'");
			}
		}
	} else if (strcmp(argv[2], "predicate-wildcard") == 0) {
		test_length = strtoul(argv[3], NULL, 0);

		for (i = 1; i <= test_length; ++i) {
			query1_i = 0;
			query1_i += sprintf(&query1[query1_i], "//a");

			for (k = 0; k < i; ++k) {
				query1_i += sprintf(&query1[query1_i], "[//*]");
			}
	
			for (j = 1; j <= test_length; ++j) {
				query2_i = 0;
				query2_i += sprintf(&query2[query2_i], "//a");

				for (k = 0; k < j; ++k) {
					query2_i += sprintf(&query2[query2_i], "[//*]");
				}

				start = clock();
				containment = algorithm(query1, query2);
				end = clock();

				printf("T(%lu, %lu) = {%lu, %s}\n",
				       i,
				       j,
				       end - start,
				       containment ? "'T'" : "'F'");
			}
		}
	} else if (strcmp(argv[2], "tree") == 0) {
		size_t depth, arity;
		size_t num = 0;

		depth = strtoul(argv[3], NULL, 0);
		arity = strtoul(argv[4], NULL, 0);

		query1_i = 0;

		create_tree(query1, &query1_i, &num, depth, arity);

		start = clock();
		containment = algorithm(query1, query1);
		end = clock();

		printf("T(%lu, %lu) = {%lu, %s}\n",
		       depth,
		       arity,
		       end - start,
		       containment ? "'T'" : "'F'");
	}

	return 0;
}
