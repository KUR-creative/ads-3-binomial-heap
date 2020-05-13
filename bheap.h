#ifndef _BHEAP_H_
#define _BHEAP_H_

#define TRUE    (1==1)
#define FALSE   (!TRUE)

#define SUCCESS (0)
#define FAILURE (1)
//#define NULL (0)

typedef int Key;

typedef struct Node {
    Key             key;
    int             degree;
    struct Node*    parent;
    struct Node*    child;
    struct Node*    sibling;
} Node;
// Empty heap is NULL pointer(0 Node).

void print_node(Node* node);
void print_tree(Node* root);
void print_roots(Node* head, Node* tail);
void print_heap(Node* heap);

int link_tree(Node* parent, Node* child);
Node* merge_roots(Node* heap1, Node* heap2);
int merge_heap(Node* heap1, Node* heap2, Node** merged);
int insert(Node* heap, Key key);

int is_heap(Node* heap);
int num_tree_node(Node* root);
#endif // _BHEAP_H_
