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
#include <omp.h>

int64_t TERMS = 1000000;
int64_t PARTITIONS = 10;
double PI = 0;

void* find_pi(double* current_PI){
    uintptr_t partition = (uintptr_t) omp_get_thread_num();
    uint64_t block = TERMS/PARTITIONS;
    uint64_t start = block * partition;  
    uint64_t end = block*(partition+1);
    double Pi = 0;
    
    for(int64_t i = start; i < end; i++){
	    Pi+= ((double) pow(-1, i)) * 1./((double)(2*i+1));
    }

    *current_PI = *current_PI+ 4*Pi;

    return NULL;
}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    if(argc==2){
	    TERMS = strtoull(argv[1], NULL, 10);
    }
    if(argc==3){
	    TERMS = strtoull(argv[1], NULL, 10);
	    PARTITIONS = strtoull(argv[2], NULL, 10);
    }

    double time_diff;
    
    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
      
    //openmp implementation
    #pragma omp parallel num_threads(PARTITIONS)
	    find_pi(&PI);
    

    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!

    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    printf("The time taken is %f \n", time_diff);
    printf("The number of terms is %" PRId64 "\n", TERMS);
    //printf("Parallel approximation of PI %" PRIu64 "\n", PI);
    printf("OpenMP approximation of PI %f\n", PI);
    
}
