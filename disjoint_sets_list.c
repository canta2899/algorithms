/*
 *
 * Disjoints Sets
 * --------------
 *
 * Implementation with linked list
 * and weighted union
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/disjoint_sets_list.h"

node *makenode(int key, char *value){
	node *new = malloc(sizeof(struct node));
	new->key = key;
	strcpy(new->value, value);
	return new;
}

node *Make(int key, char *value){
	node *x = makenode(key, value);
	x->rep = x;
	x->next = NULL;
	x->last = x;
	x->len = 1;
	return x;
}

node *Find(node *x){
	return x->rep;
}

void Link(node *z, node *w){
	z->last->next = w;
	z->last = w->last;
	z->len += w->len;
	while(w != NULL){
		w->rep = z;
		w = w->next;
	}	
}

node *Union(node *x, node *y){
	node *z = Find(x);
	node *w = Find(y);
	if(z != w){
		if(z->len > w->len){
			Link(z, w);
			return z;
		}else{
			Link(w, z);
			return w;
		}
	}
	return NULL;
}

void freeset(node *n){
	if(n->rep == n){
		node *tofree;
		while(n != NULL){
			tofree = n;
			n = n->next;
			free(tofree);	
		}
	}
}

int main(){
	
	// Making four sets
	node *s1 = Make(1, "one");
	node *s2 = Make(2, "two");
	node *s3 = Make(3, "three");
	node *s4 = Make(4, "four");
	node *found;

	found = Find(s2);
	printf("Node s2 is part of set of rep [%d:%s]\n", found->key, found->value); 
	found = Find(s4);
	printf("Node s4 is part of set of rep [%d:%s]\n", found->key, found->value); 

	Union(s1, s2);
	Union(s3, s4);

	found = Find(s2);
	printf("Node s2 is part of set of rep [%d:%s]\n", found->key, found->value); 
	found = Find(s4);
	printf("Node s4 is part of set of rep [%d:%s]\n", found->key, found->value); 

	Union(s1, s4);
	found = Find(s2);
	printf("Node s2 is part of set of rep [%d:%s]\n", found->key, found->value); 
	found = Find(s4);
	printf("Node s4 is part of set of rep [%d:%s]\n", found->key, found->value); 

	freeset(s1);
	freeset(s2);
	freeset(s3);
	freeset(s4);

}
