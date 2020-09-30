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
	struct Node* node = malloc(sizeof(struct Node)); //why am I instantiating this like this
	if(loc == -1){
		while(node -> next != NULL){
			node = node -> next;
			if(node -> next == NULL){
				struct Node* newNode = malloc(sizeof(struct Node));
				newNode -> prev = node;
				newNode -> next = NULL;
				newNode -> value = value;
			}
		}
	}
	else{
		struct Node* insert = (struct Node*)malloc(sizeof(struct Node));
		//node = head -> next;
		uint64_t i = 0;

		while(i != loc){
			node = node -> next;
			i+=1;
		}

		insert -> prev = node -> prev;
		insert -> next = node;
		insert -> value = value;
	}
	return 1;
}

int Delete(void* head, uint32_t item){
	return 1;
}

void* Find(void* head, uint32_t value){
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
