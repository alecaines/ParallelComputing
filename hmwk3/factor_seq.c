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

int64_t TARGET = 64367;
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

void find_factors(){
    for(int64_t i =1; i< TARGET; i+=2){
	    if(is_prime(i) == 1){
		for(int64_t k = i; k < TARGET; k+=2){
			if(k * i == TARGET && is_prime(k)){
				factors[0] = i;
				factors[1] = k;

				return;
			}
		}
	    }
    }

}


int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    if(argc>=2){
	    TARGET = strtoull(argv[1], NULL, 10);
    }


    double time_diff;
    factors = malloc(2*sizeof(int64_t));

    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
    find_factors();
    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!

    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    printf("The time taken is %f \n", time_diff);
    printf("%" PRId64 " * %" PRId64 " = %" PRId64 "\n", factors[0], factors[1], TARGET);

    free(factors);
}
