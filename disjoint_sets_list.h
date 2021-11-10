#ifndef DISJOINT_SETS_LIST_H
#define DISJOINT_SETS_LIST_H

#define MAXVALUE 32

typedef struct node{
	int key;
	int len;
	char value[MAXVALUE];	
	struct node *rep;
	struct node *last;
	struct node *next;
} node;

node *Make(int key, char *value);

node *Find(node *x);

node *Union(node *x, node *y);

void freeset(node *n);

#endif
