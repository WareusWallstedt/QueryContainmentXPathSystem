#include <stdio.h>
#include <stdlib.h>

#include "xpath_tree.h"
#include "xpath_parser.h"

int main(int argc, char *argv[])
{
	struct xpath_tree *t;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s xpath_expr\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	t = xpath_parser(argv[1]);
	xpath_tree_fprint(t, stdout);
	fputc('\n', stdout);
	delete_xpath_tree(t);

	return 0;
}
