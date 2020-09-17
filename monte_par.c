/* Kefu Lu
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

int64_t TERMS = 1000000;
PARTITIONS = 10;
double* xs;
double* ys;
double PI = 0;

void* monte_find_pi(void* number){
    //C doesn't actually have Pi as a constant, but...
    //Most modern CPUs actually have an instruction to just load Pi into a register!
    //Some inline assembly here. This should work for all versions of GCC...

    uintptr_t partition = (uintptr_t) number;
    uint64_t block = TERMS/PARTITIONS;
    uint64_t start = block * partition;  
    uint64_t end = block*(partition+1);

    for(int64_t i = start; i< end; i++){
        xs[i] = (2*(double) rand() / RAND_MAX) - 1;
        ys[i] = (2*(double) rand() / RAND_MAX) - 1;
    }
    
    double circle_count = 0;
    double pi_count = 0;
    for(int64_t i = start; i< end; i++){
        if (pow(xs[i], 2) + pow(ys[i], 2) <= 1){
		pi_count+=1;
	}
	else{
		circle_count+=1;
	}
    }

    PI += pi_count/circle_count;

    return NULL;
    //return pi_count/circle_count; 
}

int main(int argc, char** argv){
    //struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    if(argc>=2){
	    TERMS = strtoull(argv[1], NULL, 10);
	    PARTITIONS = strtoull(argv[2], NULL, 10);
    }


    //int64_t time_diff;
    
    //clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
    pthread_t* handlers = malloc(PARTITOINS* sizeof(pthread_t));
    xs = malloc(TERMS * sizeof(double));
    ys = malloc(TERMS * sizeof(double));

    for(int64_t i =0; i < PARTITIONS; i++){
	    pthread_create(&handlers[i], NULL, find_pi, (void*) i);
    }
    //double pi = monte_find_pi();
    //clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!

    //time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    //time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    //printf("The time taken is %f \n", time_diff);
    printf("Pi is %.20f\n", PI);

}
