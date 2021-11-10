/*
 *	Red Black Trees
 *	---------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "red_black_tree.h"

// Sentinel NIL 

node nilnode = {"NIL", -1, BLACK, NULL, NULL, NULL};
node *NIL = &nilnode;


/**
 * Allocate a new node on the heap
 * New node has RED color, NULL parent
 * and NIL left and right children by default
 */
node *makenode(int key, char *value){
	node *newnode = malloc(sizeof(node));
	newnode->key = key;
	strcpy(newnode->value, value);
	newnode->col = RED;
	newnode->left = NIL;
	newnode->right = NIL;
	newnode->parent = NULL;
	return newnode;
}


/*
 * Finds the max key of a subtree given
 * the root of the subtree
 */
node *findmax(node *root){
	while(root->right != NIL){
		root = root->right;	
	}
	return root;
}


/*
 * Finds the min key of a subtree given
 * the root of the subtree
 */
node *findmin(node *root){
	while(root->left != NIL){
		root = root->left;
	}
	return root;
}


/*
 * Searches for a key inside a subtree
 * given the subtree root pointer and key
 */
node *search(node *root, int key){
	while(root != NIL){
		if(root->key == key)
			return root;
		else if(root->key > key)
			root = root->left;
		else
			root = root->right;
	}
	return NULL;
}


/*
 * Finds the successor of the given node
 */
node *successor(node *n){
	if(n != NIL){
		if(n->right != NIL){
			return findmin(n->right);
		}else{
			node *temp = n->parent;
			while(temp != NIL && n == temp->right){
				n = temp;
				temp = temp->parent;
			}
			return temp;
		}
	}else{
		return NULL;
	}
}


/*
 * Finds the predecessor of the given node
 */
node *predecessor(node *n){
	if(n != NIL){
		if(n->left != NIL){
			return findmax(n->left);
		}else{
			node *temp = n->parent;
			while(temp != NIL && n == temp->left){
				n = temp;
				temp = temp->parent;
			}
			return temp;
		}
	}else{
		return NULL;
	}	
}


/*
 * Apply left rotation to node n where tree
 * root pointer to pointer is root
 */
void leftrotate(node **root, node *n){
	node *y = n->right;
	n->right = y->left;

	if(y->left != NIL){
		y->left->parent = n;
	}
	y->parent = n->parent;
	if(n->parent == NULL){
		*root = y;
	}else if(n == n->parent->right){
		n->parent->right = y;
	}else {
		n->parent->left = y;
	}	
	y->left = n;
	n->parent = y;
}


/*
 * Apply right rotation to node n where tree
 * root pointer to pointer is root
 */
void rightrotate(node **root, node *n){
	node *y = n->left;
	n->left = y->right;

	if(y->right != NIL){
		y->right->parent = n;
	}
	y->parent = n->parent;
	if(n->parent == NULL){
		*root = y;
	}else if(n == n->parent->right){
		n->parent->right = y;
	}else {
		n->parent->left = y;
	}	
	y->right = n;
	n->parent = y;
}


/*
 * Perform insertion fixup given tree
 * root and new node inserted 
 */
void fixup_insertion(node **root, node *new){
	node *uncle, *parent, *gparent;
	int temp;
	while(new != *root && new->col == RED && new->parent->col == RED){
		parent = new->parent;
		gparent = parent->parent;
		// Case A
		if (parent == gparent->left){
			uncle = gparent->right;
			// 1
			if (uncle != NIL && uncle->col == RED){
				gparent->col = RED;
				parent->col = BLACK;
				uncle->col = BLACK;
				new = gparent;
			}else{ // 2
				if (new == parent->right){
					leftrotate(root, parent);
					new = parent;
					parent = new->parent;
				}

				// 3
				rightrotate(root, gparent);
				temp = parent->col;
				parent->col = gparent->col;
				gparent->col = temp;
			}	
		}else{ // Case B
			uncle = gparent->left;

			// 1
			if(uncle != NIL && uncle->col == RED){
				gparent->col = RED;
				parent->col = BLACK;
				uncle->col = BLACK;
				new = gparent;
			}else{
				// 2
				if(new == parent->left){
					rightrotate(root, parent);
					new = parent;
					parent = new->parent;
				}
				// 3	
				leftrotate(root, gparent);
				temp = parent->col;
				parent->col = gparent->col;
				gparent->col = temp;
			}
		}
	}	
	(*root)->col = BLACK;
}


/*
 * Performs regular BST inseriton with RBTree Fixup
 */
void insert(node **root, int key, char *value){
	// x is the new node that will be inserted
	node *x = makenode(key, value);
	node *y = NULL;
	node *temp = *root;
	// Traverse the tree basing on key comparison 
	// and keeping track of the parent
	while(temp != NIL){
		y = temp;
		if(temp->key > x->key){
			temp = temp->left;
		}else{
			temp = temp->right;
		}
	}
	// At this point root points to a null pointer	
	// This means that y is the last node of the
	// tree and that x will be y's child

	x->parent = y;
	// If y was null, then x is the new root
	if(y == NULL){
		*root = x;
	}else{
		// Otherwise basing on parent's key I choose
		// the node to be the left or right child
		if(y->key > x->key){
			y->left = x;
		}else{
			y->right = x;
		}
	}
	// Need RB Fix
	fixup_insertion(root, x);
}


/*
 * Apply deletion fixup given deleted node
 * replacement x and tree's root
 */
void fixup_delete(node **root, node *n){
	node *parent;
	node *sib;
	while(n != *root && n->col == BLACK){
		parent = n->parent;	
		if (n == parent->left){
			sib = parent->right;
			if(sib->col == RED){
				sib->col = BLACK;
				parent->col = RED;
				leftrotate(root, parent);
			}
			if(sib->left->col == BLACK && sib->right->col == BLACK){
				sib->col = RED;
				n = parent;
				parent = n->parent;
			}else{
				if(sib->right->col == BLACK){
					sib->left->col = BLACK;
					sib->col = RED;
					rightrotate(root, sib);
					sib = parent->right;
				}	
				sib->col = parent->col;
				parent->col = BLACK;
				sib->right->col = BLACK;
				leftrotate(root, parent);
				n = *root;
			}
		}else{
			sib = parent->left;
			if(sib->col == RED){
				sib->col = BLACK;
				parent->col = RED;
				rightrotate(root, parent);
			}
			if(sib->right->col == BLACK && sib->left->col == BLACK){
				sib->col = RED;
				n = parent;
				parent = n->parent;
			}else{
				if(sib->left->col == BLACK){
					sib->right->col = BLACK;
					sib->col = RED;
					leftrotate(root, sib);
					sib = parent->left;
				}	
				sib->col = parent->col;
				parent->col = BLACK;
				sib->left->col = BLACK;
				rightrotate(root, parent);
				n = *root;
			}
		}	
	}
	n->col = BLACK;
}


/*
 * Delete del node and apply fixup
 * to maintain RBTree properties
 */
void delete(node **root, node *del){
	node *y, *x;

	// If the node has at least one null child	
	if(del->left == NIL || del->right == NIL){
		y = del;	// then it's the node to be deleted
	}else{
		// Otherwise it's the successor
		y = successor(del);
	}

	// If the node has a left child, take pointer to the left child
	if(y->left != NIL){
		x = y->left;
	}else{
		// Otherwise take pointer to the right child
		x = y->right;
	}

	x->parent = y->parent;

	if (y->parent == NULL){
		*root = x;
	}else if(y == y->parent->left){
		// If the removed is left child of its parent
		// set x as left child
		y->parent->left = x;
	}else{
		// Otherwise set x as right child
		y->parent->right = x;
	}
	
	if (y != del){
		// If y (removed) differs from the original node
		// copy the content of y to the original node
		// which was requested to be deleted
		del->key = y->key;	
		strcpy(del->value, y->value);
	}

	if (y->col == BLACK){
		// if x color (removed node's color) was black
		// i changed the number of black nodes
		// so i need to apply fixup to maintain
		// RBT properties
		fixup_delete(root, x);
	}

	free(y);
}


/*
 * Free the tree
 */
void freetree(node *root){
	// Uses post order recursive strategy in order
	// to free the subtrees of a node and then the node
	if(root != NIL){
		freetree(root->left);
		freetree(root->right);
		free(root);
	}
}


/*
 * Prints a node in a fancy way
 */
void printnode(node *root){
	if(root == NIL){
		printf("NIL ");
	}else if(root->col == BLACK){
		printf("\033[2m"); 
		printf("[%d:%s] ", root->key, root->value);	
		printf("\033[0m"); 
	}else{
		printf("\033[0;31m"); // red
		printf("[%d:%s] ", root->key, root->value);	
		printf("\033[0m"); 
	}
}


/*
 * Perform inorder visit
 */
void inorder(node *root){
	if(root != NULL){
		inorder(root->left);
		printnode(root);
		inorder(root->right);	
	}
}


/*
 * Perform preorder visit
 */
void preorder(node *root){ 
	if(root != NULL){
		printnode(root);
		preorder(root->left);
		preorder(root->right);
	}
}


/*
 * Perform postorder visit
 */
void postorder(node *root){ 
	if(root != NULL){
		preorder(root->left);
		preorder(root->right);
		printnode(root);
	}
}


/*
 * Format string with no newline char
 */
void format(char *txt){
	char *p = strrchr(txt, '\n');
	if(p != NULL)
		*p = '\0';
}


/*
 * Tokenize input string
 */
int tokenize(char **bufp, char **parsed){
	int count = 0;
	char *token; 

	while((token = strsep(bufp, " ")) != NULL){
		parsed[count] = token;
		format(parsed[count]);
		count++;
	}

	return 1;
}


/*
 * Parse given commands and perform the requested task
 */
int parse_command(node **root, char **parsed){
	if(!strcmp("insert", parsed[0])){        // insert
		insert(root, atoi(parsed[1]), parsed[2]);
	}else if(!strcmp("delete", parsed[0])){  // delete
		node *found = search(*root, atoi(parsed[1]));
		if(!found){
			printf("Node not found\n");
		}else{
			delete(root, found);
		}
	}else if(!strcmp("find", parsed[0])){   // find
		node *found = search(*root, atoi(parsed[1]));
		if(!found){
			printf("Node not found\n");
		}else{
			printf("[ Key %d - Value: %s - ", found->key, found->value);
			if(found->col == BLACK){
				printf("Color: BLACK ]\n");	
			}else{
				printf("Color: RED ]\n");
			}
		}
	}else if(!strcmp("show", parsed[0])){   // show
		preorder(*root);
		printf("\n");
	}else if(!strcmp("exit", parsed[0])){   // exit 
		return 1;	
	}else if(!strcmp("clear", parsed[0])){   // clear
		freetree(*root);
		*root = NIL;
	}else{
		printf("Unkown command\n");
	}
	return 0;
}

int main(){
	// buffer for the input string
	char *cmd = malloc(250*sizeof(char));
	char *bufp;

	// Array that contains cmd and args
	char **parsed = malloc(3*sizeof(char*));

	// Initial root node
	node *root = NIL;

	// Brief tutorial
	printf("Iterative Red Black Tree implementation\n");
	printf("Avaiable commands are:\n");
	printf("\t- insert [key] [value]\n");
	printf("\t- delete [key]\n");
	printf("\t- find [key]\n");
	printf("\t- show\n");
	printf("\t- clear\n");
	printf("\t- exit\n\n");


	while(1){	
		// bufp points to buffer beginning
		bufp = cmd;
		printf("> ");
		fgets(cmd, 250, stdin); // Obtain input from stdin
		
		// Tokenize starting from bufp and place commands
		// inside "parsed" array
		if(!tokenize(&bufp, parsed)){
			printf("Error while obtaining arguments");
			break;
		}	

		// Parse commands, if return value is true 
		// break the loop
		if(parse_command(&root, parsed))
			break;
	}
	
	// Free root and buffer
	free(parsed);
	free(cmd);
	freetree(root);

	return 0;
}
