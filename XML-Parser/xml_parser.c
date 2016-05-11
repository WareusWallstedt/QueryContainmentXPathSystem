#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "xml_tree.h"

#define BUF_LEN 1024

static const char *_filename;
static FILE *_inp;
static size_t _line;
static size_t _col;

static int _buf[BUF_LEN];
static size_t _buf_idx;
static int _cur;

static void parse_error(const char *expected)
{
	fprintf(stderr, "Parse Error: %s:%lu:%lu: Expected %s.\n",
	        _filename, _line, _col, expected);
	exit(EXIT_FAILURE);
}

static int next_str(const char *str)
{
	size_t i;

	i = _buf_idx;

	while (*str != '\0') {
		if (_buf[i] != *str) {
			return 0;
		}

		++str;
		++i;

		if (i == BUF_LEN) {
			i = 0;
		}
	}

	return 1;
}

static void next_single_char()
{
	if (_cur == '\n') {
		++_line;
		_col = 1;
	} else {
		++_col;
	}

	_buf[_buf_idx] = fgetc(_inp);
	++_buf_idx;

	if (_buf_idx == BUF_LEN) {
		_buf_idx = 0;
	}

	_cur = _buf[_buf_idx];
}

static void next_n_char(size_t n)
{
	size_t i;

	for (i = 0; i < n; ++i) {
		next_single_char();
	}
}

static void next_char()
{
	next_n_char(1);

	while (next_str("<!--")) {
		next_n_char(4);

		while (!next_str("-->")) {
			next_single_char();
		}

		next_n_char(3);
	}
}

static void exact_str(const char *str)
{
	while (*str != '\0') {
		if (_cur != *str) {
			parse_error(str);
		}

		++str;
		next_char();
	}
}

static void rule_whitespace()
{
	if (!isspace(_cur)) {
		parse_error("(#x20 | #x9 | #xD | #xA)");
	}

	next_char();

	while (isspace(_cur)) {
		next_char();
	}
}

static char *rule_name()
{
	static char name[1025];
	size_t i;

	if (!isalpha(_cur) && _cur != ':' && _cur != '_') {
		parse_error("(\":\" | [A-Z] | \"_\" | [a-z])");
	}

	name[0] = _cur;
	i = 1;
	next_char();

	while (isalnum(_cur)
	       || _cur == ':' || _cur == '_'
	       || _cur == '-' || _cur == '.') {
		name[i] = _cur;
		++i;
		next_char();
	}

	name[i] = '\0';

	return strdup(name);
}

static struct xml_tree *rule_chardata(struct xml_tree *parent)
{
	struct xml_tree *t;
	static char data[1025];
	size_t i = 0;

	t = new_xml_tree(TEXT);
	t->parent = parent;

	while (_cur != '<') {
		data[i] = _cur;
		next_char();
		++i;
	}

	data[i] = '\0';
	xml_tree_set_data(t, i, data);

	return t;
}

static struct xml_tree *rule_element(struct xml_tree *parent)
{
	struct xml_tree *t, *tmp;
	char *name;

	t = new_xml_tree(TAG);
	t->parent = parent;
	exact_str("<");
	name = rule_name();
	xml_tree_set_data(t, strlen(name), name);
	free(name);

	/* Skip attributes. */
	while (_cur != '>' && !next_str("/>")) {
		next_char();
	}

	if (_cur == '/') {
		exact_str("/>");
		return t;
	}

	exact_str(">");

	while (!next_str("</")) {
		if (_cur == '<') {
			tmp = rule_element(t);
			xml_tree_add_child(t, tmp);
		} else {
			tmp = rule_chardata(t);
			xml_tree_add_child(t, tmp);
		}
	}

	exact_str("</");
	name = rule_name();

	if (strcmp(t->data, name) != 0) {
		parse_error(t->data);
	}

	free(name);

	if (isspace(_cur)) {
		rule_whitespace();
	}

	exact_str(">");

	return t;
}

static char *rule_external_id()
{
	static char name[1025];
	size_t i = 0;

	exact_str("SYSTEM");
	rule_whitespace();

	if (_cur == '\'') {
		next_char();

		while (_cur != '\'') {
			if (_cur == EOF) {
				parse_error("(\')");
			}

			name[i] = _cur;
			++i;
			next_char();
		}

		next_char();
	} else if (_cur == '\"') {
		next_char();

		while (_cur != '\"') {
			if (_cur == EOF) {
				parse_error("(\")");
			}

			name[i] = _cur;
			++i;
			next_char();
		}

		next_char();
	} else {
		parse_error("(\'\"\' | \"\'\")");
	}

	name[i] = '\0';

	return strdup(name);
}

static char *rule_prolog()
{
	char *dtd_filename = NULL;

	if (next_str("<?xml")) {
		next_n_char(5);
		rule_whitespace();
		exact_str("version");

		if (isspace(_cur)) {
			rule_whitespace();
		}

		exact_str("=");

		if (isspace(_cur)) {
			rule_whitespace();
		}

		if (_cur == '\'') {
			next_char();
			exact_str("1.");

			while (isdigit(_cur)) {
				next_char();
			}

			exact_str("\'");
		} else if (_cur == '\"') {
			next_char();
			exact_str("1.");

			while (isdigit(_cur)) {
				next_char();
			}

			exact_str("\"");
		} else {
			parse_error("(\"\'\" | \'\"\')");
		}

		/* Skip EncodingDecl? SDDecl? */
		while (!next_str("?>")) {
			if (_cur == EOF) {
				parse_error("\'?>\'");
			}

			next_char();
		}

		next_n_char(2);
	}

	if (isspace(_cur)) {
		rule_whitespace();
	}

	if (next_str("<!DOCTYPE")) {
		next_n_char(9);
		rule_whitespace();
		free(rule_name());
		rule_whitespace();
		dtd_filename = rule_external_id();

		if (isspace(_cur)) {
			rule_whitespace();
		}

		while (_cur != '>') {
			if (_cur == EOF) {
				parse_error("\'>\'");
			}

			next_char();
		}

		next_char();

		if (isspace(_cur)) {
			rule_whitespace();
		}
	}

	return dtd_filename;
}

static struct xml_tree *rule_document()
{
	struct xml_tree *t;
	char *dtd_filename;

	dtd_filename = rule_prolog();
	t = rule_element(NULL);

	if (dtd_filename != NULL) {
		xml_tree_set_dtd_filename(t,
		                          strlen(dtd_filename),
		                          dtd_filename);
		free(dtd_filename);
	}

	while (isspace(_cur)) {
		rule_whitespace();
	}

	if (_cur != EOF) {
		parse_error("EOF");
	}

	return t;
}

struct xml_tree *xml_parser(const char *xml_filename)
{
	size_t i;
	struct xml_tree *t;

	_filename = xml_filename;
	_inp = fopen(xml_filename, "r");

	if (_inp == NULL) {
		perror(xml_filename);
		exit(EXIT_FAILURE);
	}

	_line = 1;
	_col = 1;

	for (i = 0; i < BUF_LEN; ++i) {
		_buf[i] = fgetc(_inp);
	}

	_buf_idx = 0;
	_cur = _buf[0];

	t = rule_document();

	fclose(_inp);

	return t;
}
