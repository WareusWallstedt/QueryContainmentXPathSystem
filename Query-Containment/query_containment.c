#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Set/set.h"
#include "../XML-Parser/xml_tree.h"
#include "../XML-Parser/xml_parser.h"
#include "../XPath-Parser/xpath_tree.h"
#include "../XPath-Parser/xpath_parser.h"
#include "database_system.h"

int main(int argc, char *argv[])
{
	struct xml_tree *t;
	struct xpath_tree *q1;
	struct set *res1;
	struct xpath_tree *q2;
	struct set *res2;
	struct xml_tree **array;
	size_t i, len;

	if (argc != 5) {
		fprintf(stderr,
		        "%s (none|canonical|homomorphism) "
		        "xmlfile query1 query2\n",
		        argv[0]);
		exit(EXIT_FAILURE);
	}

	t = xml_parser(argv[2]);
	q1 = xpath_parser(argv[3]);
	res1 = new_set(NULL, NULL, NULL, NULL);
	q2 = xpath_parser(argv[4]);
	res2 = new_set(NULL, NULL, NULL, NULL);

	if (database_system(t, q1, q2, res1, res2, argv[1])) {
		printf("CONTAINMENT!\n");
	} else {
		printf("NO CONTAINMENT!\n");
	}

	printf("\nquery1:\n");
	array = malloc(sizeof(struct xml_tree *) * res1->size * 2);
	set_to_array(res1, (void **)array, &len);

	for (i = 0; i < len; ++i) {
		xml_tree_print(array[i], stdout);
		fputc('\n', stdout);
	}

	free(array);
	printf("\nquery2:\n");
	array = malloc(sizeof(struct xml_tree *) * res2->size * 2);
	set_to_array(res2, (void **)array, &len);

	for (i = 0; i < len; ++i) {
		xml_tree_print(array[i], stdout);
		fputc('\n', stdout);
	}

	free(array);
	delete_xml_tree(t);
	delete_xpath_tree(q1);
	delete_set(res1);
	delete_xpath_tree(q2);
	delete_set(res2);

	return 0;
}
