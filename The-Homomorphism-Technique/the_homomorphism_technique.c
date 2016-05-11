#include <string.h>
#include "../XPath-Parser/xpath_parser.h"
#include "../XPath-Parser/xpath_tree.h"

static int _the_homomorphism_technique(struct xpath_tree *xpath_expr1,
                                       struct xpath_tree *xpath_expr2);

static int _descendant_homomorphism(struct xpath_tree *xpath_expr1, struct xpath_tree *xpath_expr2)
{
	size_t i;

	for (i = 0; i < xpath_expr1->preds_len; ++i) {
		if (_the_homomorphism_technique(xpath_expr1->preds[i], xpath_expr2)) {
			return 1;
		}

		if (_descendant_homomorphism(xpath_expr1->preds[i], xpath_expr2)) {
			return 1;
		}
	}

	if (xpath_expr1->next != NULL) {
		if (_the_homomorphism_technique(xpath_expr1->next, xpath_expr2)) {
			return 1;
		}

		if (_descendant_homomorphism(xpath_expr1->next, xpath_expr2)) {
			return 1;
		}
	}

	return 0;
}

static int _the_homomorphism_technique(struct xpath_tree *xpath_expr1,
                                       struct xpath_tree *xpath_expr2)
{
	size_t i, j;

	if (strcmp(xpath_expr2->label, "*") != 0 &&
	    strcmp(xpath_expr2->label, xpath_expr1->label) != 0) {
		return 0;
	}

	for (i = 0; i < xpath_expr2->preds_len; ++i) {
		if (xpath_expr2->preds[i]->type != CHILD) {
			continue;
		}

		for (j = 0; j < xpath_expr1->preds_len; ++j) {
			if (xpath_expr1->preds[j]->type != CHILD) {
				continue;
			}

			if (_the_homomorphism_technique(xpath_expr1->preds[j], xpath_expr2->preds[i])) {
				break;
			}
		}

		if (j < xpath_expr1->preds_len) {
			continue;
		}

		if (xpath_expr1->next != NULL &&
		    xpath_expr1->next->type == CHILD &&
		    _the_homomorphism_technique(xpath_expr1->next, xpath_expr2->preds[i])) {
			continue;
		}

		return 0;
	}

	if (xpath_expr2->next != NULL && xpath_expr2->next->type == CHILD) {
		for (j = 0; j < xpath_expr1->preds_len; ++j) {
			if (xpath_expr1->preds[j]->type != CHILD) {
				continue;
			}

			if (_the_homomorphism_technique(xpath_expr1->preds[j], xpath_expr2->next)) {
				break;
			}
		}

		if (j == xpath_expr1->preds_len) {
			if (xpath_expr1->next == NULL ||
			    xpath_expr1->next->type != CHILD ||
			    !_the_homomorphism_technique(xpath_expr1->next, xpath_expr2->next)) {
				return 0;
			}
		}
	}

	for (i = 0; i < xpath_expr2->preds_len; ++i) {
		if (xpath_expr2->preds[i]->type != DESCENDANT) {
			continue;
		}

		if (!_descendant_homomorphism(xpath_expr1, xpath_expr2->preds[i])) {
			return 0;
		}
	}

	if (xpath_expr2->next != NULL && xpath_expr2->next->type == DESCENDANT) {
		if (!_descendant_homomorphism(xpath_expr1, xpath_expr2->next)) {
			return 0;
		}
	}

	return 1;
}

int the_homomorphism_technique(struct xpath_tree *xpath_expr1,
                               struct xpath_tree *xpath_expr2)
{
	struct xpath_tree *p, *q;
	int ret;

	p = xpath_tree_copy(xpath_expr1);
	q = xpath_tree_copy(xpath_expr2);

	xpath_tree_add_x_to_selection_node(p);
	xpath_tree_add_x_to_selection_node(q);

	ret = _the_homomorphism_technique(p, q);

	delete_xpath_tree(p);
	delete_xpath_tree(q);

	return ret;
}

int the_homomorphism_technique_special(struct xpath_tree *xpath_expr1,
                                       struct xpath_tree *xpath_expr2)
{
	return _the_homomorphism_technique(xpath_expr1, xpath_expr2);
}

int the_homomorphism_technique_str(const char *xpath_expr1,
                                   const char *xpath_expr2)
{
	struct xpath_tree *t1, *t2;
	int ret;

	t1 = xpath_parser(xpath_expr1);
	t2 = xpath_parser(xpath_expr2);

	ret = the_homomorphism_technique(t1, t2);

	delete_xpath_tree(t1);
	delete_xpath_tree(t2);

	return ret;
}
