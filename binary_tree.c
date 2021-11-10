/*
 * Implementation of Binary Trees with procedures for:
 *		
 *		- In order visit
 *		- Pre order visit
 *		- Post order visit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VALUE 50

typedef struct node{
	int key;
	char value[MAX_VALUE];
	struct node *left;
	struct node *right;
} node;


void in_order(node *root, int nulls){
	if(root != NULL){
		in_order(root->left, nulls);
		printf("[Key: %d, Value: %s] ", root->key, root->value);
		in_order(root->right, nulls);	
	}else{
		if(nulls){
			printf("NULL ");
		}
	}
}

void pre_order(node *root, int nulls){
	if(root != NULL){
		printf("[Key: %d, Value: %s] ", root->key, root->value);
		pre_order(root->left, nulls);
		pre_order(root->right, nulls);
	}else{
		if(nulls){
			printf("NULL ");
		}
	}
}

void post_order(node *root, int nulls){
	if(root != NULL){
		post_order(root->left, nulls);
		post_order(root->right, nulls);
		printf("[Key: %d, Value: %s] ", root->key, root->value);
	}else{
		if(nulls){
			printf("NULL ");
		}
	}
}

node *make_node(int key, char *value){
	node *newnode = malloc(sizeof(node));
	newnode->key = key;
	strcpy(newnode->value, value);
	newnode->left = NULL;
	newnode->right = NULL;	
	return newnode;
}

void free_tree(node *root){
	if(root != NULL){
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main(){
	node *root = make_node(1, "uno");
	root->left = make_node(2, "due");
	root->right = make_node(3, "tre");
	in_order(root, 1);
	printf("\n");
	free_tree(root);
}
