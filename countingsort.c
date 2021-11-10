#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void printactual(int *A, int l){
	printf("Actual:\n");
	for(int i=0; i<l; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
}

void CountingSort(int *A, int l, int *B, int k){
	int C[k+1];

	// Initialize C to 0s
	for(int i=0; i<=k; i++){
		C[i] = 0;
	}

	// Adds the occourence of every element in A
	// inside the counting vector
	for(int i=0; i<l; i++){
		C[A[i]]++;
	}	

	// Adding the occourences of previous cells
	// in each counter's cell
	for(int i=1; i<=k; i++){
		C[i] += C[i-1];
	}

	// Assigning values to B sorted
	// For each value in A we know that C[A[i]] represents
	// the number of cells before A[i] in the sorted vector
	// So we place the value of A[i] in B[ C[ A[i] ] - 1 ] and
	// we decrease the respective counter by 1
	for(int i=l-1; i>=0; i--){
		// note: -1 because if C[A[i]] says 5 because the element is
		// in the 5th position, then we place it in the 4th position
		// because we need to consider 0th position too
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}
}

int searchMax(int *A, int l){
	int max = A[0];
	for(int i=1; i<l; i++)
		if(A[i] > max)
			max = A[i];
	return max;
}

int main(){
	srand(time(NULL));		
	int size;
	printf("Provide vector size: ");
	scanf("%d", &size);
	
	int A[size];
	int B[size];

	for(int i=0; i<size; i++)
		A[i] = rand()%100;

	int max = searchMax(A, size);
	
	CountingSort(A, size, B, max); 
	
	printf("Sorted vector is:\n");
	for(int i=0; i<size; i++){
		printf("%d ", B[i]);
	}
	printf("\n");
}
