/* 
Kefu Lu
Example code for Pi using some inline assembly.
Serves to demonstrate how to time code!
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

double find_pi(){
    //C doesn't actually have Pi as a constant, but...
    //Most modern CPUs actually have an instruction to just load Pi into a register!
    //Some inline assembly here. This should work for all versions of GCC...
    double Pi;
    asm("fldpi \n\t" "fstpl %0" : "=m"(Pi));
    return Pi; 
}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    double time_diff;
    
    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
    double pi = find_pi();
    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!

    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    printf("The time taken is %f \n", time_diff);
    printf("This example doesn't use terms\n");
    printf("Pi is %.20lf\n", pi);
}
