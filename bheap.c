#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "bheap.h"


void print_node(Node* node)
{
    if(node){
        printf(
            "k[%d] deg[%d] p[%p] child[%p] sibling[%p]\n",
            node->key, node->degree, 
            node->parent, node->child, node->sibling);
    }
}

void print_tree_(Node* root, int depth, int is_last)
{
    int deg = root->degree;
    Node* children[deg];

    int num_child = 0;
    Node* child = root->child;
    //printf("root[%p]\n", root);
    while(child){
        // Save children from back to front.
        //printf("sib[%p]\n", child);
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

void print_heap(Node* heap)
{
    for(Node* curr = heap; curr; curr = curr->sibling){
        print_tree(curr);
    }
}

int link_tree(Node* parent, Node* child)
{
    //printf("\nlink p[%p] <-> c[%p]\n", parent, child);
    //puts("----before----"); puts("parent"); print_node(parent); puts("child"); print_node(child);
    child->parent = parent;
    child->sibling = parent->child;
    parent->child = child;
    parent->degree += 1;

    //puts("----after----"); puts("parent"); print_node(parent); puts("child"); print_node(child);
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

int merge_heap(Node* heap1, Node* heap2, Node** merged)
{
    *merged = merge_roots(heap1, heap2);
    if(*merged == NULL){ return SUCCESS; }

    /*
    puts("\n----");
    print_node(*merged);
    print_node((*merged)->sibling);
    print_node(heap1);
    print_node(heap2);
    puts("----");
    */
    Node* prev = NULL;
    Node* curr = *merged;
    Node* next = (*merged)->sibling;
    while(next){
        if(curr->degree != next->degree ||
           (next->sibling &&
            next->sibling->degree == curr->degree)) 
        {
            prev = curr;
            curr = next;
        }else if(curr->key <= next->key){
            curr->sibling = next->sibling;
            link_tree(curr, next);
        }else{
            if(prev){
                prev->sibling = next; // TODO: Test it.
            }else{
                *merged = next;
            }
            link_tree(next, curr);
            curr = next;
        }
        next = curr->sibling;
    }
    return SUCCESS;
}

int is_valid_degree(int x){
    // 0 or 2^k is valid degree.
    return ((x & (x - 1)) == 0);
}

int num_tree_node_(Node* root, int num_node){
    Node* child = root->child;
    if(child){
        int num_child = 0;
        while(child){
            num_child++;
            child = child->sibling;
        }
        return num_tree_node_(
            root->child, num_node + num_child);
    }else{
        return num_node;
    }
}

/*
 * ret:
 *  -1  Invalid tree
 *   N  Number of nodes in tree 
 */
int num_tree_node(Node* root)
{
    return 1 + num_tree_node_(root, 0); // 1 is root.
}

