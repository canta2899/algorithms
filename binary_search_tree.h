#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#define MAXVALUE 32
#define STACKSIZE 1024

typedef struct node{
	char value[MAXVALUE];
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
} node;

node *search(node *root, int key);

void insert(node **root, int key, char *value);

void delete(node **root, node *del);

void freetree(node *root);

void inorder(node *root);

void preorder(node *root);

void postorder(node *root);

#endif

