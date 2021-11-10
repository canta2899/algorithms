/*
 * Disjoint sets implemented with trees
 * ------------------------------------
 *
 *  The union operation consists in a union by rank operation
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disjoint_sets_tree.h"


node *makenode(int key, char *value){
	node *new = malloc(sizeof(struct node));
	new->key = key;
	strcpy(new->value, value);
	return new;
}

node *Make(int key, char *value){
	node *new = makenode(key, value);
	new->parent = new;
	new->rank = 0;
	return new;
}

node *Find(node *x){
	if(x != x->parent){
		return Find(x->parent);
	}
	return x;
}

// Path compression
node *FindPC(node *x){
	if(x != x->parent){
		x->parent = FindPC(x->parent);
	}
	return x;
}

void Link(node *z, node *w){
	w->parent = z;
}

// Union by rank
node *Union(node *x, node *y){
	node *z = Find(x);
	node *w = Find(y);
	if(z != w){
		if(z->rank > w->rank){
			Link(z, w);
			return z;
		}else{
			Link(w, z);
			if(z->rank == w->rank){
				w->rank++;
			}
			return w;
		}
	}
	return NULL;
}

int main(){
	node *s1 = Make(1, "one");
	node *s2 = Make(2, "two");
	node *s3 = Make(3, "three");
	node *s4 = Make(4, "four");
	node *su;

	su = Union(s1, s2);
	su = Union(su, s3);
	su = Union(su, s4);

	node *found = Find(s1);
	printf("Node s1 is in set of key %d and value %s\n", found->key, found->value);
	found = Find(s2);
	printf("Node s2 is in set of key %d and value %s\n", found->key, found->value);
	found = Find(s3);
	printf("Node s3 is in set of key %d and value %s\n", found->key, found->value);
	found = Find(s4);
	printf("Node s4 is in set of key %d and value %s\n", found->key, found->value);
	
	printf("s1 has rank %d\n", s1->rank);
	printf("s2 has rank %d\n", s2->rank);
	printf("s3 has rank %d\n", s3->rank);
	printf("s4 has rank %d\n", s4->rank);

	free(s1);
	free(s2);
	free(s3);
	free(s4);
	return 0;
}
