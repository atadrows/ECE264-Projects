#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TreeNode {
	unsigned char c;
	long count;
	struct _TreeNode* left;
	struct _TreeNode* right;
} TreeNode;

typedef struct _Node {
   void *ptr;
   struct _Node *next;
} Node;

//HW 14
void print_char_header(FILE*, TreeNode*);
void print_huffman_bits(FILE*, char*);

//HW12 & 13
void create_ascii_count_array(FILE*, long*);
void print_ascii_array(FILE*, long*);
Node *pq_enqueue(Node**, const void*, int (*cmp_fn)(const void *, const void *));
int tree_compare (const void*, const void*);
Node* create_sorted_list(Node*, long*);
void destroy_tree_node(void*);
void print_tree_node(FILE*, const void*);
void print_node(FILE*, const Node*, void (*print_fn)(FILE*, const void *));
void destroy_node(Node*, void (*destroy_fn)(void *));
Node *stack_pop(Node**);
Node* build_tree(Node*);
void print_coded_values(FILE*, TreeNode*, char*, int);
int huf_compare (const void*, const void*);
