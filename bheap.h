#ifndef _BHEAP_H_
#define _BHEAP_H_

#define TRUE    (1==1)
#define FALSE   (!TRUE)

#define SUCCESS (0)
#define FAILURE (1)
//#define NULL (0)

typedef int Key;

typedef struct Node {
    Key          key;
    int          degree;
    struct Node* parent;
    struct Node* child;
    struct Node* sibling;
} Node;

void print_node(Node* node);
int link_tree(Node* child, Node* parent);

#endif // _BHEAP_H_
