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

/*
Suggested function to write, to check whether the array is sorted
Returns 0 if not sorted, returns 1 if sorted
*/
int is_sorted(int64_t* input, uint64_t size){

	/*for(uint64_t i = 0; i < size-1; i++){
		printf("%" PRId64 "\n", input[i]);
	}*/

	for(uint64_t i = 0; i < size-1; i++){
		if(input[i] > input[i+1]){
			return 0;
		}
	}
	return 1;
}

int merge(int64_t* input, int start, int midPoint, int end){
	
	printf("partition %d %d %d\n", start, midPoint, end);
	
	if(end - start == 1){
		return 0;
	}
	else if(end - start == 2){
		if(input[start] > input[end]){
			int64_t temp = input[start];
			input[start] = input[end];
			input[end] = temp;
		}
	}
	else{
		int64_t* partition_1 = malloc(sizeof(int64_t) * (midPoint - start +1));	
		int64_t* partition_2 = malloc(sizeof(int64_t) * (end - midPoint));	

		for(int i = start; i < midPoint - start + 1; i++){
			partition_1[i] = input[i];
		}
		
		for(int i = midPoint; i < end; i++){
			partition_2[i] = input[i];
		}

		printf("\n");

		int p1_count = 0;
		int p2_count = 0;
		int input_count = start;

		while(p1_count < (midPoint - start + 1) && p2_count < (end - midPoint)){
			if(partition_1[p1_count] < partition_2[p2_count]){
				input[input_count] = partition_1[p1_count];
				input_count++;
				p1_count++;
			}
			else{
				input[input_count] = partition_2[p2_count];
				input_count++;
				p2_count++;
			}
		}

		while(p1_count < (midPoint - start + 1)){
			input[input_count] = partition_1[p1_count];
			input_count++;
			p1_count++;
		}

		while(p2_count < (end - midPoint)){
			input[input_count] = partition_2[p2_count];
			input_count++;
			p2_count++;
		}

		free(partition_1);
		free(partition_2);
	}

	return 0;
}

int my_sort(int64_t* input, uint64_t start, uint64_t end){
	if(start < end){
		int midPoint = start + (end - start)/2;
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

	my_sort(input, 0, n);

	//check if it's sorted.
	int sorted = is_sorted(input, n);
	printf("Are the numbers sorted? %s \n", sorted ? "true" : "false");

	printf("Time elapsed: %lf \n", 0.0);
	free(input);
}
