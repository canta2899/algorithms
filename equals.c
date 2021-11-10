#include <stdio.h>
#include "mergesort.h"


/**
 * Sorts the array and searches for equal elements
 * Complexity is O(nlogn) because:
 * 	- MergeSort takes O(nlogn)
 * 	- Scanning the sorted array takes O(n) worst case
 */

int FindEquals(int *A, int size){
	// Takes O(nlogn) with O(n) space
	MergeSort(A, 0, size-1);

	// Takes O(n) worst case\
	for(int i=0; i < size-1; i++){
		if (A[i] == A[i+1]){
			return 1;
		}
	}
	return 0;
}


int main(){
	int A[] = {10,1,6,2,14,92,81,12,0};
	size_t size = sizeof(A)/sizeof(int);
	if (FindEquals(A, size)){
		printf("There are equal elements\n");
	}else{
		printf("There are no equal elements\n");
	}
	return 0;
}

/*
 	NOTE
	----
One can prove that worst-case every algorithm that solves this problem has
Omega(nlogn) complexity. It can't take less time than the required for a sorting
procedure

*/

