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

int64_t TERMS = 1000000;
double* xs;
double* ys;

double monte_find_pi(){
    //C doesn't actually have Pi as a constant, but...
    //Most modern CPUs actually have an instruction to just load Pi into a register!
    //Some inline assembly here. This should work for all versions of GCC...

    for(int64_t i =0; i< TERMS; i++){
        xs[i] = (2)*((double) rand() / (double) RAND_MAX) - 1;
        ys[i] = (2)*((double) rand() / (double) RAND_MAX) - 1;
    }
    
    double circle_count = 0;
    double square_count = 0;
    for(int64_t i =0; i< TERMS; i++){
        if (pow(xs[i], 2) + pow(ys[i], 2) < 1){
		circle_count+=1;
	}
	else{
		square_count+=1;
	}
    }

    return circle_count/square_count; 
}

int main(int argc, char** argv){
    //struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    if(argc>=2){
	    TERMS = strtoull(argv[1], NULL, 10);
    }


    int64_t time_diff;
    
    clock_gettime(CLOCK_REALTIME, &start); //Start the clock!
    xs = malloc(TERMS * sizeof(double));
    ys = malloc(TERMS * sizeof(double));
    double pi = monte_find_pi();
    clock_gettime(CLOCK_REALTIME, &end);   //Stops the clock!

    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    printf("The time taken is %f \n", time_diff);
    printf("Pi is %.20f\n", pi);

}
