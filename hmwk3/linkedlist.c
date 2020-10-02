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
	if(loc == -1){
		while(node -> next != NULL){
			node = node -> next;
		}

		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		//newNode -> value = malloc(sizeof(uint32_t));
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
		//newNode -> value = malloc(sizeof(uint32_t));
		newNode -> value = value;
		newNode -> prev = node;
		newNode -> next = node -> next;
		node -> next = newNode;
	}
	//free(node);
	return 1;
}

int Delete(void* head, uint32_t loc){
	struct Node* node = (struct Node*)head; //why am I instantiating this like this
	
	uint32_t count = 0;	
	while(count < loc){
		node = node -> next;
		count+=1;
	}
	
	if(node == NULL){
		return 1;
	}

	struct Node* previous;
	struct Node* subsequent;
	previous = node -> prev;
	subsequent = node -> next;
	previous -> next = subsequent;
	subsequent -> prev = previous;
	//free(node);
	return 0;
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
	//free(node);
	return NULL;
}

int SafeInsert(void* head, uint32_t value, uint32_t loc){
	struct Node* lock_node = (struct Node*)head;
	pthread_rwlock_t* lock = lock_node -> lock;
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_wrlock(lock);

	struct Node* node = (struct Node*)head; //why am I instantiating this like this
	if(loc == -1){
		while(node -> next != NULL){
			node = node -> next;
		}

		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		//newNode -> value = malloc(sizeof(uint32_t));
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
		//newNode -> value = malloc(sizeof(uint32_t));
		newNode -> value = value;
		newNode -> prev = node;
		newNode -> next = node -> next;
		node -> next = newNode;
	}
	//free(node);
	pthread_rwlock_unlock(lock);		
	//free(lock_node);	
	return 1;
}

int SafeDelete(void* head, uint32_t loc){
	struct Node* lock_node = (struct Node*)head;
	pthread_rwlock_t* lock = lock_node -> lock;
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_wrlock(lock);

	struct Node* node = (struct Node*)head; //why am I instantiating this like this
	
	uint32_t count = 0;	
	while(count < loc){
		node = node -> next;
		count+=1;
	}
	
	if(node == NULL){
		return 1;
	}

	struct Node* previous;
	struct Node* subsequent;
	previous = node -> prev;
	subsequent = node -> next;
	previous -> next = subsequent;
	subsequent -> prev = previous;
	
	
	//free(node);
	pthread_rwlock_unlock(lock);		
	//free(lock_node);
	return 0;
}

void* SafeFind(void* head, uint32_t value){
	struct Node* lock_node = (struct Node*)head;
	pthread_rwlock_t* lock = lock_node -> lock;
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_rdlock(lock);
	
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

	//free(node);
	pthread_rwlock_unlock(lock);		
	//free(lock_node);
	return NULL;
}

int Display(void* head){
	struct Node* lock_node = (struct Node*)head;
	pthread_rwlock_t* lock = lock_node -> lock;
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_rdlock(lock);
	
	struct Node* node = (struct Node*)head;
	//node -> value = malloc(sizeof(uint32_t));
	//node -> next = head;
	node = node -> next;
	int count = 0;
	printf("[ ");
	while(node != NULL){
		printf("%" PRIu32 " ", node -> value);
		node = node -> next;
		count+=1;
	}
	printf("]\n");

	//free(node);
	pthread_rwlock_unlock(lock);		
	//free(lock_node);
	return count;
}

int Destroy(void* head){
	struct Node* lock_node = (struct Node*)head;
	pthread_rwlock_t* lock = lock_node -> lock;
	pthread_rwlock_init(lock, NULL);
	pthread_rwlock_rdlock(lock);
	
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
	//free(node);
	pthread_rwlock_unlock(lock);		
	//free(lock_node);
	return 1;
}

