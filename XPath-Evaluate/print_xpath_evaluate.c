#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "xpath_evaluate.h"
#include "../Set/set.h"
#include "../XML-Parser/xml_parser.h"
#include "../XML-Parser/xml_tree.h"
#include "../XPath-Parser/xpath_parser.h"
#include "../XPath-Parser/xpath_tree.h"

int main(int argc, char *argv[])
{
	struct xml_tree *xml;
	struct xpath_tree *xpath;
	struct set res;
	struct xml_tree *array[100000];
	size_t array_len;
	size_t i;

	/* Error check. */
	if (argc != 3) {
		fprintf(stderr, "Usage: %s XML-file XPath-expression\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	set_constructor(&res, NULL, NULL, NULL, NULL);

	xml = xml_parser(argv[1]);
	xpath = xpath_parser(argv[2]);
	xpath_evaluate(&res, xpath, xml);

	set_to_array(&res, (void **)array, &array_len);

	for (i = 0; i < array_len; ++i) {
		xml_tree_print(array[i], stdout);
		fputc('\n', stdout);
	}

	delete_xml_tree(xml);
	delete_xpath_tree(xpath);
	set_destructor(&res);

	return 0;
}
