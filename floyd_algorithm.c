/*
 * Implementation of the Floyd's algorithm
 * known as the 'tortoise and hare' algorithm. 
 *
 * By using two pointers, allows to detect
 * cycles in a linked list with linear time
 * complexity and constant space complexity
 *
 */


#include <stdio.h>

struct node{
	int value;
	struct node *next;
};

typedef struct node node;

node *detect_cycle(node *head){
	// Initializes both pointers to the head node
	node *tortoise = head;
	node *hare = head;

	// Moves pointers if hare's next or next-next nodes
	while(hare->next != NULL && hare->next->next != NULL){
		// increases pointers accordingly
		tortoise = tortoise->next;
		hare = hare->next->next;

		// if pointers are equal a cycle has been found
		if (tortoise == hare){

			// Reposition the tortoise at the beginning
			tortoise = head;
			
			// Move hare and tortoise until they're equal
			while(tortoise != hare){
				tortoise = tortoise->next;
				hare = hare->next;
			}

			// When they're equal i found the point where
			// the cycle happens
			return hare;
		}	
	}

	// This means hare arrived ad the end
	// So no cycle is detected
	return NULL;
}

void insert(node *root, node *newnode){
	while(root->next != NULL){
		root = root->next;
	}

	root->next = newnode;
}

int main(){
	node nn1, nn2, nn3, nn4, nn5, nn6;

	node *n1 = &nn1;	
	n1->value = 1;
	n1->next = NULL;

	node *n2 = &nn2;
	n2->value = 2;
	n2->next = NULL;

	node *n3 = &nn3;
	n3->value = 3;
	n3->next = NULL;

	node *n4 = &nn4;
	n4->value = 4;
	n4->next = NULL;

	node *n5 = &nn5;
	n5->value = 5;
	n5->next = NULL;

	node *n6 = &nn6;
	n6->value = 6;
	n6->next = n2;

	insert(n1, n2);
	insert(n1, n3);
	insert(n1, n4);
	insert(n1, n5);
	insert(n1, n6);

	node *cycle = detect_cycle(n1);

	if(!cycle){
		printf("No cycle found\n");
	}else{
		printf("A cycle was found, involving the node %d\n", cycle->value);
	}
	return 0;
}
