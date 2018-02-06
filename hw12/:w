#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

Node* _create_linked_list(int);
Node* _create_strings_linked_list(int, char**);
static int _int_cmp(const void*, const void*);
//static int _string_cmp(const void*, const void*);
static void _string_print(const void*);
static void _int_print(const void*);
void _print_linked(Node*);
void _free_linked(Node*);
void _free_nothing();

int main(int argc, char** argv){
	// Create a new linked list
	Node* list = _create_linked_list(5);
	printf("Original list: ");
	print_node(list, &_int_print);

	// Test pq_enqueue 
	// Middle insertion
	int* i = malloc(sizeof(*i));
	if(i != NULL){
		*i = 3;
		pq_enqueue(&list, i, &_int_cmp);
		printf("Middle insert: ");
		print_node(list, &_int_print);
	}
	// Head insert
	int* q = malloc(sizeof(*i));
	if(q != NULL){
		*q = -8;
		pq_enqueue(&list, q, &_int_cmp);
		printf("Head insert: ");
		print_node(list, &_int_print);
	}
	// Tail insert
	int* w = malloc(sizeof(*i));
	if(w != NULL){
		*w = 20;
		pq_enqueue(&list, w, &_int_cmp);
		printf("Tail insert: ");
		print_node(list, &_int_print);
	}


	// Test pq_dequeue
	Node* head = pq_dequeue(&list);
	printf("Dequeued list: ");
	print_node(list, &_int_print);
	printf("Dequeued head: ");
	print_node(head, &_int_print);

	// Test stack_push
	int* j = malloc(sizeof(*j));
	if(j != NULL){
		*j = 100;
		stack_push(&list, j);
		printf("Stack push: ");
		print_node(list, &_int_print);
	}

	// Test stack_pop
	Node* first = pq_dequeue(&list);
	printf("Dequeued list: ");
	print_node(list, &_int_print);
	printf("Dequeued first: ");
	print_node(first, &_int_print);

	// Test remove_last_node
	Node* removed = remove_last_node(&list);
	printf("Lastless list: ");
	print_node(list, &_int_print);
	printf("Removed node: ");
	print_node(removed, &_int_print);

	// Test destroy_list
	Node* destroy_list = _create_linked_list(5);
	print_node(destroy_list, &_int_print);
	destroy_node(destroy_list, &free);
	
	// Test with strings
	Node* string_list = _create_strings_linked_list(argc, argv);
	print_node(string_list, &_string_print);
	destroy_node(string_list, &_free_nothing);

	destroy_node(removed, &free);
	destroy_node(first, &free);
	destroy_node(list, &free);
	destroy_node(head, &free);

	/*_free_linked(removed);
	_free_linked(first);
	_free_linked(list);
	_free_linked(head);*/
	return EXIT_SUCCESS;
}

static int _int_cmp(const void* p1, const void* p2){
	printf("%d - %d = %d\n", *(const int*)p1, *(const int*)p2, *(const int*)p1 - *(const int*)p2);
	return *(const int*)p1 - *(const int*)p2;
}

/*static int _string_cmp(const void* p1, const void* p2) {
	return strcmp((const char*)p1, (const char*)p2);
}*/

static void _int_print(const void* ptr) {
	printf("%d", *(const int*)ptr);
}

static void _string_print(const void* ptr) {
	printf("%s", (const char*)ptr);
}

void _free_nothing(){
	// Do nothing, free nothing
}

Node* _create_linked_list(int size){
	Node* first_node = malloc(sizeof(Node));
	if(first_node == NULL){ return NULL;}
	Node* current_node = first_node;

	for(int i = 0; i < size; i+=2){
		current_node->ptr = malloc(sizeof(i));
		if(current_node->ptr == NULL){ return NULL; }
		*(int*)current_node->ptr = i;
		if(i < size - 1){
			Node* next_node = malloc(sizeof(Node));
			current_node->next = next_node;
			current_node = next_node;
		}
	}
	current_node->next = NULL;
	return first_node;
}

Node* _create_strings_linked_list(int argc, char** strings){
	Node* first_node = malloc(sizeof(Node));
	if(first_node == NULL){ return NULL;}
	Node* current_node = first_node;

	for(int i = 0; i < argc; i++){
		//current_node->ptr = malloc(strlen(strings[i]) + 1);
		//if(current_node->ptr == NULL){ return NULL; }
		//strncpy(current_node->ptr,strings[i], strlen(strings[i]));
		current_node->ptr = strings[i];
		if(i < argc - 1){
			Node* next_node = malloc(sizeof(Node));
			current_node->next = next_node;
			current_node = next_node;
		}
	}
	current_node->next = NULL;
	return first_node;
}


void _print_linked(Node* first){
	Node* cur = first;
	while(cur != NULL){
		printf("%d -> ", *(int*)cur->ptr);
		cur = cur->next;
	}
	printf("NULL\n");
}

void _free_linked(Node* first){
	Node* temp;
	while(first != NULL){
		temp = first;
		first = first->next;
		printf("Freeing: %d\n", *(int*)temp->ptr);
		free(temp->ptr);
		free(temp);
	}
}


