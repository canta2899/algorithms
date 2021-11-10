/*
 *	Binary Search Trees
 *	-------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "include/stack.h"
#include "binary_search_tree.h"


node *makenode(int key, char *value){
	node *newnode = malloc(sizeof(node));
	newnode->key = key;
	strcpy(newnode->value, value);
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
	return newnode;
}

node *findmax(node *root){
	while(root->right != NULL){
		root = root->right;	
	}
	return root;
}

node *findmin(node *root){
	while(root->left != NULL){
		root = root->left;
	}
	return root;
}

node *search(node *root, int key){
	while(root != NULL){
		if(root->key == key)
			return root;
		else if(root->key > key)
			root = root->left;
		else
			root = root->right;
	}
	return root;
}

node *successor(node *n){
	if(n != NULL){
		if(n->right != NULL){
			return findmin(n->right);
		}else{
			node *temp = n->parent;
			while(temp != NULL && n == temp->right){
				n = temp;
				temp = temp->parent;
			}
			return temp;
		}
	}else{
		return NULL;
	}
}

node *predecessor(node *n){
	if(n != NULL){
		if(n->left != NULL){
			return findmax(n->left);
		}else{
			node *temp = n->parent;
			while(temp != NULL && n == temp->left){
				n = temp;
				temp = temp->parent;
			}
			return temp;
		}
	}else{
		return NULL;
	}	
}

void insert(node **root, int key, char *value){
	// x is the new node that will be inserted
	node *x = makenode(key, value);
	node *y = NULL;
	node *temp = *root;

	// Traverse the tree basing on key comparison 
	// and keeping track of the parent
	while(temp != NULL){
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
	if(!y){
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
}

void delete(node **root, node *del){
	node *x, *y, *v;

	if(!del->left || !del->right){
		// Case 1/2 (del has 0 or 1 children)
		// so node del will be removed
		y = del;
	}else{
		// Case 3 (del has 2 children)
		// so del's successor will replace
		// del (that will be removed)
		y = successor(del);
	}

	// x will be left or right child of the node 
	// that will be removed
	if(y->left != NULL){
		// left child if present
		x = y->left;
	}else{
		// otherwise right child
		x = y->right;
	}

	// If x is actually a child node of the one to be removed
	// (so it's not null), i have to relink it's parent to the
	// corrent one, which is the parent of the node to be removed
	if(x != NULL){
		x->parent = y->parent;
	}

	// If y's parent is NULL this means that y is a root, so
	// I just have to replace the actual root with x
	if(!y->parent){
		*root = x;
	}else{
		// Otherwise x will be y's parent left child
		// if x was y's parent left child
		if(y == y->parent->left){
			y->parent->left = x;
		}else{
			// right child otherwise
			y->parent->right = x;
		}
	}

	// Now I've linked children and parent of the node 
	// And i can finally get rid of it

	// If it's case 1 or case2 I can just free the node
	// If it's case 3 I have to move the node to the position
	// of the one that I'm about to remove
	if(y != del){
		// in case 3 the content of the node is copied to
		// the positiono of the node that will be removed
		del->key = y->key;
		strcpy(del->value, y->value);
	}

	// Now it's safe to free the removed node. If it was case
	// 1 or case 2 I'd have simply remove any link to that node
	// and freed the memory. If it was case 3, I would have erased
	// the content of the node, copied the content of the successor
	// in it, and then freed the successor in its original position
	free(y);
}

void freetree(node *root){
	// Uses post order recursive strategy in order
	// to free the subtrees of a node and then the node
	if(root != NULL){
		freetree(root->left);
		freetree(root->right);
		free(root);
	}
}

// In order visit
void inorder(node *root){
	if(root != NULL){
		inorder(root->left);
		printf("[%d:%s] ", root->key, root->value);
		inorder(root->right);	
	}else{
		printf("NULL ");
	}
}

// void inorder_it(node *root, int nulls){
// 	struct Stack *s = initstack(-1);
// 	node *temp = root;
// 	while(!isempty(s) || temp != NULL){
// 		if (temp != NULL){
// 			push(s, temp);
// 			temp = temp->left;
// 		}else{
// 			temp = pop(s);
// 			printf("[%d:%s] ", temp->key, temp->value);
// 			temp = temp->right;
// 		}
// 	}	
// 	freestack(s);
// }


void preorder(node *root){
	if(root != NULL){
		printf("[%d:%s] ", root->key, root->value);
		preorder(root->left);
		preorder(root->right);
	}else{
		printf("NULL ");
	}
}

// void preorder_it(node *root, int nulls){
// 	struct Stack *s = initstack(STACKSIZE);
// 	node *temp = root;
// 	push(s, temp);
// 	while(!isempty(s)){
// 		temp = pop(s);
// 		printf("[%d:%s] ", temp->key, temp->value);
// 		if(temp->right != NULL)
// 			push(s, temp->right);
// 		if(temp->left != NULL)
// 			push(s, temp->left);
// 	}	
// 	freestack(s);
// }

// Postorder visit
void postorder(node *root){
	if(root != NULL){
		postorder(root->left);
		postorder(root->right);
		printf("[%d:%s] ", root->key, root->value);
	}else{
		printf("NULL ");
	}
}

// void postorder_it(node *root, int nulls){
// 	struct Stack *s = initstack(STACKSIZE);
// 	struct Stack *o = initstack(STACKSIZE);
// 	node *temp;
// 	push(s, root);
// 	while(!isempty(s)){
// 		temp = pop(s);
// 		push(o, temp);
// 		if(temp->left != NULL)
// 			push(s, temp->left);
// 		if(temp->right != NULL)
// 			push(s, temp->right);
// 	}	
// 	while(!isempty(o)){
// 		temp = pop(o);
// 		printf("[%d:%s] ", temp->key, temp->value);
// 	}
// 	freestack(o);
// 	freestack(s);
// }

void format(char *txt, size_t len){
	char *p = strrchr(txt, '\n');
	if(p != NULL)
		*p = '\0';
}

int tokenize(char **bufp, char **parsed){
	int count = 0;
	char *token; 

	while((token = strsep(bufp, " ")) != NULL){
		parsed[count] = token;
		format(parsed[count], strlen(parsed[count]));
		count++;
	}

	return 1;
}

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
			printf("[ Key %d - Value: %s]\n", found->key, found->value);
		}
	}else if(!strcmp("show", parsed[0])){   // show
		preorder(*root);
		printf("\n");
	}else if(!strcmp("exit", parsed[0])){   // exit 
		return 1;	
	}else if(!strcmp("clear", parsed[0])){   // clear
		freetree(*root);
		*root = NULL;
	}else{	// unkown 
		printf("Unkown command\n");
	}
	return 0;
}

int main(){
	char *cmd = malloc(250*sizeof(char));
	char *bufp;
	char **parsed = malloc(3*sizeof(char*));
	node *root;

	printf("Iterative binary search tree implementation\n");
	printf("Avaiable commands are:\n");
	printf("\t- insert [key] [value]\n");
	printf("\t- delete [key]\n");
	printf("\t- find [key]\n");
	printf("\t- show\n");
	printf("\t- clear\n");
	printf("\t- exit\n\n");

	while(1){	
		bufp = cmd;
		printf("> ");
		fgets(cmd, 250, stdin); // Obtain input from stdin
		
		if(!tokenize(&bufp, parsed)){
			printf("Error while obtaining arguments");
			break;
		}	

		if(parse_command(&root, parsed))
			break;
	}
	
	free(parsed);
	free(cmd);
	freetree(root);

	return 0;
}
