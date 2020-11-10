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
	printf("\n-----------------------------------------------------\n");
	for(int i = 0; i < size; i++){
		printf("% " PRId64 , input[i]);
	}
	printf("\n-----------------------------------------------------\n");
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

int merge(int64_t* input, int start, int midPoint, int end){

	printf("partition %d %d %d\n", start, midPoint, end);
	int64_t* partitions = malloc(sizeof(int64_t) * (end - start + 1));	

	//printArray(input, end - start + 1);

	int p1_count = start;
	int p1_threshold = midPoint;

	int p2_count = midPoint + 1;
	int p2_threshold = end;

	int input_count = 0;


	while(p1_count <= p1_threshold && p2_count <= p2_threshold){
		if(input[p1_count] < input[p2_count]){
			partitions[input_count] = input[p1_count];
			input_count++;
			p1_count++;
		}
		else{
			partitions[input_count] = input[p2_count];
			input_count++;
			p2_count++;
		}
	}

	while(p1_count <= p1_threshold){
		partitions[input_count] = input[p1_count];
		input_count++;
		p1_count++;
	}

	while(p2_count <= p2_threshold){
		partitions[input_count] = input[p2_count];
		input_count++;
		p2_count++;
	}

	for(int i = start; i <= end; i++){
		input[i] = partitions[i - start];
	}

	free(partitions);

	return 0;
}

int my_sort(int64_t* input, uint64_t start, uint64_t end){
	if(start < end){
		int midPoint = (end - start)/2;
		my_sort(input, start, midPoint);
		my_sort(input, midPoint+1, end);
		merge(input, start, midPoint, end);

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
	
	
	my_sort(input, 0, n-1);
	printf("n-1 \n");
	printArray(input, n);	

	my_sort(input, 0, n);
	printf("n \n");
	printArray(input, n);	

	//check if it's sorted.
	int sorted = is_sorted(input, n);
	printf("Are the numbers sorted? %s \n", sorted ? "true" : "false");

	printf("Time elapsed: %lf \n", 0.0);
	free(input);
}
