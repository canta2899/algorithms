/**
 *
 *	•--------------------------•
 *	| HASH TABLE WITH CHAINING |
 *	•--------------------------•
 *
 *	Hash table that resolves conflicts using chaining,
 *	so every position in the table is a linked list. 
 *
 *	If you search for the node given its key, the hash
 *	function computes the position in the table and then
 *	each chained node is traversed in order to find the 
 *	one requested. 
 *
 *	With a good hash function that provides a balanced
 *	tradeoff between table size and number of linked nodes
 *	for each position, all the operations (searching, 
 *	removing, adding a node) require constant time. 
 *
 *	This techinique opposes to open addressing hashing
 *	which is not implemented here
 *
 */

// An interesting thread on double pointers
// https://stackoverflow.com/questions/5580761/why-use-double-indirection-or-why-use-pointers-to-pointers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TSIZE 20  			// table size
#define MAX_VALUE 35 		// max string length

/**
 * Defines the node for a linked list 
 */
typedef struct node{
	int key;
	char value[MAX_VALUE];
	struct node *next;
} *node;


// Hashtable (needs initialization)
node HASHTABLE[TSIZE];


/*
 * Must be called before using the hashtable
 * Initializes every pointer to NULL
 */
void hashtableinit(){
	for(int i=0; i<TSIZE; i++)
		HASHTABLE[i] = NULL;
}


/**
 * Must be called in order to free the hashtable
 * Frees all the linked nodes in the hash table
 */
void hashtablefree(){
	node start;
	node prev;
	for(int i=0; i<TSIZE; i++){
		start = HASHTABLE[i];
		while(start != NULL){
			prev = start;
			start = start->next;
			free(prev);	
		}
	}
}


/**
 * HASH FUNCTION (module TSIZE macro)
 */
int hash_function(int key){
	return key%TSIZE;
}


/**
 * Allocates and builds a new node given key
 * and value
 *
 * Must be deallocated
 */
node mknode(int key, char *value){
	node newnode = malloc(sizeof(struct node));
   	newnode->key = key;
	strcpy(newnode->value, value);
	newnode->next = NULL;
	return newnode;	
}


/**
 * Searches for a node with the given key
 *
 * Returns a pointer to the node if found
 * Otherwise, the pointer points to NULL;
 */
node search(int key){
	int position = hash_function(key);
	node start = HASHTABLE[position];

	while(start != NULL){
		if(start->key == key) return start;
		start = start->next;
	}
	return NULL;
}


/**
 * Inserts new key,value in the Hash Table
 * Allocates a new node from key and value and
 * proceeds to insert it in the table 
 */
void insert(int key, char *value){
	node newnode = mknode(key, value);
	int position = hash_function(key);
	newnode->next = HASHTABLE[position];
	HASHTABLE[position] = newnode;
}


/**
 * If found, removes the node with the given key
 *
 * Returns 1 if the node was removed.
 * Otherwise, returns 0;
 */
int removenode(int key){
 	int position = hash_function(key);
 	node *temp = &HASHTABLE[position];
 
 	while(*temp != NULL && (*temp)->key != key){
 		temp = &((*temp)->next);
 	}
 
 	if (!*temp) return 0;
 	
	// Free the node
 	node tofree = *temp;
 	*temp = (*temp)->next;
 	free(tofree);
 
 	return 1;
 }

/**
 *
 * Displays the actual status of the hash table 
 *
 */
void printwholetable(){
	node start;
	for(int i=0; i<TSIZE; i++){
		printf(" - [%d] ", i);
		start = HASHTABLE[i];	
		while(start != NULL){
			printf("-> {%d, %s} ", start->key, start->value);
			start = start->next;
		}
		printf("\n");
	}
}

/* Some testing */
int main(){
	node found;

	// Hash table must be initialized
	hashtableinit();

	// Insertion 
	insert(3, "three");
	insert(23, "twentythree");
	insert(11, "eleven");
	insert(8, "eight");
	insert(12, "twelve");
	insert(19, "nineteen");
	insert(10, "ten");
	insert(99, "ninetynine");
	insert(854, "eighthundred and fityfour");
	insert(30, "twenty");
	
	printwholetable();

	// Removing some nodes
	if(removenode(854)) printf("Node 854 removed\n");
	if(removenode(23)) printf("Node 19 removed\n");

	// searching for a node 
	if(!(found = search(23)))
		printf("Node 23 not found\n");
	else
		printf("Node 23 found, value is %s\n", found->value);
	
	printwholetable();

	// Table must be freed
	hashtablefree();	
	return 0;
}

