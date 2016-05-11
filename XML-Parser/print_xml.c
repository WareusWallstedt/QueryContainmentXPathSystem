#include <stdio.h>
#include <stdlib.h>

#include "xml_tree.h"
#include "xml_parser.h"

int main(int argc, char *argv[])
{
	struct xml_tree *t;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	t = xml_parser(argv[1]);
	xml_tree_print(t, stdout);
	fputc('\n', stdout);
	delete_xml_tree(t);

	return 0;
}
