#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stddef.h>

struct binary_tree {
	size_t size;
	void *data;
	void (*delete_data)(void *);		/* Can be NULL */
	int (*data_cmp)(void *, void *);	/* Can be NULL */
	void *(*data_copy)(void *);		/* Can be NULL */
	void (*data_print)(void *, FILE *);	/* Can be NULL */
	struct binary_tree *left;
	struct binary_tree *right;
};

void binary_tree_constructor(struct binary_tree *this,
                             void *data,
                             void (*delete_data)(void *),
                             int (*data_cmp)(void *, void *),
                             void *(*data_copy)(void *),
                             void (*data_print)(void *, FILE *));

void binary_tree_destructor(struct binary_tree *this);

struct binary_tree *new_binary_tree(void *data,
                                    void (*delete_data)(void *),
                                    int (*data_cmp)(void *, void *),
                                    void *(*data_copy)(void *),
                                    void (*data_print)(void *, FILE *));

void delete_binary_tree(struct binary_tree *this);

struct binary_tree *binary_tree_copy(struct binary_tree *this);

int binary_tree_contains(struct binary_tree *this, void *data);

int binary_tree_insert(struct binary_tree *this, void *data);

void binary_tree_to_array(struct binary_tree *this, void **array, size_t *len);

size_t binary_tree_sprint(struct binary_tree *this, char *dest);

size_t binary_tree_fprint(struct binary_tree *this, FILE *fp);

#endif
