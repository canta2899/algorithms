#include <stdio.h>
#include <time.h>
#include "tools.h"

void FindMinMax(int *A, int size){
	int min=A[0], max=A[0];

	for(int i=1; i < size; i++){
		if (A[i] < min){
			min = A[i];
		}
	
		if (A[i] > max){
			max = A[i];
		}
	}
	printf("Min is: %d\n", min);
	printf("Max is: %d\n", max);
}

int main(int argc, char const *argv[]){
	int size;
	
	// Random array 

	printf("Size: ");
	scanf("%d", &size);
	
	int A[size];
	srand(time(NULL));

	for(int i=0; i < size; i++){
		A[i] = rand() % 100;
	}

	PrintVector(A, size);

	// Finding min and max
	
	FindMinMax(A, size);	
}
