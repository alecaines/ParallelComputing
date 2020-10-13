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
	//Just allocate a bunch of memory to use up some memory for now...
	*size = 1234;
	return (int64_t*) malloc(1234 * sizeof(size));
}

int my_sort(int64_t* input, uint64_t size){
	if(omp_get_thread_num()%2 == 0){
		for(uint64_t i = 0; i < size - 2; i+=2){
			if(input[i] > input[i+1]){
				int64_t mid = input[i+1];
				input[i+1] = input[i];
				input[i] = mid;
			}
		}
	}

	if(omp_get_thread_num()%2 == 1){
		for(uint64_t i = 1; i < size - 2; i+=2){
			if(input[i] > input[i+1]){
				int64_t mid = input[i+1];
				input[i+1] = input[i];
				input[i] = mid;
			}
		}
	}
	
	return 0;
}

/*
Suggested function to write, to check whether the array is sorted
Returns 0 if not sorted, returns 1 if sorted
*/
int is_sorted(int64_t* input, uint64_t size){
	for(uint64_t i =0; i < size-1; i++){
		if(input[i] > input[i+1]){
			return 0;
		}
	}
    return 1;
}

int main(int argc, char** argv){
	uint64_t n; //The input size
	int64_t* input = Populate("./numbers.txt", &n); //gets the array
	
	struct timespec start, end;
	double time_diff;

	clock_gettime(CLOCK_MONOTONIC, &start);

	#pragma omp parallel
		my_sort(input, n);

	clock_gettime(CLOCK_MONOTONIC, &end);
	time_diff = (end.tv_sec - start.tv_sec);
	time_diff += (end.tv_nsec - start.tv_nsec) / 1e9;
	//check if it's sorted.

	int sorted = is_sorted(input, n);
	printf("Are the numbers sorted? %s \n", sorted ? "true" : "false");

	printf("Time elapsed: %lf \n", time_diff);
	free(input);
}
