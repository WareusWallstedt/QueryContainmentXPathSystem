#ifndef XML_TREE_H
#define XML_TREE_H

#include <stdio.h>
#include <stddef.h>

enum xml_tree_node_type {
	TAG,
	TEXT
};

struct xml_tree {
	enum xml_tree_node_type type;
	size_t dtd_filename_len;
	char *dtd_filename;
	size_t data_len;
	char *data;
	size_t children_len;
	size_t children_alloc;
	struct xml_tree **children;
	struct xml_tree *parent;
};

void xml_tree_constructor(struct xml_tree *this,
                          enum xml_tree_node_type type);

void xml_tree_destructor(struct xml_tree *this);

struct xml_tree *new_xml_tree(enum xml_tree_node_type type);

void delete_xml_tree(struct xml_tree *this);

void xml_tree_set_dtd_filename(struct xml_tree *this,
                               size_t dtd_filename_len,
                               char *dtd_filename);

void xml_tree_set_data(struct xml_tree *this,
                       size_t data_len,
                       char *data);

void xml_tree_add_child(struct xml_tree *this,
                        struct xml_tree *child);

void xml_tree_print(struct xml_tree *this, FILE *fp);

#endif
