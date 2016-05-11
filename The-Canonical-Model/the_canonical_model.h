#ifndef THE_CANONICAL_MODEL_H
#define THE_CANONICAL_MODEL_H

#include "../XPath-Parser/xpath_tree.h"

/**
 * The Canonical Model
 *
 * Input:
 *   XPath Expr q{1,2}
 *   - Expression in XPath(/, //, [ ], *)
 *   - May not contain label "z"
 *
 * Output:
 *   q1 ⊆ q2 ?
 */

int the_canonical_model(struct xpath_tree *q1, struct xpath_tree *q2);
int the_canonical_model_str(const char *q1, const char *q2);

#endif
