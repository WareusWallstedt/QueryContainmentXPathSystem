#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "xpath_tree.h"

void xpath_tree_constructor(struct xpath_tree *this,
                            enum xpath_tree_type type,
                            size_t label_len,
                            const char *label)
{
	this->type = type;
	this->label_len = label_len;
	this->label = malloc(label_len + 1);
	strcpy(this->label, label);
	this->next = NULL;
	this->preds_len = 0;
	this->preds_alloc = 16;
	this->preds = malloc(sizeof(struct xpath_tree *) * this->preds_alloc);
	this->parent = NULL;
}

void xpath_tree_destructor(struct xpath_tree *this)
{
	size_t i;

	if (this == NULL) {
		return;
	}

	free(this->label);

	for (i = 0; i < this->preds_len; ++i) {
		delete_xpath_tree(this->preds[i]);
	}

	free(this->preds);

	delete_xpath_tree(this->next);
}

struct xpath_tree *new_xpath_tree(enum xpath_tree_type type,
                                  size_t label_len,
                                  const char *label)
{
	struct xpath_tree *this;

	this = malloc(sizeof(struct xpath_tree));
	xpath_tree_constructor(this, type, label_len, label);

	return this;
}

void delete_xpath_tree(struct xpath_tree *this)
{
	if (this == NULL) {
		return;
	}

	xpath_tree_destructor(this);
	free(this);
}

struct xpath_tree *xpath_tree_copy(struct xpath_tree *this)
{
	struct xpath_tree *copy;
	size_t i;

	copy = new_xpath_tree(this->type, this->label_len, this->label);

	for (i = 0; i < this->preds_len; ++i) {
		xpath_tree_add_pred(copy, xpath_tree_copy(this->preds[i]));
	}

	if (this->next != NULL) {
		copy->next = xpath_tree_copy(this->next);
	}

	return copy;
}

void xpath_tree_add_x_to_selection_node(struct xpath_tree *this)
{
	if (this->next == NULL) {
		this->next = new_xpath_tree(CHILD, 1, "x");
	} else {
		xpath_tree_add_x_to_selection_node(this->next);
	}
}

void xpath_tree_add_pred(struct xpath_tree *this,
                         struct xpath_tree *pred)
{
	struct xpath_tree **tmp;
	size_t i;

	this->preds[this->preds_len] = pred;
	++this->preds_len;
	pred->parent = this;

	if (this->preds_len == this->preds_alloc) {
		this->preds_alloc *= 2;
		tmp = malloc(sizeof(struct xpath_tree *) * this->preds_alloc);

		for (i = 0; i < this->preds_len; ++i) {
			tmp[i] = this->preds[i];
		}

		free(this->preds);
		this->preds = tmp;
	}
}

int xpath_tree_sprint(struct xpath_tree *this,
                      char *dest)
{
	int i = 0;
	size_t j;


	if (this->type == CHILD) {
		i += sprintf(&dest[i], "/%s", this->label);
	} else {
		i += sprintf(&dest[i], "//%s", this->label);
	}


	for (j = 0; j < this->preds_len; ++j) {
		i += sprintf(&dest[i], "[");
		i += xpath_tree_sprint(this->preds[j], &dest[i]);
		i += sprintf(&dest[i], "]");
	}

	if (this->next != NULL) {
		i += xpath_tree_sprint(this->next, &dest[i]);
	}

	return i;
}

int xpath_tree_fprint(struct xpath_tree *this, FILE *fp)
{
	char str[1025];
	int ret;

	ret = xpath_tree_sprint(this, str);
	fprintf(fp, "%s", str);

	return ret;
}
