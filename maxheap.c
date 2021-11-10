/**
 *	Implementation of a MaxHeap that allows to execute interactively 
 * 	the following operations: 
 * 
 *	   - Insert
 *	   - Delete
 *	   - Extract
 *     - Clear
 * 	   - Modifify
 * 	   - Visit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define LEFT(i) (2*i)
#define RIGHT(i) (2*i + 1)
#define PARENT(i) (i/2)

struct MaxHeap {
	int *heap;
	int heapsize;
    int maxsize;
};

void Swap(struct MaxHeap *H, int i, int parent){
	int temp = H->heap[i];
	H->heap[i] = H->heap[parent];
	H->heap[parent] = temp;
}

/*
 * Inserts a new element k inside the heap
 * Returns 0 if the insertion was succesful
 * Returns -1 if the insertion couldn't happen
 * because of max heap size reached
 */
int MaxHeapInsert(struct MaxHeap *H, int k){
	int i;
	if(H->heapsize < H->maxsize){
		H->heapsize++;
		H->heap[H->heapsize-1] = k;
		i = H->heapsize-1;
		while(i > 0 && H->heap[i] > H->heap[PARENT(i)]){
			Swap(H, i, PARENT(i));
			i = PARENT(i);	
		}
		return 0;
	}else{
		return -1;
	}		
}

/*
 * Recursive Heapify Algorithm, not in place.
 * Ensures that, from the i-th position, the
 * array contains a max-heap. Otherwise, swaps
 * the nodes that need to be swapped. 
 *
 * At the end of the execution, the array is a 
 * MaxHeap
 */
void Heapify(struct MaxHeap *H, int i){
	int l, r, m;
	l = LEFT(i);
	r = RIGHT(i);
	if (l < H->heapsize && H->heap[l] > H->heap[i]){
		m = l;	
	}else{
		m = i;
	}

	if (r < H->heapsize && H->heap[r] > H->heap[m]){
		m = r;
	}

	if (m != i){
		Swap(H, i, m);
		Heapify(H, m);
	}
}

/*
 * Extract the highest element from the
 * max-heap and re-applies heapify in order
 * to mantain the heap structure. 
 */
int MaxHeapExtract(struct MaxHeap *H){
	if (H->heapsize > 0){
		Swap(H, 0, H->heapsize-1);
		H->heapsize--;
		Heapify(H, 0);
		return H->heap[H->heapsize];
	}else{
		return -1;
	}
}

/*
 * Prints the heap to stdout
 */
void printheap(struct MaxHeap *H){
	printf("Heap is the following\n");
	for(int i=0; i < H->heapsize; i++){
		printf("%d ", H->heap[i]);
	}
	printf("\n");
}

/*
 * Modify the value of the i-th node adding
 * the value s. The re-applies heapify for
 * each note before the i-th one including
 * the root node in order to mantain heap structure
 */
void MaxHeapModify(struct MaxHeap *H, int i, int s){
	H->heap[i] += s;
	for(;i>=0;i--){
		Heapify(H, i);
	}
}

/*
 *	Sigint signal handler (allows exiting with C-c)
 */
void handler(int num){
	printf("Closing...\n");
	exit(0);
}

/*
 * Allocates a maxheap with the given array of values, 
 * given size and given maximum size
 *
 * Returns a pointer to the maxheap that needs to be
 * deallocated in future
 */
struct MaxHeap *getmaxheap(int *A, size_t size, int maxsize){
	int length = size / sizeof(int);
    struct MaxHeap *H = malloc(sizeof(struct MaxHeap));
	H->heap = malloc(size);
    memcpy(H->heap, A, size);
    H->heapsize = length;
	if (maxsize < 0){
		H->maxsize = length;
	}else{
    	H->maxsize = maxsize;
	}
	return H;
}


/*
 * Allocates an empty maxheap given it's max size 
 */
struct MaxHeap *getmaxheapempty(int maxsize){
    struct MaxHeap *H = malloc(sizeof(struct MaxHeap));
	H->heap = calloc(maxsize, sizeof(int));
    H->heapsize = 0;
    H->maxsize = maxsize;
    return H;
}

/*
 * Deallocates the MaxHeap pointed by H
 */
void freemaxheap(struct MaxHeap *H){
	free(H->heap);
	free(H);
}
