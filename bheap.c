#include <stdlib.h>
#include <stdio.h>
#include "bheap.h"


void print_node(Node* node)
{
    printf("k[%d] deg[%d] p[%p] child[%p] sibling[%p]",
        node->key, node->degree, 
        node->parent, node->child, node->sibling);
}

void print_tree_(Node* root, int depth, int is_last){
    int deg = root->degree;
    Node* children[deg];

    int num_child = 0;
    Node* child = root->child;
    while(child){
        // Save children from back to front.
        children[deg - 1 - num_child] = child;
        num_child++;
        child = child->sibling;
    }

    // Assertion.
    if(num_child != deg){
        printf("deg[%d] != [%d]num_child", deg, num_child);
        exit(1);
    }

    // Print tree keys in tree form.
    if(num_child == 0){
        printf("\n"); return;
    }
    for(int i = 0; i < num_child; i++){
        if(i != 0) { 
            for(int d = 0; d < depth; d++){
                printf(is_last ? "   " : "|  ");
            } 
            printf("|\n"); 

            for(int d = 0; d < depth; d++){
                printf(is_last ? "   " : "|  ");
            } 
            printf("*");
        }
        printf("--%d", children[i]->key);

        int last = (i == num_child - 1);
        print_tree_(children[i], depth + 1, last);
    }
}

void print_tree(Node* root)
{
    printf("%d", root->key);
    print_tree_(root, 0, FALSE);
}

int link_tree(Node* parent, Node* child)
{
    child->parent = parent;
    child->sibling = parent->child;
    parent->child = child;
    parent->degree += 1;

    return SUCCESS;
}

