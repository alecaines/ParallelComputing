#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //Needed to use int64_t
#include <inttypes.h> //Needed to Specify output format PRId64
#include <time.h> //For timing
#include <pthread.h>

int64_t NUMBERS = 10000;
int THREADS = 10;
uint64_t* results;

//Function with void*
void* Sum(void* number){
    uintptr_t my_rank = (uintptr_t) &number;
    uint64_t block = NUMBERS/THREADS;
    uint64_t start = block * my_rank;
    uint64_t end = block * (my_rank +1);
    uint64_t answer = 0;

    for (uint64_t i = start; i < end; i++){
        answer+=i;
    }

    results[my_rank] = answer;

    return NULL;
}

int main(int argc, char** argv){
    if (argc>=2){
        NUMBERS = strtoull(argv[1], NULL, 10);
    }

    struct timespec start,end; //Structs for timing
    clock_gettime(CLOCK_MONOTONIC, &start); //find proper way to time on windows/gcc
    
    pthread_t* handlers = malloc(THREADS * sizeof(pthread_t));

    results = malloc(THREADS * sizeof(uint64_t));

    //split the sum into partial sums for each thread
    
    for (uintptr_t i =0; i < THREADS; i++){
        pthread_create(&handlers[i], NULL, Sum, (void*) i); 
    }

    for (uintptr_t i =0;i < THREADS; i++){
	    pthread_join(handlers[i], NULL);
    }
    
    //sum up the results 
    uint64_t answer = 0;
    for(int i =0;i < THREADS; i++){
	    answer+=results[i];
    }
    
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    free(handlers);
    free(results);
    printf("The sum is %"PRIu64"\n", answer); //Should be "portable" for all compilers

    //printf("The sum is %lld\n", ans);  //For linux/mac/gcc
    //printf("The sum is %I64d\n", ans); //For some compilers



    double diff;
    diff = (end.tv_sec - start.tv_sec); //time diff in seconds
    diff += (end.tv_nsec - start.tv_nsec) / 1e9;    //residue time diff in nanosecs
    printf("The time taken is %f \n", diff);
}
