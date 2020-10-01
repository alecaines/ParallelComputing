/*
 * Alexander Caines. This file is a linkedlist implementation. 
 */
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
#include "linkedlist.h"

void* Create(){
	struct Node *head = (struct Node*)malloc(sizeof(*head)); //what amount of space is it actually allocating?
	head -> prev = NULL;
	head -> next = NULL;
	head -> value = 0;
	return head;
}

int Insert(void* head, uint32_t value, uint32_t loc){
	struct Node* node = (struct Node*)malloc(sizeof(struct Node)); //why am I instantiating this like this
	node -> value = malloc(sizeof(uint32_t));
	node -> next = head;

	if(loc == -1){
		//tbd
		while(node -> next != NULL){
			node = node -> next;
		}
		node -> value = value;
		node -> next = NULL;
		//node ->  prev = ???
		printf("%" PRIu32 "\n", (*node).value); 
		return 0;
	}
	else{
		uint32_t count = 0;
		while(count < loc){
			printf("%" PRIu32 "\n", (*node).value); 
			 
			/*
			node -> value = node -> next -> value;
			node -> next = node -> next -> next;
			node -> prev = node;
			*/
			count+=1;
		}
		node -> value = value;
	}

	return 1;
}

int Delete(void* head, uint32_t item){
	return 1;
}

void* Find(void* head, uint32_t value){
	struct Node* node = (struct Node*)malloc(sizeof(struct Node)); //why am I instantiating this like this
	//node -> value = (uint32_t)malloc(sizeof(uint32_t));
	node -> next = head;
	printf("------------------------\n");	
	while(node -> next != NULL){
		if(node -> value == value){
			printf("%" PRIu32 "\n", (*node).value); 
			uint64_t *p = node -> value;
			return p;
		}
		else{
			printf("%" PRIu32 "\n", (*node).value); 
			node = node -> next;
		}
	}
	return NULL;
}

int SafeInsert(void* head, uint32_t value, uint32_t loc){
	return 1;
}

int SafeDelete(void* head, uint32_t item){
	return 1;
}

void* SafeFind(void* head, uint32_t value){
	return NULL;
}

int Display(void* head){
	return 1;
}

int Destroy(void* head){
	return 1;
}
