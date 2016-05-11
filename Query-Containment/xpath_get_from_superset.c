#include <stdlib.h>
#include <string.h>
#include "../Set/set.h"
#include "../XPath-Parser/xpath_tree.h"
#include "../XML-Parser/xml_tree.h"

static int _xpath_pred_true(struct xpath_tree *pred,
                            struct xml_tree *node)
{
	size_t i, j;

	if (pred->type == CHILD) {
		for (i = 0; i < node->children_len; ++i) {
			if (node->children[i]->type != TAG) {
				continue;
			}

			if (pred->label[0] != '*' &&
			    strcmp(node->children[i]->data, pred->label) != 0) {
				continue;
			}

			for (j = 0; j < pred->preds_len; ++j) {
				if (!_xpath_pred_true(pred->preds[j], node->children[i])) {
					break;
				}
			}

			if (j < pred->preds_len) {
				continue;
			}

			if (pred->next == NULL ||
			    _xpath_pred_true(pred->next, node->children[i])) {
				return 1;
			}
		}
	} else {
		for (i = 0; i < node->children_len; ++i) {
			if (node->children[i]->type != TAG) {
				continue;
			}

			if (pred->label[0] == '*' ||
			    strcmp(node->children[i]->data, pred->label) == 0) {
				for (j = 0; j < pred->preds_len; ++j) {
					if (!_xpath_pred_true(pred->preds[j], node->children[i])) {
						break;
					}
				}

				if (j == pred->preds_len) {
					if (pred->next == NULL ||
					    _xpath_pred_true(pred->next, node->children[i])) {
						return 1;
					}
				}
			}

			if (_xpath_pred_true(pred, node->children[i])) {
				return 1;
			}
		}
	}

	return 0;
}

static int _node_valid_for_query(struct xpath_tree *query,
                                 struct xml_tree *node)
{
	size_t i;
	struct xml_tree *it;

	if (query->label[0] != '*' &&
	    strcmp(query->label, node->data) != 0) {
		return 0;
	}

	for (i = 0; i < query->preds_len; ++i) {
		if (!_xpath_pred_true(query->preds[i], node)) {
			return 0;
		}
	}

	if (query->parent == NULL && node->parent == NULL) {
		return 1;
	}

	if (query->type == DESCENDANT && query->parent == NULL) {
		return 1;
	}

	if (query->parent == NULL || node->parent == NULL) {
		return 0;
	}

	if (query->type == CHILD) {
		return _node_valid_for_query(query->parent, node->parent);
	} else {
		for (it = node->parent; it != NULL; it = it->parent) {
			if (_node_valid_for_query(query->parent, it)) {
				return 1;
			}
		}

		return 0;
	}
}

static void _insert_contained_nodes(struct set *dest,
                                    struct xpath_tree *query_last,
                                    struct xml_tree *node)
{
	size_t i;

	if (_node_valid_for_query(query_last, node)) {
		set_insert(dest, node);
	}

	for (i = 0; i < node->children_len; ++i) {
		_insert_contained_nodes(dest,
		                        query_last,
		                        node->children[i]);
	}
}

static struct xpath_tree *_query_get_last(struct xpath_tree *query)
{
	if (query->next == NULL) {
		return query;
	}

	return _query_get_last(query->next);
}

void xpath_get_from_superset(struct set *dest,
                             struct set *src,
                             struct xpath_tree *query)
{
	struct xpath_tree *query_last;
	struct xml_tree **array;
	size_t len;
	size_t i;

	query_last = _query_get_last(query);
	array = malloc(sizeof(struct xml_tree *) * src->size * 2);
	set_to_array(src, (void **)array, &len);

	for (i = 0; i < len; ++i) {
		_insert_contained_nodes(dest, query_last, array[i]);
	}

	free(array);
}
