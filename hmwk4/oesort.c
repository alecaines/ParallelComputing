#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>

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

	int64_t* array = malloc(sizeof(int64_t) * *size);
	
	for(uint64_t i = 0; i < *size; i++){
		if(i > 3){
			getline(&cap, &len, file);
			array[i] = strtoull(cap, &ptr, 10);
		}
		else{
			getline(&cap, &len, file);
		}
	}

	fclose(file);
	return array;
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

int64_t* my_sort(int64_t* input, uint64_t size){
		for(uint64_t j = 0; j < size - 1; j++){
			//#pragma omp parallel for
			#pragma omp parallel
			for(uint64_t i = j%2; i < size - 1; i+=2){
				if(input[i] > input[i+1]){
					int64_t mid = input[i+1];
					input[i+1] = input[i];
					input[i] = mid;
				}
			}
	}

	return input;
}


int main(int argc, char** argv){
	FILE *file;
	file = fopen("./numbers.txt", "r");
	char *cap = NULL;
	char *ptr;
	size_t len = 0;

	getline(&cap, &len, file);
	uint64_t n = strtoull(cap, &ptr, 10);
	fclose(file);

	int64_t* input = Populate("./numbers.txt", &n); //gets the array
	struct timespec start, end;
	double time_diff;

	clock_gettime(CLOCK_MONOTONIC, &start);
	int64_t* output = my_sort(input, n);
	clock_gettime(CLOCK_MONOTONIC, &end);
	time_diff = (end.tv_sec - start.tv_sec);
	time_diff += (end.tv_nsec - start.tv_nsec) / 1e9;
	//check if it's sorted.

	int sorted = is_sorted(output, n);
	printf("Are the numbers sorted? %s \n", sorted ? "true" : "false");

	//printf("Time elapsed: %lf \n", time_diff);
	free(input);
}
