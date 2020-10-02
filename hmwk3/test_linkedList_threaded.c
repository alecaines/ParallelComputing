#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "linkedlist.h"

int THREADCOUNT = 400;
int OPS = 2; //An even number!

int MoreTests();

void* DoSafeDeletes(void* head){
    int t = time(NULL) ^ pthread_self();
    srand(t);
    for (int i =0; i < OPS/2; i++){
        uint32_t loc = rand() % (OPS);
	//printf("Do %d\n", i);
        SafeDelete(head, loc);
    }
    return NULL;
}
void* DoSafeInserts(void* head){
    int t = time(NULL) ^ pthread_self();
    srand(t);
    for (int i =0; i<OPS; i++){
        uint32_t val = rand() % (THREADCOUNT * OPS);
        uint32_t loc = rand() % (OPS);
        SafeInsert(head, val, loc);
    }
    return NULL;
}

void* DoDeletes(void* head){
    int t = time(NULL) ^ pthread_self();
    srand(t);
    for (int i =0; i < OPS/2; i++){
        uint32_t loc = rand() % (OPS);
        Delete(head, loc);
    }
    return NULL;
}
void* DoInserts(void* head){
    int t = time(NULL) ^ pthread_self();
    srand(t);
    for (int i =0; i<OPS; i++){
        uint32_t val = rand() % (THREADCOUNT * OPS);
        uint32_t loc = rand() % (OPS);
        Insert(head, val, loc);
    }
    return NULL;
}

int TestSafeInserts(void* head){
    pthread_t* handlers = malloc(sizeof(pthread_t)*THREADCOUNT);
    for (int i = 0; i< THREADCOUNT; i++){
        pthread_create(&handlers[i], NULL, DoSafeInserts, (void*) head);
    }
  
    for (int i = 0; i< THREADCOUNT; i++){
        pthread_join(handlers[i], NULL);
    }

    int length = Display(head);
    printf("There are %d numbers. There should be %d numbers. \n", length, THREADCOUNT * OPS);
    return 0;
}

int TestSafeDeletes(void* head, int target_numb){
    pthread_t* handlers = malloc(sizeof(pthread_t)*THREADCOUNT);
    for (int i = 0; i< THREADCOUNT; i++){
	//printf("Test %d\n", i);
        pthread_create(&handlers[i], NULL, DoSafeDeletes, (void*) head);
    }
  
    for (int i = 0; i< THREADCOUNT; i++){
        pthread_join(handlers[i], NULL);
    }

    int length = Display(head);
    printf("There are %d numbers. There should be %d numbers. \n", length, target_numb);
    return 0;
}

int TestUnsafeInserts(void* head){
    pthread_t* handlers = malloc(sizeof(pthread_t)*THREADCOUNT);
    for (int i = 0; i< THREADCOUNT; i++){
        pthread_create(&handlers[i], NULL, DoInserts, (void*) head);
    }
  
    for (int i = 0; i< THREADCOUNT; i++){
        pthread_join(handlers[i], NULL);
    }

    int length = Display(head);
    printf("There are %d numbers. There should be %d numbers. \n", length, THREADCOUNT * OPS);
    return 0;
}

int TestUnsafeDeletes(void* head, int target_numb){
    pthread_t* handlers = malloc(sizeof(pthread_t)*THREADCOUNT);
    for (int i = 0; i< THREADCOUNT; i++){
        pthread_create(&handlers[i], NULL, DoDeletes, (void*) head);
    }
  
    for (int i = 0; i< THREADCOUNT; i++){
        pthread_join(handlers[i], NULL);
    }

    int length = Display(head);
    printf("There are %d numbers. There should be %d numbers. \n", length, target_numb);
    return 0;
}

int main(int argc, char** argv){
    if (argc == 2){
        THREADCOUNT = strtoul(argv[1], NULL, 10);
    }

    printf("Safe tests!\n");
    //"Safe" tests
    printf("Trying Creating\n");
    void* head = Create();
    printf("Finished Creating\n");
    printf("Trying Inserting\n");
    TestSafeInserts(head);
    printf("Finished Safe Inserting\n");
    printf("Trying SafeDeletes\n");
    TestSafeDeletes(head, THREADCOUNT * OPS/2);
    printf("Finisehd Safe Deletes\n");
    printf("Trying SafeDeletes again\n");
    TestSafeDeletes(head, 0);
    printf("Finisehd Safe Deletes again\n");
    printf("Trying Destroying\n");
    Destroy(head);
    printf("Finished Destroying\n");

    //"Unsafe" tests
    //These may cause crashes or other race-y things.
    printf("\n\nUnsafe tests!\n");
    head = Create();
    TestUnsafeInserts(head);
    TestUnsafeDeletes(head, THREADCOUNT * OPS/2);
    TestUnsafeDeletes(head, 0);
    Destroy(head);

    MoreTests(); //There are always more!
    return 0;
}

int MoreTests(){
    return 0;
}
