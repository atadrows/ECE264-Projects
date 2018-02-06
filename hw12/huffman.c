#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huffman.h"

Node *pq_enqueue(Node **pq, const void *new_object, 
                  int (*cmp_fn)(const void *, const void *)){
	if(new_object == NULL){ return NULL; }
	
	Node *new_node = malloc(sizeof(*new_node));
	if(new_node == NULL) { return NULL; }
	new_node->ptr = (void*) new_object;

	if(*pq == NULL || (*cmp_fn)(new_object, (*pq)->ptr) <= 0){
		new_node->next = *pq;
		*pq = new_node;
	} else {
		Node *cur = *pq;
		while(cur->next != NULL && (*cmp_fn)(new_object, cur->next->ptr) > 0){
			cur = cur->next;
		}
		new_node->next = cur->next;
		cur->next = new_node;
	}
	return new_node;
}

                       
Node *pq_dequeue(Node **pq){
	if(*pq == NULL) { return NULL; }
	Node* head = *pq;
	*pq = (*pq)->next;
	head->next = NULL;
	return head;
}


Node *stack_push(Node **stack, const void *new_object){
	if(new_object == NULL){ return NULL; }
	
	Node *new_node = malloc(sizeof(Node));
	if(new_node == NULL) { return NULL; }
	new_node->ptr = (void*) new_object;

	new_node->next = *stack;
	*stack = new_node;

	return new_node;
}

Node *stack_pop(Node **stack){
	if(*stack == NULL) { return NULL; }
	Node* head = *stack;
	*stack = (*stack)->next;
	head->next = NULL;
	return head;
}


Node *remove_last_node(Node **list){
	if(*list == NULL) { return NULL; }
	Node* cur = *list;
	if((*list)->next == NULL) { 
		*list = NULL;
		return cur;
	}
	while(cur->next->next != NULL){
		cur = cur->next;
	}
	Node* removed = cur->next;
	cur->next = NULL;

	return removed;
}


void destroy_node(Node *list, void (*destroy_fn)(void *)){
	Node* temp;
	while(list != NULL){
		temp = list;
		list = list->next;
		destroy_fn(temp->ptr);
		free(temp);
	}

	return;
}

/* print an entire linked list                                           */
/* pq is the address of the first Node in the linked list               */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an Node in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */
 
void print_node(const Node *list, void (*print_fn)(const void *)){
	while (list != NULL) {
		// print the memory associated with list->ptr
		print_fn(list->ptr);
		// print an arrow
		fprintf(stdout, "->");
		list = list->next;
	} 
	// print NULL and a newline after that 
	fprintf(stdout, "NULL\n");
}

