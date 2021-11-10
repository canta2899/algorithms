#ifndef DISJOINT_SETS_TREE_H
#define DISJOINT_SETS_TREE_H

#define MAXVALUE 32

typedef struct node{
	char value[32];
	int key;
	int rank;
	struct node *parent;
} node;

node *Make(int key, char *value);

node *Find(node *x);

node *FindPC(node *x);

node *Union(node *x, node *y);

#endif
