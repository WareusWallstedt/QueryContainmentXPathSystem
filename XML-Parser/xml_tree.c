#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "xml_tree.h"

#define INIT_CHILDREN_ALLOC 16

void xml_tree_constructor(struct xml_tree *this,
                          enum xml_tree_node_type type)
{
	this->type = type;
	this->dtd_filename_len = 0;
	this->dtd_filename = NULL;
	this->data_len = 0;
	this->data = NULL;

	if (type == TAG) {
		this->children_len = 0;
		this->children_alloc = INIT_CHILDREN_ALLOC;
		this->children = malloc(sizeof(struct xml_tree *) *
		                        INIT_CHILDREN_ALLOC);
	} else {
		this->children_len = 0;
		this->children_alloc = 0;
		this->children = NULL;
	}

	this->parent = NULL;
}

void xml_tree_destructor(struct xml_tree *this)
{
	size_t i;

	if (this == NULL) {
		return;
	}

	if (this->dtd_filename != NULL) {
		free(this->dtd_filename);
	}

	if (this->data != NULL) {
		free(this->data);
	}

	if (this->type == TAG) {
		for (i = 0; i < this->children_len; ++i) {
			delete_xml_tree(this->children[i]);
		}

		free(this->children);
	}
}

struct xml_tree *new_xml_tree(enum xml_tree_node_type type)
{
	struct xml_tree *this;

	this = malloc(sizeof(struct xml_tree));
	xml_tree_constructor(this, type);

	return this;
}

void delete_xml_tree(struct xml_tree *this)
{
	if (this == NULL) {
		return;
	}

	xml_tree_destructor(this);
	free(this);
}

void xml_tree_set_dtd_filename(struct xml_tree *this,
                               size_t dtd_filename_len,
                               char *dtd_filename)
{
	if (this->dtd_filename != NULL) {
		free(this->dtd_filename);
	}

	this->dtd_filename_len = dtd_filename_len;
	this->dtd_filename = malloc(dtd_filename_len + 1);
	strcpy(this->dtd_filename, dtd_filename);
}

void xml_tree_set_data(struct xml_tree *this,
                       size_t data_len,
                       char *data)
{
	if (this->data != NULL) {
		free(this->data);
	}

	this->data_len = data_len;
	this->data = malloc(data_len + 1);
	strcpy(this->data, data);
}

void xml_tree_add_child(struct xml_tree *this,
                        struct xml_tree *child)
{
	struct xml_tree **tmp;
	size_t i;

	this->children[this->children_len] = child;
	++this->children_len;
	child->parent = this;

	if (this->children_len == this->children_alloc) {
		this->children_alloc *= 2;
		tmp = malloc(sizeof(struct xml_tree *) *
		             this->children_alloc);

		for (i = 0; i < this->children_len; ++i) {
			tmp[i] = this->children[i];
		}

		free(this->children);
		this->children = tmp;
	}
}

void xml_tree_print(struct xml_tree *this, FILE *fp)
{
	size_t i;
	
	if (this->type == TAG) {
		if (this->dtd_filename != NULL) {
			fprintf(fp, "<!DOCTYPE %s SYSTEM \"%s\">\n",
			        this->data, this->dtd_filename);
		}
		if (this->children_len == 0) {
			fprintf(fp, "<%s />", this->data);
		} else {
			fprintf(fp, "<%s>", this->data);

			for (i = 0; i < this->children_len; ++i) {
				xml_tree_print(this->children[i], fp);
			}

			fprintf(fp, "</%s>", this->data);
		}
	} else {
		fprintf(fp, "%s", this->data);
	}
}
