#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //Needed to use int64_t
#include <inttypes.h> //Needed to Specify output format PRId64
#include <time.h> //For timing

int64_t NUMBERS = 10000;
//Function with void*
uint64_t Sum(){
    uint64_t answer = 0;
    for (uint64_t i = 0; i < NUMBERS; i++){
        answer+=i;
    }
    return answer;
}

int main(int argc, char** argv){
    if (argc>=2){
        NUMBERS = strtoull(argv[1], NULL, 10);
    }

    struct timespec start,end; //Structs for timing
    //clock_gettime(CLOCK_MONOTONIC, &start); //find proper way to time on windows/gcc
    uint64_t ans = Sum();
    //clock_gettime(CLOCK_MONOTONIC, &end);

    printf("The sum is %"PRIu64"\n", ans); //Should be "portable" for all compilers

    //printf("The sum is %lld\n", ans);  //For linux/mac/gcc
    //printf("The sum is %I64d\n", ans); //For some compilers



    /*double diff;
    diff = (end.tv_sec - start.tv_sec); //time diff in seconds
    diff += (end.tv_nsec - start.tv_nsec) / 1e9;    //residue time diff in nanosecs
    printf("The time taken is %f \n", diff);*/
}
