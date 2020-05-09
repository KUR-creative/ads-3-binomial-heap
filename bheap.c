#include <stdio.h>
#include "bheap.h"

void print_node(Node* node)
{
    printf("k[%d] deg[%d] p[%p] child[%p] sibling[%p]",
        node->key, node->degree, 
        node->parent, node->child, node->sibling);
}

int link_tree(Node* child, Node* parent)
{
    child->parent = parent;
    child->sibling = parent->child;
    parent->child = child;
    parent->degree += 1;

    return SUCCESS;
}
