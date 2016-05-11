#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Set/set.h"
#include "../XML-Parser/xml_tree.h"
#include "../XML-Parser/xml_parser.h"
#include "../XPath-Parser/xpath_tree.h"
#include "../XPath-Parser/xpath_parser.h"
#include "../XPath-Evaluate/xpath_evaluate.h"
#include "../The-Canonical-Model/the_canonical_model.h"
#include "../The-Homomorphism-Technique/the_homomorphism_technique.h"
#include "xpath_get_from_superset.h"

int database_system(struct xml_tree *t,
                    struct xpath_tree *q1,
                    struct xpath_tree *q2,
                    struct set *res1,
                    struct set *res2,
                    const char *algorithm)
{
	int containment;
	int containment_rev;
	int ret = 0;

	/* TODO: Hash table */

	if (strcmp(algorithm, "none") == 0) {
		containment = 0;
		containment_rev = 0;
	} else if (strcmp(algorithm, "canonical") == 0) {
		containment = the_canonical_model(q1, q2);
		containment_rev = the_canonical_model(q2, q1);
	} else if (strcmp(algorithm, "homomorphism") == 0) {
		containment = the_homomorphism_technique(q1, q2);
		containment_rev = the_homomorphism_technique(q2, q1);
	} else {
		fprintf(stderr,
		        "Error: The \"%s\" algorithm is not yet available.\n",
		        algorithm);
		exit(EXIT_FAILURE);
	}

	if (containment) {
		ret = 1;
		xpath_evaluate(res2, q2, t);
		xpath_get_from_superset(res1, res2, q1);
	} else if (containment_rev) {
		ret = 1;
		xpath_evaluate(res1, q1, t);
		xpath_get_from_superset(res2, res1, q2);
	} else {
		xpath_evaluate(res1, q1, t);
		xpath_evaluate(res2, q2, t);
	}

	return ret;
}
