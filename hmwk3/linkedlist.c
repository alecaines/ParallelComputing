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
	pthread_rwlock_t* rwlock = malloc(sizeof(pthread_rwlock_t));
	head -> lock = rwlock;
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

int Delete(void* head, uint32_t loc){
	struct Node* node = (struct Node*)head; //why am I instantiating this like this
	node -> value = malloc(sizeof(uint32_t));
	
	uint32_t count = 0;	
	while(count < loc){
		node = node -> next;
		count+=1;
	}

	struct Node* previous;
	struct Node* subsequent;
	previous = node -> prev;
	subsequent = node -> next;
	previous -> next = subsequent;
	subsequent -> prev = previous;

	return 1;
}

void* Find(void* head, uint32_t value){
	struct Node* node = (struct Node*)head; //why am I instantiating this like this
	while(node != NULL){
		if(node -> value == value){
			uint32_t *p = malloc(sizeof(uint32_t));
			*p = node -> value;
			return p;
		}
		else{
			node = node -> next;
		}
	}
	return NULL;
}

int SafeInsert(void* head, uint32_t value, uint32_t loc){
	struct Node* node = (struct Node*)head;
	pthread_rwlock_t* lock = node -> lock;
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_wrlock(lock);
		Insert(head, value, loc);
	pthread_rwlock_unlock(lock);		

	return 1;
}

int SafeDelete(void* head, uint32_t loc){
	struct Node* node = (struct Node*)head;
	pthread_rwlock_t* lock = node -> lock;
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_wrlock(lock);
		Delete(head, loc);
	pthread_rwlock_unlock(lock);		

	return 1;
}

void* SafeFind(void* head, uint32_t value){
	struct Node* node = (struct Node*)head;
	pthread_rwlock_t* lock = node -> lock;
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_rdlock(lock);
		Find(head, value);
	pthread_rwlock_unlock(lock);		

	return NULL;
}

int Display(void* head){
	struct Node* node = (struct Node*)head;
	node -> value = malloc(sizeof(uint32_t));
	//node -> next = head;
	node = node -> next;
	printf("[ ");
	while(node != NULL){
		printf("%" PRIu32 " ", node -> value);
		node = node -> next;
	}
	printf("]\n");

	return 1;
}

int Destroy(void* head){
	struct Node* node = (struct Node*)head;
	while(node != NULL){
		node = node -> next;	
	}

	while(node != NULL){
		struct Node* previous = (struct Node*)head;
		previous = node;
		node = node -> prev;
		free(previous);
	}

	return 1;
}

