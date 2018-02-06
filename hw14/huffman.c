#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"

const int ASCII_COUNT = 256;

// Homework 14

// Outputs a string header containing a char header in
// bits to the file fp
void print_huffman_bits(FILE* fp, char* header){
	int i = 0, num_bits = 0;
	int bit_data = 0;
	while(header[i] != '\0'){
		if (header[i] == '0'){
			//bit_data = (0 << (8 - num_bits));
			num_bits++;
			if(num_bits == 8){
				fputc(bit_data, fp);
				num_bits = 0;
				bit_data = 0;
			}
		} else {
			bit_data = bit_data | 1;
			num_bits++;
			i++;
			if(num_bits == 8){
				fputc(bit_data, fp);
				num_bits = 0;
				bit_data = 0;
			}
			bit_data = bit_data << (8 - num_bits);
			int most = header[i] >> num_bits;
			int least = header[i] << (8 - num_bits);

			fputc(bit_data + most, fp);
			bit_data = least >> (8 - num_bits);
		}
		bit_data = bit_data << 1;
		i++;
	}
	if(num_bits > 0){
		fputc(bit_data, fp);
	}
}

void print_char_header(FILE* fp, TreeNode* tree){
	if(tree == NULL){
		return;
	}

	print_char_header(fp, tree->left);
	print_char_header(fp, tree->right);

	if(tree->left == NULL && tree->right == NULL){
		fputc('1', fp);
		fputc(tree->c, fp);
		return;
	}
	fputc('0', fp);
	return;
}

// EVERYTHING BELOW HERE IS HW12/HW13

// Creates an 256 length int array of the number of 
// occurances of each ascii char in a file and returns it
void create_ascii_count_array(FILE* fp, long* asciiCount){
	rewind(fp);
	int c = 0;
	int i = 0;
	while ((c = fgetc(fp)) != EOF){
		asciiCount[c]++;
		i++;
	}
}

// Prints the ascii array to the desired output
void print_ascii_array(FILE* fp, long* array){
	for (int i = 0; i < ASCII_COUNT; i++){
		fprintf(fp, "%ld\n", array[i]);
	}
}

// Creates a linked list at head using the frequency values in array
Node* create_sorted_list(Node* head, long* array){
	for (int i = 0; i < ASCII_COUNT; i++){
		if(array[i] != 0){
			TreeNode* new_tree = malloc(sizeof(*new_tree));
			if(new_tree == NULL){ 
				return NULL; 
			}
			new_tree->c = (char) i;
			new_tree->count = array[i];
			new_tree->left = NULL;
			new_tree->right = NULL;
			pq_enqueue(&head, new_tree, &tree_compare);
		}
	}
	return head;
}

// Constructs a huffman tree from the ascii linked list
// And frees lost nodes from the list

Node* build_tree(Node* list){
	if(list == NULL) { 
		return NULL;
	}
	TreeNode* parent = NULL;

	while(list->next != NULL){
		Node* first = stack_pop(&list);
		Node* second = stack_pop(&list);
		
		parent = malloc(sizeof(*parent));
		if(parent == NULL) { 
			return NULL; 
		} 
		parent->left = first->ptr;
		parent->right = second->ptr;
		parent->count = parent->left->count + parent->right->count;
		
		pq_enqueue(&list, parent, &huf_compare);
		
		free(first);
		free(second);
	}

	return list;
}

int huf_compare (const void* t1, const void* t2){
	if (((TreeNode*) t1)->count == ((TreeNode*) t2)->count){
		if((((TreeNode*) t1)->left != NULL && ((TreeNode*) t1)->right != NULL) || (((TreeNode*) t2)->left == NULL && ((TreeNode*) t2)->right == NULL)){
			return 1;
		} else {
			return -1;
		}
	}
	return ((TreeNode*) t1)->count - ((TreeNode*) t2)->count;

}

// Returns a string of the correctly formatted coded values
void print_coded_values(FILE* fp, TreeNode* top, char path[], int numChar){
	if(top == NULL) { 
		return; 
	}
	if(top->left == NULL && top->right == NULL){
		fprintf(fp, "%c:%s\n", top->c, path);
	} else {
		char* new = malloc(sizeof(*new) * (numChar + 1));
		strcpy(new, path);
		new[numChar] = '\0';
		new[numChar-1] = '0';
		print_coded_values(fp, top->left, new, numChar+1);
		new[numChar-1] = '1';
		print_coded_values(fp, top->right, new, numChar+1);
		free(new);
	}
}

// Removes the first Node on the stack
Node *stack_pop(Node **stack){
	if(*stack == NULL) { 
		return NULL; 
	}
	Node* head = *stack;
	*stack = (*stack)->next;
	head->next = NULL;
	return head;
}


// Compares two TreeNodes
int tree_compare (const void* t1, const void* t2){
	if(((TreeNode*) t1)->count == ((TreeNode*) t2)->count){ 
		return ((const TreeNode*) t1)->c - ((const TreeNode*) t2)->c;
	}
	return ((const TreeNode*) t1)->count - ((const TreeNode*) t2)->count;
}
// Prints the contents of a TreeNode
void print_tree_node(FILE* fp, const void* tnode){
	fprintf(fp, "%c:%ld", ((TreeNode*) tnode)->c, ((TreeNode*) tnode)->count);
}

// Frees a TreeNode and all its children
void destroy_tree_node(void* tnode){
	if(tnode == NULL){
		return;
	}
	destroy_tree_node(((TreeNode*)tnode)->left);
	destroy_tree_node(((TreeNode*)tnode)->right);
	free(tnode);
}

// Inserts a node into a priority queue at the correct location
Node *pq_enqueue(Node **pq, const void *new_object, int (*cmp_fn)(const void *, const void *)){
	if(new_object == NULL){ 
		return NULL; 
	}
	Node *new_node = malloc(sizeof(*new_node));
	if(new_node == NULL) { 
		return NULL; 
	}
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

// Print a linked list
void print_node(FILE* fp, const Node *list, void (*print_fn)(FILE*, const void *)){
	while (list != NULL) {
		// print the memory associated with list->ptr
		print_fn(fp, list->ptr);
		// print an arrow
		fprintf(fp, "->");
		list = list->next;
	} 
	// print NULL and a newline after that 
	fprintf(fp, "NULL\n");
}

// Frees a linked list
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

