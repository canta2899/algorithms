#include "mergesort.h"
/*
   Merge procedure
   
   Takes: Array, left, center, right
   Precondition: Array is sorted from p to r and from r+1 to q
   Postcondition: Array is sorted from p to q
 */
void Merge(int *A, int p, int r, int q){
	int *B = malloc((q-p+1)*sizeof(int));
	int k = 0;
	int i = p;
	int j = r+1;
	
	while(i <= r && j <= q) {
		if(A[i] < A[j]){
			B[k] = A[i];
			i++;
		}else{
			B[k] = A[j];
			j++;
		}
		k++;
	}

	while(i <= r){
		B[k] = A[i];
		i++;
		k++;
	}

	while(j <= q){
		B[k] = A[j];
		j++;
		k++;
	}

	for(int a=p; a<=q; a++){
		A[a] = B[a-p];
	}
	free(B);	
}


/*
  MergeSort algorithm (relies on Merge procedure)
  Recursively sorts the two halfs of the array
  And later on merges them to become fully sorted
 */
void MergeSort(int *A, int p, int q){
	if (p < q) {
		int r = (p+q)/2;
		MergeSort(A, p, r);
		MergeSort(A, r+1, q);	
		Merge(A, p, r, q);
	}
}


/*
	int main(){
		int size;

		printf("Select size: ");
		scanf("%d", &size);
		int array[size];
		srand(time(NULL));
		for(int i=0; i < size; i++){
			array[i] = abs(rand());
		}

		printf("Original vector:\n");
		PrintVector(array, size);

		MergeSort(array,0, size-1);	

		printf("Sorted vector:\n");
		PrintVector(array, size);
		return 0;
	}
*/
