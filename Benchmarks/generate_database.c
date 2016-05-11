#include <stdio.h>
#include <stdlib.h>

void recursive_print(size_t *num, size_t depth, size_t arity, size_t spaces)
{
	size_t i;
	size_t this_num = *num;

	++*num;

	for (i = 0; i < spaces; ++i) {
		fputc(' ', stdout);
	}

	printf("<a%lu>\n", this_num);

	if (depth > 1) {
		for (i = 0; i < arity; ++i) {
			recursive_print(num, depth - 1, arity, spaces + 1);
		}
	}

	for (i = 0; i < spaces; ++i) {
		fputc(' ', stdout);
	}

	printf("</a%lu>\n", this_num);
}

int main(int argc, char *argv[])
{
	size_t num = 0;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s depth arity\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	recursive_print(&num, strtoul(argv[1], NULL, 0), strtoul(argv[2], NULL, 0), 0);

	return 0;
}
