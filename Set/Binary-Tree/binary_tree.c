#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "binary_tree.h"

void binary_tree_constructor(struct binary_tree *this,
                             void *data,
                             void (*delete_data)(void *),
                             int (*data_cmp)(void *, void *),
                             void *(*data_copy)(void *),
                             void (*data_print)(void *, FILE *))
{
	this->size = 1;
	this->data = data;
	this->delete_data = delete_data;
	this->data_cmp = data_cmp;
	this->data_copy = data_copy;
	this->data_print = data_print;
	this->left = NULL;
	this->right = NULL;
}

void binary_tree_destructor(struct binary_tree *this)
{
	if (this == NULL) {
		return;
	}

	delete_binary_tree(this->left);
	delete_binary_tree(this->right);

	if (this->delete_data != NULL) {
		this->delete_data(this->data);
	}
}

struct binary_tree *new_binary_tree(void *data,
                                    void (*delete_data)(void *),
                                    int (*data_cmp)(void *, void *),
                                    void *(*data_copy)(void *),
                                    void (*data_print)(void *, FILE *))
{
	struct binary_tree *this;

	this = malloc(sizeof(struct binary_tree));
	binary_tree_constructor(this,
	                        data,
	                        delete_data,
	                        data_cmp,
	                        data_copy,
	                        data_print);

	return this;
}

void delete_binary_tree(struct binary_tree *this)
{
	if (this == NULL) {
		return;
	}

	binary_tree_destructor(this);
	free(this);
}

struct binary_tree *binary_tree_copy(struct binary_tree *this)
{
	struct binary_tree *copy;

	if (this == NULL) {
		return NULL;
	}

	if (this->data_copy == NULL) {
		copy = new_binary_tree(this->data,
		                       this->delete_data,
		                       this->data_cmp,
		                       this->data_copy,
		                       this->data_print);
	} else {
		copy = new_binary_tree(this->data_copy(this->data),
		                       this->delete_data,
		                       this->data_cmp,
		                       this->data_copy,
		                       this->data_print);
	}

	copy->size = this->size;
	copy->left = binary_tree_copy(this->left);
	copy->right = binary_tree_copy(this->right);

	return copy;
}

int binary_tree_contains(struct binary_tree *this, void *data)
{
	int cmp;

	if (this == NULL) {
		return 0;
	}

	if (this->data_cmp == NULL) {
		cmp = (int)((long)data - (long)this->data);
	} else {
		cmp = this->data_cmp(data, this->data);
	}

	if (cmp == 0) {
		return 1;
	} else if (cmp < 1) {
		return binary_tree_contains(this->left, data);
	} else {
		return binary_tree_contains(this->right, data);
	}
}

int binary_tree_insert(struct binary_tree *this, void *data)
{
	int cmp;

	if (this->data_cmp == NULL) {
		cmp = (int)((long)data - (long)this->data);
	} else {
		cmp = this->data_cmp(data, this->data);
	}

	if (cmp == 0) {
		return 0;
	} else if (cmp < 1) {
		if (this->left == NULL) {
			this->left = new_binary_tree(data,
			                             this->delete_data,
			                             this->data_cmp,
			                             this->data_copy,
			                             this->data_print);
			++this->size;
			return 1;
		} else if (binary_tree_insert(this->left, data)) {
			++this->size;
			return 1;
		} else {
			return 0;
		}
	} else {
		if (this->right == NULL) {
			this->right = new_binary_tree(data,
			                              this->delete_data,
			                              this->data_cmp,
			                              this->data_copy,
			                              this->data_print);
			++this->size;
			return 1;
		} else if (binary_tree_insert(this->right, data)) {
			++this->size;
			return 1;
		} else {
			return 0;
		}
	}
}

void binary_tree_to_array(struct binary_tree *this, void **array, size_t *len)
{
	if (this->left != NULL) {
		binary_tree_to_array(this->left, array, len);
	}

	array[*len] = this->data;
	++*len;

	if (this->right != NULL) {
		binary_tree_to_array(this->right, array, len);
	}
}

/* TODO: Replace dummy function with actual function */
size_t binary_tree_sprint(struct binary_tree *this, char *dest)
{
	size_t i = 0;

	i += sprintf(&dest[i], "%lu", this->size);

	return i;
}

/* TODO: Replace dummy function with actual function */
size_t binary_tree_fprint(struct binary_tree *this, FILE *fp)
{
	fprintf(fp, "%lu", this->size);
	return this->size;
}
