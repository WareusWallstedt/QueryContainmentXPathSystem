#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "set.h"
#include "Binary-Tree/binary_tree.h"

void set_constructor(struct set *this,
                     void (*delete_data)(void *),
                     int (*data_cmp)(void *, void *),
                     void *(*data_copy)(void *),
                     void (*data_print)(void *, FILE *))
{
	this->size = 0;
	this->root = NULL;
	this->delete_data = delete_data;
	this->data_cmp = data_cmp;
	this->data_copy = data_copy;
	this->data_print = data_print;
}

void set_destructor(struct set *this)
{
	if (this == NULL) {
		return;
	}

	delete_binary_tree(this->root);
}

struct set *new_set(void (*delete_data)(void *),
                    int (*data_cmp)(void *, void *),
                    void *(*data_copy)(void *),
                    void (*data_print)(void *, FILE *))
{
	struct set *this;

	this = malloc(sizeof(struct set));
	set_constructor(this,
	                delete_data,
	                data_cmp,
	                data_copy,
	                data_print);

	return this;
}

void delete_set(struct set *this)
{
	if (this == NULL) {
		return;
	}

	set_destructor(this);
	free(this);
}

struct set *set_copy(struct set *this)
{
	return (struct set *)(size_t)(this == NULL);
}

int set_contains(struct set *this, void *data)
{
	return binary_tree_contains(this->root, data);
}

int set_insert(struct set *this, void *data)
{
	if (this->root == NULL) {
		this->root = new_binary_tree(data,
		                             this->delete_data,
		                             this->data_cmp,
		                             this->data_copy,
		                             this->data_print);
		return 1;
	} else if (binary_tree_insert(this->root, data)) {
		++this->size;
		return 1;
	} else {
		return 0;
	}
}

void set_to_array(struct set *this, void **array, size_t *len)
{
	*len = 0;

	if (this->root != NULL) {
		binary_tree_to_array(this->root, array, len);
	}
}

size_t set_sprint(struct set *this, char *dest)
{
	size_t i = 0;

	i += sprintf(&dest[i], "%lu", this->size);

	return i;
}

size_t set_fprint(struct set *this, FILE *fp)
{
	return fprintf(fp, "%lu", this->size);
}
