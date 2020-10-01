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

int SUCCESS = 0;

void* Create(){
	struct Node *head = (struct Node*)malloc(sizeof(*head)); //what amount of space is it actually allocating?
	head -> prev = NULL;
	head -> next = NULL;
	head -> value = 0;
	return head;
}

int Insert(void* head, uint32_t value, uint32_t loc){
	struct Node* node = (struct Node*)head; //why am I instantiating this like this
	node -> value = malloc(sizeof(uint32_t));
	if(loc == -1){
		while(node -> next != NULL){
			node = node -> next;
		}

		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode -> value = malloc(sizeof(uint32_t));
		newNode -> value = value;
		newNode -> prev = node;
		node -> next = newNode;	

		//printf("%" PRIu32 "\n", (*node).value); 
		return 0;
	}
	else{
		uint32_t count = 0;
		while(count < loc){
			node = node -> next;
			count+=1;
		//printf("%" PRIu32 "\n", (*node).value); 
		}
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode -> value = malloc(sizeof(uint32_t));
		newNode -> value = value;
		newNode -> prev = node;
		newNode -> next = node -> next;
		node -> next = newNode;
	}

	return 1;
}

int Delete(void* head, uint32_t item){
	struct Node* node = (struct Node*)head; //why am I instantiating this like this
	node -> value = malloc(sizeof(uint32_t));
	while(node != NULL || SUCCESS == 1){
		if(node -> value == item){
			struct Node* previous = (struct Node*)malloc(sizeof(struct Node));
		       	struct Node* subsequent = (struct Node*)malloc(sizeof(struct Node));
		       	previous = node -> prev;
		       	subsequent = node -> next;
			previous -> next = subsequent;
			subsequent -> prev = previous;
			SUCCESS = 1;
		}
	}

	return 1;
}

void* Find(void* head, uint32_t value){
	struct Node* node = (struct Node*)head; //why am I instantiating this like this
	//node -> value = (uint32_t)malloc(sizeof(uint32_t));
	//node -> next = head;
	//printf("------------------------\n");	
	while(node != NULL){
		if(node -> value == value){
			//printf("%" PRIu32 "\n", (*node).value); 
			uint32_t *p = malloc(sizeof(uint32_t));
			*p = node -> value;
			return p;
		}
		else{
			//printf("%" PRIu32 "\n", (*node).value); 
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
	struct Node* node = (struct Node*)head;
	node -> value = malloc(sizeof(uint32_t));
	//node -> next = head;
	node = node -> next;
	printf("[");
	while(node != NULL){
		printf("%" PRIu32 " ", node -> value);
		node = node -> next;
	}
	printf("]\n");

	return 1;
}

int Destroy(void* head){
	return 1;
}
