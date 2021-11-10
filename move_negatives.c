#include <stdio.h>
#include <time.h>
#define N 40

/**
 *	Given e vector A that contains n positive integers and n negative integers
 *	modify A in order to let the n negative integers occupy the first n 
 *	positions
 *
 *	The algorithm must be theta(n) and in place
 */

void Swap(int *A, int a, int b){
	int temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}

void MoveNegatives(int *A, int size){
	int swapindex = 0;
	for(int i=0; i<size; i++){
		if(A[i] < 0){
			Swap(A, swapindex, i);
			swapindex++;
		}	
	}
}

int main(){
	srand(time(NULL));
	int size = N*2;	
	int A[size];
	int i=0;
	for(; i<size/2; i++){
		A[i] = rand()%100 * -1;
	}
	
	for(; i<size; i++){
		A[i] = rand()%100;
	}

	MoveNegatives(A, size);
	
	printf("Now the vector is: \n");
	for(int value:A){
		printf("%d ", value);
	}
	printf("\n");
	return 0;
}
