#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "xpath_tree_node.h"
#include "xpath_containment_alg1.h"


void test_replacing_desc_edges()
{
	struct xpath_tree_node *p1, *p2, *p3;
	size_t desc_edges_counter = 0;

	p1 = new_xpath_tree_node();
	p1->label = strdup("a");
	p2 = new_xpath_tree_node();
	p2->label = strdup("b");
	xpath_tree_node_add_child(p1, p2);
	p3 = new_xpath_tree_node();
	p3->label = strdup("d");
	xpath_tree_node_add_descendant(p2, p3);
	p3 = new_xpath_tree_node();
	p3->label = strdup("*");
	xpath_tree_node_add_child(p2, p3);
	p2 = new_xpath_tree_node();
	p2->label = strdup("c");
	xpath_tree_node_add_child(p3, p2);

	printf("p:\n");
	xpath_tree_node_print(p1, stdout);

	xpath_tree_node_rename_all_labels(p1, "*", "z");

	printf("p: (renamed * -> z)\n");
	xpath_tree_node_print(p1, stdout);

	p2 = new_xpath_tree_node_replace_descendant_edges(p1, &desc_edges_counter, "z");
	printf("p': (replaced // with 0 /z)\n");
	xpath_tree_node_print(p2, stdout);
	delete_xpath_tree_node(&p2);

	desc_edges_counter = 1;

	p2 = new_xpath_tree_node_replace_descendant_edges(p1, &desc_edges_counter, "z");
	printf("p'': (replaced // with 1 /z)\n");
	xpath_tree_node_print(p2, stdout);
	delete_xpath_tree_node(&p2);

	desc_edges_counter = 2;

	p2 = new_xpath_tree_node_replace_descendant_edges(p1, &desc_edges_counter, "z");
	printf("p''': (replaced // with 2 /z)\n");
	xpath_tree_node_print(p2, stdout);
	delete_xpath_tree_node(&p2);

	printf("p:\n");
	xpath_tree_node_print(p1, stdout);
	delete_xpath_tree_node(&p1);
}

void test1_alg1()
{
	struct xpath_tree_node *p, *q;
	struct xpath_tree_node *tmp1, *tmp2;

	p = new_xpath_tree_node();
	p->label = strdup("a");
	tmp1 = new_xpath_tree_node();
	tmp1->label = strdup("b");
	xpath_tree_node_add_child(p, tmp1);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("d");
	xpath_tree_node_add_descendant(tmp1, tmp2);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("*");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp1 = new_xpath_tree_node();
	tmp1->label = strdup("c");
	xpath_tree_node_add_child(tmp2, tmp1);

	q = new_xpath_tree_node();
	q->label = strdup("a");
	tmp1 = new_xpath_tree_node();
	tmp1->label = strdup("d");
	xpath_tree_node_add_descendant(q, tmp1);
	tmp1 = new_xpath_tree_node();
	tmp1->label = strdup("*");
	xpath_tree_node_add_child(q, tmp1);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("c");
	xpath_tree_node_add_descendant(tmp1, tmp2);
#ifndef DEBUG
	printf("p:\n");
	xpath_tree_node_print(p, stdout);
	printf("\nq:\n");
	xpath_tree_node_print(q, stdout);
#endif
	printf("\nContainment: %s\n", xpath_containment_alg1(p, q) ? "true" : "false");

	delete_xpath_tree_node(&p);
	delete_xpath_tree_node(&q);
}

void test2_alg1()
{
	struct xpath_tree_node *p, *q;
	struct xpath_tree_node *tmp1, *tmp2, *tmp3, *tmp4;

	p = new_xpath_tree_node();
	p->label = strdup("a");
	tmp1 = new_xpath_tree_node();
	tmp1->label = strdup("b");
	xpath_tree_node_add_child(p, tmp1);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("c");
	xpath_tree_node_add_descendant(tmp1, tmp2);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("c");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("d");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp3 = new_xpath_tree_node();
	tmp3->label = strdup("c");
	xpath_tree_node_add_child(tmp2, tmp3);
	tmp1 = new_xpath_tree_node();
	tmp1->label = strdup("b");
	xpath_tree_node_add_child(p, tmp1);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("c");
	xpath_tree_node_add_descendant(tmp1, tmp2);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("c");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("d");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp3 = new_xpath_tree_node();
	tmp3->label = strdup("d");
	xpath_tree_node_add_child(tmp2, tmp3);
	tmp4 = new_xpath_tree_node();
	tmp4->label = strdup("c");
	xpath_tree_node_add_child(tmp3, tmp4);
	tmp1 = new_xpath_tree_node();
	tmp1->label = strdup("b");
	xpath_tree_node_add_child(p, tmp1);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("c");
	xpath_tree_node_add_descendant(tmp1, tmp2);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("d");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp3 = new_xpath_tree_node();
	tmp3->label = strdup("c");
	xpath_tree_node_add_child(tmp2, tmp3);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("d");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp3 = new_xpath_tree_node();
	tmp3->label = strdup("d");
	xpath_tree_node_add_child(tmp2, tmp3);
	tmp4 = new_xpath_tree_node();
	tmp4->label = strdup("c");
	xpath_tree_node_add_child(tmp3, tmp4);

	q = new_xpath_tree_node();
	q->label = strdup("a");
	tmp1 = new_xpath_tree_node();
	tmp1->label = strdup("b");
	xpath_tree_node_add_child(q, tmp1);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("c");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("*");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp3 = new_xpath_tree_node();
	tmp3->label = strdup("c");
	xpath_tree_node_add_child(tmp2, tmp3);
	tmp2 = new_xpath_tree_node();
	tmp2->label = strdup("*");
	xpath_tree_node_add_child(tmp1, tmp2);
	tmp3 = new_xpath_tree_node();
	tmp3->label = strdup("*");
	xpath_tree_node_add_child(tmp2, tmp3);
	tmp4 = new_xpath_tree_node();
	tmp4->label = strdup("c");
	xpath_tree_node_add_child(tmp3, tmp4);
#ifndef DEBUG
	printf("p:\n");
	xpath_tree_node_print(p, stdout);
	printf("\nq:\n");
	xpath_tree_node_print(q, stdout);
#endif
	printf("\nContainment: %s\n", xpath_containment_alg1(p, q) ? "true" : "false");

	delete_xpath_tree_node(&p);
	delete_xpath_tree_node(&q);
}

int main()
{
	struct xpath_tree_node *p1, *p2, *p3, *p4;

	test_replacing_desc_edges();
	test1_alg1();
	test2_alg1();

	p1 = new_xpath_tree_node();
	p1->label = strdup("a");
	p2 = new_xpath_tree_node();
	p2->label = strdup("b");
	xpath_tree_node_add_child(p1, p2);
	p3 = new_xpath_tree_node();
	p3->label = strdup("d");
	xpath_tree_node_add_descendant(p2, p3);
	p3 = new_xpath_tree_node();
	p3->label = strdup("*");
	xpath_tree_node_add_child(p2, p3);
	p2 = new_xpath_tree_node();
	p2->label = strdup("c");
	xpath_tree_node_add_child(p3, p2);

	xpath_tree_node_print(p1, stdout);

	assert(xpath_tree_node_has_label(p1, "a"));
	assert(xpath_tree_node_has_label(p1, "b"));
	assert(xpath_tree_node_has_label(p1, "c"));
	assert(xpath_tree_node_has_label(p1, "d"));
	assert(xpath_tree_node_has_label(p1, "*"));
	assert(!xpath_tree_node_has_label(p1, "z"));
	assert(xpath_tree_node_longest_child_wildcard_chain(p1, 0, 0) == 1);
	assert(xpath_tree_node_n_descendant_edges(p1) == 1);

	xpath_tree_node_rename_all_labels(p1, "*", "z");

	assert(xpath_tree_node_has_label(p1, "a"));
	assert(xpath_tree_node_has_label(p1, "b"));
	assert(xpath_tree_node_has_label(p1, "c"));
	assert(xpath_tree_node_has_label(p1, "d"));
	assert(!xpath_tree_node_has_label(p1, "*"));
	assert(xpath_tree_node_has_label(p1, "z"));
	assert(xpath_tree_node_longest_child_wildcard_chain(p1, 0, 0) == 0);
	assert(xpath_tree_node_n_descendant_edges(p1) == 1);

	delete_xpath_tree_node(&p1);

	p1 = new_xpath_tree_node();
	p1->label = strdup("a");
	p2 = new_xpath_tree_node();
	p2->label = strdup("b");
	xpath_tree_node_add_child(p1, p2);
	p3 = new_xpath_tree_node();
	p3->label = strdup("c");
	xpath_tree_node_add_child(p2, p3);
	p3 = new_xpath_tree_node();
	p3->label = strdup("*");
	xpath_tree_node_add_child(p2, p3);
	p4 = new_xpath_tree_node();
	p4->label = strdup("c");
	xpath_tree_node_add_child(p3, p4);
	p3 = new_xpath_tree_node();
	p3->label = strdup("*");
	xpath_tree_node_add_child(p2, p3);
	p4 = new_xpath_tree_node();
	p4->label = strdup("*");
	xpath_tree_node_add_child(p3, p4);
	p3 = new_xpath_tree_node();
	p3->label = strdup("c");
	xpath_tree_node_add_child(p4, p3);

	xpath_tree_node_print(p1, stdout);

	assert(xpath_tree_node_has_label(p1, "a"));
	assert(xpath_tree_node_has_label(p1, "b"));
	assert(xpath_tree_node_has_label(p1, "c"));
	assert(!xpath_tree_node_has_label(p1, "d"));
	assert(xpath_tree_node_has_label(p1, "*"));
	assert(!xpath_tree_node_has_label(p1, "z"));
	assert(xpath_tree_node_longest_child_wildcard_chain(p1, 0, 0) == 2);
	assert(xpath_tree_node_n_descendant_edges(p1) == 0);

	xpath_tree_node_rename_all_labels(p1, "*", "z");

	assert(xpath_tree_node_has_label(p1, "a"));
	assert(xpath_tree_node_has_label(p1, "b"));
	assert(xpath_tree_node_has_label(p1, "c"));
	assert(!xpath_tree_node_has_label(p1, "d"));
	assert(!xpath_tree_node_has_label(p1, "*"));
	assert(xpath_tree_node_has_label(p1, "z"));
	assert(xpath_tree_node_longest_child_wildcard_chain(p1, 0, 0) == 0);
	assert(xpath_tree_node_n_descendant_edges(p1) == 0);

	delete_xpath_tree_node(&p1);

	return 0;
}
