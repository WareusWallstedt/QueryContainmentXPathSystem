#ifndef XPATH_GET_FROM_SUPERSET_H
#define XPATH_GET_FROM_SUPERSET_H

#include "../Set/set.h"
#include "../XPath-Parser/xpath_tree.h"

void xpath_get_from_superset(struct set *dest,
                             struct set *src,
                             struct xpath_tree *query);

#endif
