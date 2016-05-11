#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../XPath-Parser/xpath_tree.h"
#include "../XPath-Parser/xpath_parser.h"
#include "../The-Homomorphism-Technique/the_homomorphism_technique.h"

static size_t _longest_child_wildcard_chain_helper(struct xpath_tree *t, size_t cur_m_q)
{
	size_t i;
	size_t tmp_m_q;
	size_t ret;

	if (t->type == CHILD && t->label[0] == '*') {
		++cur_m_q;
	} else {
		cur_m_q = 0;
	}

	ret = cur_m_q;

	for (i = 0; i < t->preds_len; ++i) {
		tmp_m_q = _longest_child_wildcard_chain_helper(t->preds[i], cur_m_q);

		if (tmp_m_q > ret) {
			ret = tmp_m_q;
		}
	}

	if (t->next != NULL) {
		tmp_m_q = _longest_child_wildcard_chain_helper(t->next, cur_m_q);

		if (tmp_m_q > ret) {
			ret = tmp_m_q;
		}
	}

	return ret;
}

static size_t _longest_child_wildcard_chain(struct xpath_tree *t)
{
	return _longest_child_wildcard_chain_helper(t, 0);
}

static struct xpath_tree *_xpath_tree_copy_replace_wildcards(struct xpath_tree *t,
                                                             size_t label_len,
                                                             const char *label)
{
	struct xpath_tree *copy;
	size_t i;

	if (t->label[0] == '*') {
		copy = new_xpath_tree(t->type, label_len, label);
	} else {
		copy = new_xpath_tree(t->type, t->label_len, t->label);
	}

	for (i = 0; i < t->preds_len; ++i) {
		xpath_tree_add_pred(
			copy,
			_xpath_tree_copy_replace_wildcards(t->preds[i],
			                                   label_len,
			                                   label)
		);
	}

	if (t->next != NULL) {
		copy->next = _xpath_tree_copy_replace_wildcards(t->next,
		                                                label_len,
		                                                label);
	}

	return copy;
}

struct desc_edge_list {
	size_t len;
	size_t alloc_len;
	struct xpath_tree ***from;
	struct xpath_tree **to;
};

static void _xpath_tree_get_descendant_edges_helper(struct xpath_tree *t,
                                                    struct xpath_tree **parent_edge,
                                                    struct desc_edge_list *d)
{
	struct xpath_tree ***from_tmp;
	struct xpath_tree **to_tmp;
	size_t i;

	if (t->type == DESCENDANT) {
		t->type = CHILD;
		t->parent = NULL;
		d->from[d->len] = parent_edge;
		d->to[d->len] = t;
		++d->len;

		if (d->len == d->alloc_len) {
			d->alloc_len <<= 1;

			from_tmp = malloc(sizeof(struct desc_edge_list **) * d->alloc_len);
			to_tmp = malloc(sizeof(struct desc_edge_list *) * d->alloc_len);

			for (i = 0; i < d->len; ++i) {
				from_tmp[i] = d->from[i];
				to_tmp[i] = d->to[i];
			}

			free(d->from);
			free(d->to);

			d->from = from_tmp;
			d->to = to_tmp;
		}
	}

	for (i = 0; i < t->preds_len; ++i) {
		_xpath_tree_get_descendant_edges_helper(t->preds[i], &t->preds[i], d);
	}

	if (t->next != NULL) {
		_xpath_tree_get_descendant_edges_helper(t->next, &t->next, d);
	}
}

static struct desc_edge_list *_xpath_tree_get_descendant_edges(struct xpath_tree *t)
{
	struct desc_edge_list *d;

	d = malloc(sizeof(struct desc_edge_list));
	d->len = 0;
	d->alloc_len = 16;
	d->from = malloc(sizeof(struct desc_edge_list **) * 16);
	d->to = malloc(sizeof(struct desc_edge_list *) * 16);

	_xpath_tree_get_descendant_edges_helper(t, NULL, d);

	return d;
}

static struct xpath_tree *_new_xpath_tree_chain(const char *label,
                                                size_t len,
                                                struct xpath_tree **t_last)
{
	struct xpath_tree *t;

	t = new_xpath_tree(CHILD, strlen(label), label);

	if (len > 1) {
		t->next = _new_xpath_tree_chain(label, len - 1, t_last);
	} else {
		*t_last = t;
	}

	return t;
}


/**
 * xpath_alg1 returns 1 if p ⊆ q, otherwise 0.
 * p and q are XPath(/, //, [ ], *).
 * The algorithm belongs to coNP.
 */

static int _trees_match(struct xpath_tree *t1, struct xpath_tree *t2)
{
	return the_homomorphism_technique_special(t1, t2);
}

int _the_canonical_model(struct xpath_tree *q1, struct xpath_tree *q2)
{
	size_t i, j;
	size_t m_q;
	size_t *it;
	struct xpath_tree *q1_renamed;
	struct xpath_tree *t_first, *t_last;
	struct desc_edge_list *d;

	/* Calculate m(q), time complexity:
	 * Ο(n_q) */
	m_q = _longest_child_wildcard_chain(q2);

	/* Rename all * in p to new_label, time complexity:
	 * Ο(n_p) */
	q1_renamed = _xpath_tree_copy_replace_wildcards(q1, 1, "z");

	/* Get pointers to descendant edges in p, time complexity:
	 * O(n_p) */
	d = _xpath_tree_get_descendant_edges(q1_renamed);

	/* Construct array of length counters for descendant edges. */
	it = malloc(sizeof(size_t) * d->len);

	for (i = 0; i < d->len; ++i) {
		it[i] = 0;
	}

	/* Test all combinations of lengths for the descendant edges. */
	for (i = 0; ; ++i) {
		for (j = 0; j < d->len; ++j) {
			if (it[j] > 0) {
				if (d->from[j] != NULL) {
					t_first = _new_xpath_tree_chain("z", it[j], &t_last);
					*d->from[j] = t_first;
					t_last->next = d->to[j];
					d->to[j]->parent = t_last;
				}
			}
		}

		if (!_trees_match(q1_renamed, q2)) {
			delete_xpath_tree(q1_renamed);
			free(it);
			free(d->from);
			free(d->to);
			free(d);
			return 0;
		}

		for (j = 0; j < d->len; ++j) {
			if (d->to[j]->parent != NULL) {
				d->to[j]->parent->next = NULL;
				delete_xpath_tree(*d->from[j]);
				*d->from[j] = d->to[j];
				d->to[j]->parent = NULL;
			}
		}

		for (j = 0; j < d->len; ++j) {
			++it[j];

			if (it[j] < m_q + 2) {
				break;
			} else {
				it[j] = 0;
			}
		}

		if (j == d->len) {
			break;
		}
	}

	delete_xpath_tree(q1_renamed);
	free(it);
	free(d->from);
	free(d->to);
	free(d);

	return 1;
}

int the_canonical_model(struct xpath_tree *q1, struct xpath_tree *q2)
{
	struct xpath_tree *p, *q;
	int ret;

	p = xpath_tree_copy(q1);
	q = xpath_tree_copy(q2);

	xpath_tree_add_x_to_selection_node(p);
	xpath_tree_add_x_to_selection_node(q);

	ret = _the_canonical_model(p, q);

	delete_xpath_tree(p);
	delete_xpath_tree(q);

	return ret;
}

int the_canonical_model_str(const char *q1, const char *q2)
{
	struct xpath_tree *q1_parsed, *q2_parsed;
	int ret;

	q1_parsed = xpath_parser(q1);
	q2_parsed = xpath_parser(q2);

	ret = the_canonical_model(q1_parsed, q2_parsed);

	delete_xpath_tree(q1_parsed);
	delete_xpath_tree(q2_parsed);	

	return ret;
}
