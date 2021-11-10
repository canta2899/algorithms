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
	printf("]\n");
}


/**
 * Selection Sort Algorithm
 */
int *SelectionSort(int *array, int size){
	int temp, min;
	for(int i=0; i<size-1; i++){
		min = i;
		for(int j=i+1; j<size; j++){
			if (array[j] < array[min])
				min = j;
		}

		if (min != i){
			temp = array[min];
			array[min] = array[i];
			array[i] = temp;
		}
	}
	return array;
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

	SelectionSort(array, size);	

	printf("Sorted vector:\n");
	printvector(array, size);
	return 0;
}
