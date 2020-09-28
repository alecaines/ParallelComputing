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

int64_t TARGET = 10000000;
int64_t PARTITIONS = 10;
int64_t* factors;

int is_prime(int64_t alleged){
	if(alleged == 1){
		return 0;
	}

	for(int64_t j=2; j < alleged; j++){
		if(alleged % j == 0){
			return 0;
		}
	}

	return 1;
}

void* find_factors(void* number){

    uintptr_t partition = (uintptr_t) number;
    uint64_t block = TARGET/PARTITIONS;
    uint64_t start = block * partition;  
    uint64_t end = block*(partition+1);

    for(int64_t i = start; i< end; i+=2){
	    if(is_prime(i) == 1){
		    printf("hey\n");
		    printf("%" PRId64 "\n", i);
		    for(int64_t k = i; k < TARGET; k+=2){
			    printf("wassup\n");
			    printf("%" PRId64 " % " PRId64 "\n", i, k);
			    if(k * i == TARGET && is_prime(k)){
				    factors[0] = i;
				    factors[1] = k;

				    return NULL;
			    }
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
	    int64_t div = TARGET / 3;
	    printf("%d * %" PRId64 " = %" PRId64 "\n", 3, div, TARGET);
    }
    else if(TARGET % 5 == 0){
	    int64_t div = TARGET / 5;
	    printf("%d * %" PRId64 " = %" PRId64 "\n", 5, div, TARGET);
    }
    else if(TARGET % 2 == 0){
	    int64_t div = TARGET / 2;
	    printf("%d * %" PRId64 " = %" PRId64 "\n", 2, div, TARGET);
    }
    else if(TARGET % 7 == 0){
	    int64_t div = TARGET / 7;
	    printf("%d * %" PRId64 " = %" PRId64 "\n", 7, div, TARGET);
    }
    else{

	    double time_diff;
	    
	    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
	    pthread_t* handlers = malloc(PARTITIONS* sizeof(pthread_t));
	    factors = malloc(PARTITIONS*sizeof(double));

	    for(int64_t i = 0; i < PARTITIONS; i++){
		    pthread_create(&handlers[i], NULL, find_factors, (void*) i);
	    }

	    for(int64_t i = 0; i < PARTITIONS; i++){
		    pthread_join(handlers[i], NULL);
	    }

	    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!
	    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
	    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

	    printf("The time taken is %f\n", time_diff);
	    printf("%" PRId64 " * %" PRId64 " = %" PRId64 "\n", factors[0], factors[1], TARGET);

	    free(handlers);
	    free(factors);
    }
}
