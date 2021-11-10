#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * Prints vector to stout
 */
void printvector(int *a, int l){
	printf("[ ");
	for(int i=0; i<l; i++){
		printf("%d ", *(a+i));
	}
	printf(" ]\n");
}


/**
 * MinSearch function (linear complexity) 
 */
int MinSearch(int *A, int k, int h){
	int min = A[k];
	int min_pos = k;
	for(int i=k+1; i < h; i++){
		if (A[i] < min) {
			min = A[i];
			min_pos = i;
		}
	}
	return min_pos;
}


/**
 * Swap function (constant complexity)
 */
void Swap(int *A, int k, int h){
	int temp = A[k];
	A[k] = A[h];
	A[h] = temp;
}

/**
 * Selection Sort Algorith - Recursive Version
 */
void SelectionSort(int *A, int size, int p){
	int i;
	if (p < size-1){ // theta(1) 
		i = MinSearch(A, p, size); // theta(n)
		Swap(A, i, p);				// theta(1)
		SelectionSort(A, size, p+1);  // theta(n-1)
	}

	/**
	 *		  | theta(1) [a]    if n = 1
	 * T(n) = |
	 *		  | T(n-1) + theta(n) [b]    if n > 1
	 */
}

int main(){
	int size;

	printf("Select size: ");
	scanf("%d", &size);
	int array[size];
	srand(time(NULL));
	for(int i=0; i < size; i++){
		array[i] = rand()%50;
	}

	printf("Original vector:\n");
	printvector(array, size);

	SelectionSort(array, size, 0);	

	printf("Sorted vector:\n");
	printvector(array, size);
	return 0;
}
