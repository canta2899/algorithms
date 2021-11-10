#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printvector(int *a, int l){
	printf("[ ");
	for(int i=0; i<l; i++){
		printf("%d ", *(a+i));
	}
	printf(" ]\n");
}

/*
   Insertion sort algorithm scans the array
   and, for each element (except first one)
   loops back down to the beginning until it
   finds smaller elements shifting the array
   everytime. At the end moves the pointed 
   element to the stop position and proceeds
   to the same thing for the next element
*/
void InsertionSort(int A[], int l){
	int key, previous;
	for(int i=1; i<l; i++){
		key = A[i];
		previous = i-1;
		while (previous >= 0 && A[previous] > key) {
			A[previous+1] = A[previous];
			previous--;
		}
		A[previous+1] = key;
	}
}

int main(){
	int size;

	printf("Select size: ");
	scanf("%d", &size);
	int array[size];
	
	// Generates random vector
	srand(time(NULL));
	for(int i=0; i < size; i++){
		array[i] = rand()%50;
	}

	printf("Original vector:\n");
	printvector(array, size);

	InsertionSort(array, size);	

	printf("Sorted vector:\n");
	printvector(array, size);
	return 0;
}

/*

			start
		 	-----

   First iteration
   ---------------

   | 4 | 2 | 6 | 1 | 8 | 9 |
   	 p   ^

   | 4 | 4 | 6 | 1 | 8 | 9 |  step1
   | 2 | 4 | 6 | 1 | 8 | 9 |  step2


   Second iteration
   ----------------
   | 4 | 2 | 6 | 1 | 8 | 9 |
   		 p   ^

   Third iteration
   ---------------

   | 4 | 2 | 6 | 1 | 8 | 9 |
   		 	 p   ^

   | 4 | 2 | 6 | 1 | 8 | 9 | step1
   | 4 | 2 | 6 | 6 | 8 | 9 | step2
   | 4 | 2 | 2 | 6 | 8 | 9 | step3
   | 4 | 4 | 2 | 6 | 8 | 9 | step4
   | 1 | 4 | 2 | 6 | 8 | 9 | step5


   Fourth iteration
   ---------------

   | 4 | 2 | 6 | 1 | 8 | 9 |
   		 	 	 p   ^


   Fifth iteration
   ---------------

   | 4 | 2 | 6 | 1 | 8 | 9 |
   		 	 		 p   ^

		    end
			---

*/
