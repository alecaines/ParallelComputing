/* Alexander Caines 
Example code for Pi using some inline assembly.
Serves to demonstrate how to time code!
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

uint64_t TARGET = 646367;
uint64_t PARTITIONS = 10;
uint64_t* factors;
int SUCCESS = 0;

void* find_factors(void* number){

    if(SUCCESS == 1){
	    return NULL;
    }

    uintptr_t partition = (uintptr_t) number;
    uint64_t block = TARGET/PARTITIONS;
    uint64_t start = block * partition;  
    start = (start > 0) ? start : 3;
    uint64_t end = block*(partition+1);

    for(uint64_t i = start; i< end; i+=2){
	if(SUCCESS == 1){
	       return NULL;
	}
	else{
		if(TARGET%i==0){
			factors[0] = i;
			factors[1] = TARGET/i;
			SUCCESS = 1;
		}
	}

    }


    return NULL;
}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    if(argc==2){
	    TARGET = strtoull(argv[1], NULL, 10);
    }
    if(argc==3){
	    TARGET = strtoull(argv[1], NULL, 10);
	    PARTITIONS = strtoull(argv[2], NULL, 10);
    }

    if(TARGET % 3 == 0){ 
	    uint64_t div = TARGET / 3;
	    printf("%d * %" PRIu64 " = %" PRIu64 "\n", 3, div, TARGET);
    }
    else if(TARGET % 5 == 0){
	    uint64_t div = TARGET / 5;
	    printf("%d * %" PRIu64 " = %" PRIu64 "\n", 5, div, TARGET);
    }
    else if(TARGET % 2 == 0){
	    uint64_t div = TARGET / 2;
	    printf("%d * %" PRIu64 " = %" PRIu64 "\n", 2, div, TARGET);
    }
    else if(TARGET % 7 == 0){
	    uint64_t div = TARGET / 7;
	    printf("%d * %" PRIu64 " = %" PRIu64 "\n", 7, div, TARGET);
    }
    else{

	    double time_diff;
	    
	    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
	    pthread_t* handlers = malloc(PARTITIONS* sizeof(pthread_t));
	    factors = malloc(PARTITIONS*sizeof(double));

	    for(uint64_t i = 0; i < PARTITIONS; i++){
		    pthread_create(&handlers[i], NULL, find_factors, (void*) i);
	    }

	    for(uint64_t i = 0; i < PARTITIONS; i++){
		    pthread_join(handlers[i], NULL);
	    }

	    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!
	    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
	    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

	    printf("The time taken is %f\n", time_diff);
	    printf("%" PRIu64 " * %" PRIu64 " = %" PRIu64 "\n", factors[0], factors[1], TARGET);

	    free(handlers);
	    free(factors);
    }
}
