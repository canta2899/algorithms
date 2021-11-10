#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#define MAXVALUE 32
#define RED 1
#define BLACK 0

typedef struct node{
	char value[MAXVALUE];
	int key;
	int col;
	struct node *left;
	struct node *right;
	struct node *parent;
} node;

void insert(node **root, int key, char *value);

void delete(node **root, node *del);

void freetree(node *root);

void inorder(node *root);

void preorder(node *root);

void postorder(node *root);

#endif

