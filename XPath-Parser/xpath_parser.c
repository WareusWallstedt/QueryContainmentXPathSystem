#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "xpath_tree.h"

static const char *_inp, *_inp_start;

static void parse_error(const char *expected)
{
	size_t i;

	fprintf(stderr, "Parse Error: Expected %s.\n", expected);
	fprintf(stderr, "%s\n", _inp_start);

	for (i = 0; i < (size_t)(_inp - _inp_start); ++i) {
		fputc(' ', stderr);
	}

	fputs("^\n", stderr);

	exit(EXIT_FAILURE);
}

static int rule_name(char *dest)
{
	int i;

	if (!isalpha(*_inp) && *_inp != ':' && *_inp != '_') {
		parse_error("(\':\' | [A-Z] | \'_\' | [a-z])");
	}

	dest[0] = *_inp;
	i = 1;
	++_inp;

	while (isalnum(*_inp) || *_inp == ':'
	       || *_inp == '_' || *_inp == '-' || *_inp == '.') {
		dest[i] = *_inp;
		++i;
		++_inp;
	}

	dest[i] = '\0';

	return i;
}

static struct xpath_tree *rule_expr(struct xpath_tree *parent);

static struct xpath_tree *rule_step(struct xpath_tree *parent)
{
	struct xpath_tree *t;
	int label_len;
	static char label[1025];
	enum xpath_tree_type type = CHILD;

	if (*_inp != '/') {
		parse_error("(\'/\' | \'//\')");
	}

	++_inp;

	if (*_inp == '/') {
		++_inp;
		type = DESCENDANT;
	}

	if (*_inp == '*') {
		++_inp;
		label_len = sprintf(label, "*");
	} else {
		label_len = rule_name(label);
	}

	t = new_xpath_tree(type, label_len, label);
	t->parent = parent;

	while (*_inp == '[') {
		++_inp;
		xpath_tree_add_pred(t, rule_expr(t));

		if (*_inp != ']') {
			parse_error("\']\'");
		}

		++_inp;
	}

	if (*_inp == '/') {
		t->next = rule_step(t);
	}

	return t;
}

static struct xpath_tree *rule_expr(struct xpath_tree *parent)
{
	struct xpath_tree *t;
	int label_len;
	static char label[1025];
	enum xpath_tree_type type = CHILD;

	if (*_inp == '/') {
		++_inp;

		if (*_inp == '/') {
			++_inp;
			type = DESCENDANT;
		}
	}

	if (*_inp == '*') {
		++_inp;
		label_len = sprintf(label, "*");
	} else {
		label_len = rule_name(label);
	}

	t = new_xpath_tree(type, label_len, label);
	t->parent = parent;

	while (*_inp == '[') {
		++_inp;
		xpath_tree_add_pred(t, rule_expr(t));

		if (*_inp != ']') {
			parse_error("\']\'");
		}

		++_inp;
	}

	if (*_inp == '/') {
		t->next = rule_step(t);
	}

	return t;
}

static struct xpath_tree *rule_xpath()
{
	struct xpath_tree *t;

	t = rule_expr(NULL);

	if (*_inp != '\0') {
		parse_error("\'\\0\'");
	}

	return t;
}

struct xpath_tree *xpath_parser(const char *xpath_expr)
{
	_inp = _inp_start = xpath_expr;
	return rule_xpath();
}
