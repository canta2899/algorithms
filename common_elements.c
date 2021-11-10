#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Let A and B be two sorted vectors of length n and m
 *	
 * Find the common elements of A and B:
 *
 * 	0. Naive --> theta(m*n) [doesn't suppose vector are already sorted]
 * 	1. Modified Merge --> theta(n+m)
 * 	2. Binary Search --> search every element of B in A O(mlogn)
 *
 */
int min(int a, int b){
	if (a<b)
		return a;
	else
		return b;
}

int *FindCommon(int *A, int *B, int sizeA, int sizeB){
	int *C = (int*)malloc(min(sizeA, sizeB)*sizeof(int));
	int i = 0;
	int r = sizeA-1;
	int j = 0;
	int q = sizeB-1;
	int cindex = 0;
	while(i <= r && j <= q) {
		if(A[i] < B[j]){
			i++;
		}else{
			if (A[i] == B[j]){
				C[cindex] = A[i];
				cindex++;
			}
			j++;
		}
	}
	C[cindex] = -1;
	return C;
}

// theta(sizeA+sizeB)
void ModifiedMergeSolution(){
	int A[] = {1,2,3,4,5,6};
	int sizeA = sizeof(A)/sizeof(int);

	int B[] = {2,5,17};
	int sizeB = sizeof(B)/sizeof(int);

	int *common = FindCommon(A, B, sizeA, sizeB);
	int *tofree = common;
	
	printf("Common values are: ");
	while(*common != -1){
		printf("%d ", *common);
		++common;
	}	
	printf("\n");
	free(tofree);
}

int *BinarySearch(int *A, int p, int q, int s){
	if (p > q)
		return NULL;
	int mid = (p+q)/2;	
	if(A[mid] == s)
		return &(A[mid]);
	else if(A[mid] > s)
		return BinarySearch(A, p, mid-1, s);
	else
		return BinarySearch(A, mid+1, q, s);			

}

int *FindCommonBS(int *A, int *B, int sizeA, int sizeB){
	int *common = (int*)malloc(min(sizeA, sizeB)*sizeof(int));
	int *toret = common;
	int *item;
	for(int i=0; i<sizeA; i++){
		item = BinarySearch(B, 0, sizeB-1, A[i]);
		if(!item){
		}else{
			*common = *item;
			common++;
		}
	}	
	*common = -1;
	return toret;
}

// Takes theta(sizeA) * O(logsizeB) so it's O(sizeA*logsizeB)
void BinarySearchSolution(){
	int A[] = {1,2,3,4,5,6,82,900,1002};
	int sizeA = sizeof(A)/sizeof(int);

	int B[] = {2,5,17,82,1002};
	int sizeB = sizeof(B)/sizeof(int);
	
	int *common = FindCommonBS(A, B, sizeA, sizeB);
	int *tofree = common;
	printf("Common values are: ");
	while(*common != -1){
		printf("%d ", *common);
		common++;
	}	
	printf("\n");
	free(tofree);
}

int main(){
	// ModifiedMergeSolution();
	BinarySearchSolution();
	return 0;
}
