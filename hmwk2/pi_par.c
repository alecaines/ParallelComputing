/* Alexander Caines 
 * Parallelized pi approximation.
*/
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

int64_t TERMS = 10;
int64_t PARTITIONS = 10;
double PI=0;
double* results;

void* find_pi(void* number){
    //C doesn't actually have Pi as a constant, but...
    //Most modern CPUs actually have an instruction to just load Pi into a register!
    //Some inline assembly here. This should work for all versions of GCC...
    
    uintptr_t partition = (uintptr_t) number;
    uint64_t block = TERMS/PARTITIONS;
    uint64_t start = block * partition;  
    uint64_t end = block*(partition+1);
    double Pi = 0;
    
    for(int64_t i = start; i < end; i++){
	    Pi+= ((double) pow(-1, i)) * 1./((double)(2*i+1));
    }

    results[partition] = Pi;

    return NULL;
}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    
    if(argc>=2){
	    TERMS = strtoull(argv[1], NULL, 10);
	    PARTITIONS = strtoull(argv[2], NULL, 10);
    }

    pthread_t* handlers = malloc(PARTITIONS * sizeof(pthread_t));
    results = malloc(PARTITIONS * sizeof(double));

    double time_diff;
    
    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
      
    //creating the threads
    for(uintptr_t i = 0; i < PARTITIONS; i++){
	    pthread_create(&handlers[i], NULL, find_pi, (void*) i);
    }

    //joining the threads
    
    for(uintptr_t i = 0; i < PARTITIONS; i++){
	    pthread_join(handlers[i], NULL);
    }

    for(int i =0;i < PARTITIONS; i++){
	    PI+=results[i];
    }

    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!

    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    printf("The time taken is %f \n", time_diff);
    PI*=4;

    printf("Parallel approximation of PI %.20f\n", PI);
    
}
