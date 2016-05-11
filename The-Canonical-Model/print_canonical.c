#include <stdio.h>
#include <stdlib.h>

#include "the_canonical_model.h"

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s xpath_expr1 xpath_expr2\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (the_canonical_model_str(argv[1], argv[2])) {
		printf("Containment.\n");
	} else {
		printf("No containment.\n");
	}

	return 0;
}
