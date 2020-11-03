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

int64_t* my_sort(int64_t* input, uint64_t size){
	
	if(is_sorted(input, size)){
		return input;
	}
	else{
		int pi = rand() % (size + 1);
		int64_t pivot = input[pi];
		

		int64_t* b = malloc(sizeof(int64_t) * size);

		for(int i = 0; i < size; i++){
			if(input[i] < pivot){
				b[i] = input[i];
			}	
			else{
				b[i+pi] = input[i];
			}
		}
		return input;
	}
}
/*
Suggested function to write, to check whether the array is sorted
Returns 0 if not sorted, returns 1 if sorted
*/
int is_sorted(int64_t* input, uint64_t size){
	for(int i = 0; i < size; i++){
		printf("%" PRId64 "\n", input[i]);
	}
	for(uint64_t i = 0; i < size-1; i++){
		printf("%" PRId64 "\n", input[i]);
		if(input[i] > input[i+1]){
			return 0;
		}
	}
	return 1;
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

	my_sort(input, n);

	//check if it's sorted.
	int sorted = is_sorted(input, n);
	printf("Are the numbers sorted? %s \n", sorted ? "true" : "false");

	printf("Time elapsed: %lf \n", 0.0);
	free(input);
}
