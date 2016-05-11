#ifndef XPATH_EVALUATE_H
#define XPATH_EVALUATE_H

#include <stddef.h>

#include "../Set/set.h"
#include "../XML-Parser/xml_tree.h"
#include "../XPath-Parser/xpath_tree.h"

void xpath_evaluate(struct set *dest,
                    struct xpath_tree *expr,
                    struct xml_tree *database);

#endif
