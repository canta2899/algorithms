/*
 * Majority Candidate
 * ------------------
 *
 * Given an array, find out if a majority candidate is present. 
 *
 * The majority candidate is the element that appears in the
 * array at least n/2 times where n is the array size.
 *
 * The majority candidate may not exists
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

int find_candidate(int *A, int size){
	int candidate = 0;
	int count = 1;

	for(int i=1; i<size; i++){
		if(count == 0){
			candidate = i;
			count = 1;
		}else{
			if(A[i] == A[candidate]){
				count++;
			}else{
				count--;
			}
		}

	}
	
	return candidate;
}

int *check_candidate(int *A, int size, int candidate){
	int count = 0;
	for(int i=0; i<size; i++){
		if(A[i] == A[candidate]){
			count++;
		}
	}

	if(count > size/2){
		return (A + candidate);
	}else{
		return NULL;
	}
}

int main(){
	int count = 0;
	char input[100];
	char *start = input;
	char *token;
	int *A = malloc(MAXSIZE * sizeof(int));

	printf("Type the array values space separated. (max 30)\n");
	printf("> ");
	fgets(start, 100, stdin);

	while((token = strsep(&start, " \t")) != NULL){
		if(count == MAXSIZE){
			printf("Max array size reached\n");
			break;
		}

		if(*token == 0 || *token == 10)
			continue;

		A[count] = atoi(token);
		count++;
	}

	if(count != MAXSIZE){
		A = realloc(A, count * sizeof(int));
	}

	printf("Array is: [ ");
	for(int i=0; i<count; i++){
		printf("%d ", A[i]);
	}
	printf("]\n");

	int candidate = find_candidate(A, count);
	int *c = check_candidate(A, count, candidate);

	if(!c){
		printf("No majority candidate found\n");
	}else{
		printf("Found majority candidate of value %d\n", *c);
	}

	free(A);

	return 0;
}
