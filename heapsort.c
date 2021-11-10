#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEFT(i) (2*i) 		// left child of a node
#define RIGHT(i) (2*i + 1)	// right child of a node

void Swap(int A[], int a, int b){
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

/*
 * Heapify with no recursive call.
 * Using a while loop, the heapify algorithm
 * becomes in place other than theta(n)
 */
void Heapify(int A[], int i, int length){
	int l, r, m;
	while (1){
		l = LEFT(i);
		r = RIGHT(i);
		if (l < length && A[l] > A[i]){
			m = l;	
		}else{
			m = i;
		}

		if (r < length && A[r] > A[m]){
			m = r;
		}

		if (m != i){
			Swap(A, i, m);
			i = m;
		}else{
			break;
		}
	}
}

/**
 * Builds a Max Heap from a given array
 * pointer by applying Heapify to every
 * non leaf node
 */
void BuildHeap(int *A, int length){
    int i=length/2-1;
    for(;i>=0; i--){
        Heapify(A, i, length);
    }
}

/*
 * Heap sort algorithm. Applies BuildHeap
 * first, then Swaps the first element
 * with the last one and re-build the heap
 * (after the heapsize has been reduces). 
 *
 * Everytime the higher value element is
 * swapped so the algorithm ends with the
 * vector sorted
 */
void HeapSort(int *A, int length){
    BuildHeap(A, length);
    for(int i=length-1; i>0; i--){
        Swap(A, 0, i);
        Heapify(A, 0, i);
    }
}


int main(){
	int size;
	printf("Provide size for the array: ");
	scanf("%d", &size);
	int A[size];
	srand(time(NULL));
	for(int i=0; i<size; i++){
		A[i] = rand()%200;	
	}
    HeapSort(A, size);
    printf("Sorted array is: ");
    for(int i=0; i<size; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
