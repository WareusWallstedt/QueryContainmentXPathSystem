#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void print_tree_child(size_t *num, size_t depth, size_t arity)
{
	size_t i;

	if (depth == 0) {
		return;
	}

	for (i = 0; i < arity; ++i) {
		printf("[/a%lu", *num);
		++*num;

		if (depth > 1) {
			print_tree_child(num, depth - 1, arity);
		}

		printf("]");
	}
}

void print_tree_descendant(size_t *num, size_t depth, size_t arity)
{
	size_t i;

	if (depth == 0) {
		return;
	}

	for (i = 0; i < arity; ++i) {
		printf("[//a%lu", *num);
		++*num;

		if (depth > 1) {
			print_tree_descendant(num, depth - 1, arity);
		}

		printf("]");
	}
}

void print_tree_child_descendant(size_t *num, size_t depth, size_t arity)
{
	size_t i;

	if (depth == 0) {
		return;
	}

	for (i = 0; i < arity; ++i) {
		if ((*num & 1) == 0) {
			printf("[/a%lu", *num);
		} else {
			printf("[//a%lu", *num);
		}
		++*num;

		if (depth > 1) {
			print_tree_child_descendant(num, depth - 1, arity);
		}

		printf("]");
	}
}

void print_tree_child_wildcard(size_t *num, size_t depth, size_t arity)
{
	size_t i;

	if (depth == 0) {
		return;
	}

	for (i = 0; i < arity; ++i) {
		printf("[/*");
		++*num;

		if (depth > 1) {
			print_tree_child_wildcard(num, depth - 1, arity);
		}

		printf("]");
	}
}

void print_tree_descendant_wildcard(size_t *num, size_t depth, size_t arity)
{
	size_t i;

	if (depth == 0) {
		return;
	}

	for (i = 0; i < arity; ++i) {
		printf("[//*");
		++*num;

		if (depth > 1) {
			print_tree_descendant_wildcard(num, depth - 1, arity);
		}

		printf("]");
	}
}

void print_tree_child_descendant_wildcard(size_t *num, size_t depth, size_t arity)
{
	size_t i;

	if (depth == 0) {
		return;
	}

	for (i = 0; i < arity; ++i) {
		if ((*num & 1) == 0) {
			printf("[/*");
		} else {
			printf("[//*");
		}
		++*num;

		if (depth > 1) {
			print_tree_child_descendant_wildcard(num, depth - 1, arity);
		}

		printf("]");
	}
}

int main(int argc, char *argv[])
{
	size_t depth, arity;
	size_t num = 1;

	if (argc != 4) {
		fprintf(stderr,
		        "Usage: %s (child|descendant|child-descendant|child-wildcard|descendant-wildcard|child-descendant-wildcard) depth arity\n",
		        argv[0]);
		exit(EXIT_FAILURE);
	}

	depth = strtoul(argv[2], NULL, 0);
	arity = strtoul(argv[3], NULL, 0);

	printf("/root");

	if (strcmp(argv[1], "child") == 0) {
		print_tree_child(&num, depth, arity);
	} else if (strcmp(argv[1], "descendant") == 0) {
		print_tree_descendant(&num, depth, arity);
	} else if (strcmp(argv[1], "child-descendant") == 0) {
		print_tree_child_descendant(&num, depth, arity);
	} else if (strcmp(argv[1], "child-wildcard") == 0) {
		print_tree_child_wildcard(&num, depth, arity);
	} else if (strcmp(argv[1], "descendant-wildcard") == 0) {
		print_tree_descendant_wildcard(&num, depth, arity);
	} else if (strcmp(argv[1], "child-descendant-wildcard") == 0) {
		print_tree_child_descendant_wildcard(&num, depth, arity);
	}

	putchar('\n');

	return 0;
}
