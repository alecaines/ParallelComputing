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

uint64_t TARGET = 646367;
uint64_t* factors;
int SUCCESS = 0;

void* find_factors(){
    for(uint64_t i =3; i< TARGET; i+=2){
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
    if(argc>=2){
	    TARGET = strtoull(argv[1], NULL, 10);
    }


    double time_diff;
    factors = malloc(2*sizeof(uint64_t));

    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
    find_factors();
    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!

    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    printf("%" PRIu64 " * %" PRIu64 " = %" PRIu64 "\n", factors[0], factors[1], TARGET);
    printf("Time: %f \n", time_diff);

    free(factors);
}
