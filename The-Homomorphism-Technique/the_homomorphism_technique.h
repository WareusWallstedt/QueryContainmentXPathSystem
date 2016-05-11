#ifndef THE_HOMOMORPHISM_TECHNIQUE_H
#define THE_HOMOMORPHISM_TECHNIQUE_H

#include "../XPath-Parser/xpath_tree.h"

int the_homomorphism_technique(struct xpath_tree *xpath_expr1,
                               struct xpath_tree *xpath_expr2);

int the_homomorphism_technique_special(struct xpath_tree *xpath_expr1,
                                       struct xpath_tree *xpath_expr2);

int the_homomorphism_technique_str(const char *xpath_expr1,
                                   const char *xpath_expr2);

#endif
