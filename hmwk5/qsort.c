#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

/*
This function returns a pointer to an array with all the numbers in the file as int64_t
Sets *size to be the number of numbers
*/
int64_t* Populate(char* fname, uint64_t* size){
	FILE *file;
	file = fopen(fname, "r");
	char *cap = NULL;
	char *ptr;
	size_t len = 0;
	getline(&cap, &len, file);
	getline(&cap, &len, file);

	int64_t* array = malloc(sizeof(int64_t) * *size);
	
	for(uint64_t i = 0; i < *size; i++){
		getline(&cap, &len, file);
		array[i] = strtoull(cap, &ptr, 10);
	}


	fclose(file);
	return array;
}

int printArray(int64_t* input, uint64_t size){
	printf("\n----------------------------------------------\n");
		for(int i = 0; i < size; i++){
			printf("% " PRId64, input[i]);
		}
	printf("\n----------------------------------------------\n");
	return 0;
}

/*
Suggested function to write, to check whether the array is sorted
Returns 0 if not sorted, returns 1 if sorted
*/
int is_sorted(int64_t* input, uint64_t size){

	for(uint64_t i = 0; i < size-1; i++){
		if(input[i] > input[i+1]){
			return 0;
		}
	}
	return 1;
}

int partition(int64_t* input, int start, int end){
	//printf("start %d end %d\n", start, end);
	//int pi = (rand() % (end - start)) + start; 
	//int64_t pivotPoint = input[pi];
	int64_t pivotPoint = input[end];
	int i = start - 1;
	for(int j = start; j <= end - 1; j++){
		if(input[j] < pivotPoint){
			i++;
			int64_t temp = input[i];
			input[i] = input[j];
			input[j] = temp;
		}
	}
	int64_t temp2 = input[i+1];
	input[i+1] = input[end];
	input[end] = temp2;
	
	return i + 1;	

}

int my_sort(int64_t* input, int start, int end){
	if (start >= end){
		return 0;
	}	
	else{
		int pivotPoint = partition(input, start, end);
		my_sort(input, start, pivotPoint - 1);
		my_sort(input, pivotPoint + 1, end);
	}

	return 0;
}

int main(int argc, char** argv){
	FILE *file;
	file = fopen("./numbers.txt", "r");
	char *cap = NULL;
	char *ptr;
	size_t len = 0;

	getline(&cap, &len, file);
	uint64_t n = strtoull(cap, &ptr, 10); //the input size
	fclose(file);

	int64_t* input = Populate("./numbers.txt", &n); //gets the array
	
	printArray(input, n);
	my_sort(input, 0, n);
	printArray(input, n);

	//check if it's sorted.
	int sorted = is_sorted(input, n);
	printf("Are the numbers sorted? %s \n", sorted ? "true" : "false");

	printf("Time elapsed: %lf \n", 0.0);
	free(input);
}
