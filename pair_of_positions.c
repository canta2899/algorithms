#include <stdio.h>
#include "mergesort.h"
#include "tools.h"

/**
 * Given an array A of length N and given an integer K
 * find two elements of A (x and y) whose sum is k.
 *
 * Solution has to be O(nlogn) and the algorithm must return
 * the position of the two elements or NULL otherwise
 */


// Algorithm
int *FindPair(int *A, int size, int k){

	// MergeSort takes O(nlogn)
	MergeSort(A, 0, size-1);

	int l = 0;
	int r = size-1;

	// Worst case n-1 times so it's O(n)
	while (l < r){
		if (A[l] + A[r] == k){
			int *result = malloc(2*sizeof(int));
			result[0] = l;
			result[1] = r;		
			return result;
		}else if (A[l] + A[r] < k){
			l++;
		}else{
			r--;
		}	
	}
	
	/*
	 * Recursive version?
	 * ------------------
	 *
	 * Recursive version can be implemented by using a procedure
	 * which admits left and right parameters. The recursive call
	 * may happen on Procedure(A, l+1, r) or Procedure(A, l, r-1)
	 *
	 * That wouldn't be in place though
	 */
	
	// Considering O(nlogn) for MergeSort and O(n) for the rest
	// The algorithm is then O(nlogn)
	return NULL;
}

int main(){
	int size;
	int k;

	printf("Select size: ");
	scanf("%d", &size);
	printf("Choose K: ");
	scanf("%d", &k);

	int *A = BuildRandomVector(size);

	printf("Vector is: \n");
	PrintVector(A, size);

	int *pair = FindPair(A, size, k);

	if (!pair){
		printf("No pair found\n");
	}else{
		printf("Value 1: %d\n", A[pair[0]]);
		printf("Value 2: %d\n", A[pair[1]]);
	}

	free(pair);
	free(A);
	return 0;
}
