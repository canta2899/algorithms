#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printvector(int *A, int l){
	for(int i=0; i<l; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
}

void Swap(int *A, int i, int j){
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

/*
 Partitions the array taking the higher element
 as the pivot. Because of that, scans the array
 from the first element and the pivot index starts
 from a negative value. 

 At the end the pivot is swapped to its position
 without specific logic. The i index will always
 get at least one increment (when A[q] is confronted
 with A[q], conditions will always be true since
 they are equal).
 */
int Partition(int *A, int p, int q){
	int i = p-1;
	int x = A[q];
	for(int j=p; j<=q; j++){
		if(A[j] <= x){
			i++;
			Swap(A, i, j);
		}
	}
	return i;
}

/*
 Partitions the array taking the lower element
 as the pivot. Works identically to the other
 algorithm except that it swaps before returning

 This happens because at the end i equals to the
 position of the pivot element so you need to
 move the first element to it's pivot position
 by using a swap
 */
int PartitionLowIndex(int *A, int p, int q){
	int i = p;
	int x = A[p];
	for(int j=p+1; j<=q; j++){
		if(A[j] <= x){
			i++;
			Swap(A, i, j);
		}
	}
	Swap(A, p, i);
	return i;
}


/*
	Quick sort algorithm 
 */
void QuickSort(int *A, int p, int q){
	if (p < q){
		int r = PartitionLowIndex(A, p, q);
		// int r = Partition(A, p, q);
		QuickSort(A, p, r-1);
		QuickSort(A, r+1, q);
	}
}


/*
 	Populates an array with random
	values in between 0 and 1000
 */
void BuildRandomArray(int *A, int size){
	srand(time(NULL));
	for(int i=0; i<size; i++){
		A[i] = rand()%1000;
	}
}

int main(){
	int size;
	
	printf("Select array size: ");
	scanf("%d", &size);
	int A[size];
	BuildRandomArray(A, size);
	
	// Some testing 
	printf("The original vector is:\n");
	printvector(A, size);
	printf("\n\n");
	QuickSort(A, 0, size-1);
	printf("QuickSort performed. Sorted array is:\n");
	printvector(A, size);
	return 0;
}
