#include "tools.h"

void PrintVector(int *a, int l){
	printf("[ ");
	for(int i=0; i<l; i++){
		printf("%d ", *(a+i));
	}
	printf(" ]\n");
}

int *BuildRandomVector(int size){
	int *A = malloc(size*sizeof(int));
	srand(time(NULL));
	for(int i=0; i < size; i++){
		A[i] = rand()%50;
	}
	return A;
}
