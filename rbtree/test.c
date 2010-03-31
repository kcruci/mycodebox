#include <stdio.h>
#include "rbtree.h"

struct page {
	unsigned long offset;
	struct rb_node node;
};

static inline struct page * rb_search_page(struct rb_root *root,
						 unsigned long offset)
{
	struct rb_node * n = root->rb_node;
	struct page * page;

	while (n) {
		page = rb_entry(n, struct page, node);

		if (offset < page->offset)
			n = n->rb_left;
		else if (offset > page->offset)
			n = n->rb_right;
		else
			return page;
	}
	return NULL;
}

static inline struct page * rb_insert_page(struct rb_root *root, struct page *page1)
{
	struct rb_node ** p = &root->rb_node;
	struct rb_node * parent = NULL;
	struct rb_node * node = &page1->node;
	struct page * page;
	unsigned long offset = page1->offset;

	while (*p) {
		parent = *p;
		page = rb_entry(parent, struct page, node);

		if (offset < page->offset)
			p = &(*p)->rb_left;
		else if (offset > page->offset)
			p = &(*p)->rb_right;
		else
			return page;
	}

	rb_link_node(node, parent, p);
	rb_insert_color(node, root);
	return NULL;
}

struct rb_root page_root = {
	.rb_node = NULL,
};

int main(int argc, char **argv)
{
	struct page page1 = {
		.offset = 1,
	};
	struct page page2 = {
		.offset = 2,
	};
	struct page page3 = {
		.offset = 3,
	};

	struct page *page;

	RB_CLEAR_NODE(&page1.node);
	RB_CLEAR_NODE(&page2.node);
	RB_CLEAR_NODE(&page3.node);

	rb_insert_page(&page_root, &page1);
	rb_insert_page(&page_root, &page2);
	rb_insert_page(&page_root, &page3);

//	printf("%X\n", (unsigned long)page_root.rb_node);
//	printf("%X\n", (unsigned long)&page1.node);

	page = rb_search_page(&page_root, 2);
	if (page)
		printf("find page %lu\n", page->offset);

	return 0;
}
