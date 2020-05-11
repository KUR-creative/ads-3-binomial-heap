#include <stdlib.h>
#include <stdio.h>
#include "bheap.h"


void print_node(Node* node)
{
    printf("k[%d] deg[%d] p[%p] child[%p] sibling[%p]",
        node->key, node->degree, 
        node->parent, node->child, node->sibling);
}

void print_tree_(Node* root, int depth, int is_last)
{
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

void print_roots(Node* head, Node* tail)
{
    Node* now = head;
    if(tail){
        while(now && now->sibling && now != tail->sibling){
            printf("%d ", now->degree);
            now = now->sibling;
        }
    }else{
        for(Node* now = head; now; now = now->sibling){
            printf("%d ", now->degree);
        }
    }
    puts("");
}

#include <limits.h>
// NOTE: side effect! It changes heap1 and heap2.
Node* merge_roots(Node* heap1, Node* heap2)
{
    Node* h1 = heap1; if(h1 == NULL) return heap2;
    Node* h2 = heap2; if(h2 == NULL) return heap1;

    Node* head = ((h1->degree <= h2->degree) ? h1 : h2);
    Node* now = head;
    while(now){
/*
printf("------------------\n");
printf("now[%d] h1[%d] h2[%d] ", (now ? now->degree : -1), (h1 ? h1->degree : -1), (h2 ? h2->degree : -1));
printf("roots: "); print_roots(head, NULL); puts("");
printf("roots: "); print_roots(head, now); puts("");
*/
        int sib_deg = (now->sibling ? 
            now->sibling->degree : INT_MAX);
        if(now == h1){
            int h2deg = (h2 ? h2->degree : INT_MAX);
            h1 = h1->sibling;
            if(h2deg < sib_deg){
                now->sibling = h2;
            }
            now = now->sibling;
        }
        else if(now == h2){
            int h1deg = (h1 ? h1->degree : INT_MAX);
            h2 = h2->sibling;
            if(h1deg < sib_deg){
                now->sibling = h1;
            }
            now = now->sibling;
        }
    }

    return head;
}

