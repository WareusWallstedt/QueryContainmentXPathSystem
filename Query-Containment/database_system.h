#ifndef DATABASE_SYSTEM_H
#define DATABASE_SYSTEM_H

#include "../Set/set.h"
#include "../XML-Parser/xml_tree.h"
#include "../XML-Parser/xml_parser.h"
#include "../XPath-Parser/xpath_tree.h"
#include "../XPath-Parser/xpath_parser.h"

int database_system(struct xml_tree *t,
                    struct xpath_tree *q1,
                    struct xpath_tree *q2,
                    struct set *res1,
                    struct set *res2,
                    const char *algorithm);

#endif
