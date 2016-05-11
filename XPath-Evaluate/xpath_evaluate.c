#include <stddef.h>
#include <string.h>

#include "../Set/set.h"
#include "../XML-Parser/xml_tree.h"
#include "../XPath-Parser/xpath_tree.h"

static struct set *_dest;

static int _xpath_pred_satisfied(struct xpath_tree *pred,
                                 struct xml_tree *database)
{
	size_t i, j;

	if (pred->type == CHILD) {
		for (i = 0; i < database->children_len; ++i) {
			if (database->children[i]->type != TAG) {
				continue;
			}

			if (pred->label[0] != '*' &&
			    strcmp(pred->label, database->children[i]->data) != 0) {
				continue;
			}

			for (j = 0; j < pred->preds_len; ++j) {
				if (!_xpath_pred_satisfied(pred->preds[j], database->children[i])) {
					break;
				}
			}

			if (i < pred->preds_len) {
				continue;
			}

			if (pred->next == NULL) {
				return 1;
			} else {
				_xpath_pred_satisfied(pred->next, database->children[i]);
			}
		}

		return 0;
	} else {
		for (i = 0; i < database->children_len; ++i) {
			if (database->children[i]->type != TAG) {
				continue;
			}

			if (pred->label[0] != '*' &&
			    strcmp(pred->label, database->children[i]->data) != 0) {
				if (_xpath_pred_satisfied(pred, database->children[i])) {
					return 1;
				} else {
					continue;
				}
			}

			for (j = 0; j < pred->preds_len; ++j) {
				if (!_xpath_pred_satisfied(pred->preds[j], database->children[i])) {
					break;
				}
			}

			if (i < pred->preds_len) {
				continue;
			}

			if (pred->next == NULL) {
				return 1;
			} else {
				_xpath_pred_satisfied(pred->next, database->children[i]);
			}
		}

		return 0;
	}
}

static void _xpath_evaluate_helper(struct xpath_tree *expr,
                                   struct xml_tree *database)
{
	size_t i;

	if (expr->type == CHILD) {
		if (expr->label[0] != '*' &&
		    strcmp(expr->label, database->data) != 0) {
			return;
		}

		for (i = 0; i < expr->preds_len; ++i) {
			if (!_xpath_pred_satisfied(expr->preds[i], database)) {
				return;
			}
		}

		if (expr->next == NULL) {
			set_insert(_dest, database);
		} else {
			for (i = 0; i < database->children_len; ++i) {
				if (database->children[i]->type != TAG) {
					continue;
				}

				_xpath_evaluate_helper(expr->next, database->children[i]);
			}
		}
	} else {
		if (expr->label[0] != '*' &&
		    strcmp(expr->label, database->data) != 0) {
			for (i = 0; i < database->children_len; ++i) {
				if (database->children[i]->type != TAG) {
					continue;
				}

				_xpath_evaluate_helper(expr, database->children[i]);
			}

			return;
		} else {
			for (i = 0; i < database->children_len; ++i) {
				if (database->children[i]->type != TAG) {
					continue;
				}

				_xpath_evaluate_helper(expr, database->children[i]);
			}
		}

		for (i = 0; i < expr->preds_len; ++i) {
			if (!_xpath_pred_satisfied(expr->preds[i], database)) {
				return;
			}
		}

		if (expr->next == NULL) {
			set_insert(_dest, database);
		} else {
			for (i = 0; i < database->children_len; ++i) {
				if (database->children[i]->type != TAG) {
					continue;
				}

				_xpath_evaluate_helper(expr->next, database->children[i]);
			}
		}
	}
}

void xpath_evaluate(struct set *dest,
                    struct xpath_tree *expr,
                    struct xml_tree *database)
{
	_dest = dest;
	_xpath_evaluate_helper(expr, database);
}
