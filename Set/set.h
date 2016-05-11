#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stddef.h>

#include "Binary-Tree/binary_tree.h"

struct set {
	size_t size;
	struct binary_tree *root;
	void (*delete_data)(void *);		/* Can be NULL */
	int (*data_cmp)(void *, void *);	/* Can be NULL */
	void *(*data_copy)(void *);		/* Can be NULL */
	void (*data_print)(void *, FILE *);	/* Can be NULL */
};

void set_constructor(struct set *this,
                     void (*delete_data)(void *),
                     int (*data_cmp)(void *, void *),
                     void *(*data_copy)(void *),
                     void (*data_print)(void *, FILE *));

void set_destructor(struct set *this);

struct set *new_set(void (*delete_data)(void *),
                    int (*data_cmp)(void *, void *),
                    void *(*data_copy)(void *),
                    void (*data_print)(void *, FILE *));

void delete_set(struct set *this);

struct set *set_copy(struct set *this);

int set_contains(struct set *this, void *data);

int set_insert(struct set *this, void *data);

void set_to_array(struct set *this, void **array, size_t *len);

size_t set_sprint(struct set *this, char *dest);

size_t set_fprint(struct set *this, FILE *fp);

#endif
