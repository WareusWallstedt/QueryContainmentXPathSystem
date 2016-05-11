#include <stdio.h>
#include <stdlib.h>

#include "the_homomorphism_technique.h"

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s xpath_expr1 xpath_expr2\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (the_homomorphism_technique_str(argv[1], argv[2])) {
		printf("Homomorphism exists.\n");
	} else {
		printf("No homomorphism exists.\n");
	}

	return 0;
}
