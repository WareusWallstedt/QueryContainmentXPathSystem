#ifndef XPATH_TREE_H
#define XPATH_TREE_H

#include <stdio.h>
#include <stddef.h>

enum xpath_tree_type {
	CHILD,
	DESCENDANT
};

struct xpath_tree {
	enum xpath_tree_type type;
	size_t label_len;
	char *label;
	struct xpath_tree *next;
	struct xpath_tree **preds;
	size_t preds_len;
	size_t preds_alloc;
	struct xpath_tree *parent;
};

void xpath_tree_constructor(struct xpath_tree *this,
                            enum xpath_tree_type type,
                            size_t label_len,
                            const char *label);

void xpath_tree_destructor(struct xpath_tree *this);

struct xpath_tree *new_xpath_tree(enum xpath_tree_type type,
                                  size_t label_len,
                                  const char *label);

void delete_xpath_tree(struct xpath_tree *this);

struct xpath_tree *xpath_tree_copy(struct xpath_tree *this);

void xpath_tree_add_x_to_selection_node(struct xpath_tree *this);

void xpath_tree_add_pred(struct xpath_tree *this,
                         struct xpath_tree *pred);

int xpath_tree_sprint(struct xpath_tree *this,
                      char *dest);

int xpath_tree_fprint(struct xpath_tree *this, FILE *fp);

#endif
