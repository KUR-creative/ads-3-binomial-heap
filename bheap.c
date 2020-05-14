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
        if(curr->sibling){
            puts("|");
        }
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

int insert(Node** heap, Node* node)
{
    node->degree  = 0;
    node->parent  = NULL;
    node->child   = NULL;
    node->sibling = NULL;
    merge_heap(*heap, node, heap);
    return SUCCESS;
}

int pop_min(Node** heap)
{
    if(*heap == NULL) {
        return INT_MAX;
    }

    // Get min prev and min node
    Key min_key = INT_MAX;
    Node* min_prev = NULL; Node* min_node;

    Node* prev = NULL; Node* root = *heap;
    for(; root; prev = root, root = root->sibling){
        if(min_key > root->key){
            min_key = root->key;
            min_prev = prev;
            min_node = root;
        }
    }

    puts("--- WTFWTF ---");
    printf("min_prev[%d]\n",GET(min_prev, key, -1));
    printf("min_node[%d]\n",GET(min_node, key, -1));
    printf("min_prev->[%p]\n",GET(min_prev, sibling, NULL));
    // Unlink min_prev -> min_node
    if(min_prev){
        min_prev->sibling = min_node->sibling;
    }
    if(min_node == *heap){
        *heap = min_node->sibling;
    }
    puts("unlinked");
    printf("min_prev[%d]\n",GET(min_prev, key, -1));
    printf("min_node[%d]\n",GET(min_node, key, -1));
    printf("min_prev->[%p]\n",GET(min_prev, sibling, NULL));

    // Save children from back to front.
    int deg = min_node->degree;
    Node* children[deg];

    int num_child = 0;
    Node* child = min_node->child;
    while(child){
        children[deg - 1 - num_child] = child;
        num_child++;
        child = child->sibling;
    }
    
    /*
    printf("===============sib: ");
    for(Node* c = min_node->child; c; c = c->sibling){
        printf("[%d]", c->key);
    }
    printf("\n------------ch: ");
    for(int i = 0; i < num_child; i++){
        printf("[%d]", children[i]->key);
    }
    */

    // Reverse children linkage
    //printf("=======================wtf: %d \n", num_child);
    if(num_child > 0){
        Node* prev; Node* curr;
        for(int idx = 1; idx < num_child; idx++){
            prev = children[idx - 1];
            curr = children[idx];
            prev->sibling = curr;
            //printf("\np[%d] c[%d]", (prev ? prev->key : -1), (curr ? curr->key : -1));
        }
        curr->sibling = NULL; // last elem->(nil)

        merge_heap(*heap, children[0], heap);
    }

    /*
    puts("------ *heap ------");
    print_heap(*heap);
    if(num_child > 1){
        puts("--- children[0] ---");
        print_heap(children[0]);
    }
    */

    return min_key;
}

// Return is minimum key.
int min(Node* heap, Node** min_node)
{
    Key min = INT_MAX;
    for(Node* root = heap; root; root = root->sibling){
        if(min > root->key){
            min = root->key;
            if(min_node){ // NULL means: Ignore min_node
                *min_node = root;
            }
        }
    }
    return min;
}

// TODO: tail recursion version?
int num_tree_node_(Node* parent, int num_node){
    if(parent){
        Node* child = parent->child;
        int num_child = 1;
        while(child){
            num_child += num_tree_node_(child,0);
            child = child->sibling;
        }
        return num_child;
    }else{
        return 0;
    }
}

int num_tree_node(Node* root)
{
    //return 1 + num_tree_node_(root, 0); // 1 is root.
    return num_tree_node_(root, 0);
}

int is_pow_of_2(int x){
    // x = 0 or x = 2^k ?
    return ((x & (x - 1)) == 0);
}

int is_min_heap_tree(Node* root)
{
    Node* child = root->child;
    if(child){
        // compare to root
        for(Node* c = child; c; c = c->sibling){
            if(c->key < root->key ||
               (! is_min_heap_tree(c))){
                return FALSE;
            }
        }
    }
    return TRUE;
}

int is_heap(Node* heap)
{
    for(Node* root = heap; root; root = root->sibling){
        //printf("root_key[%d] num_tree_node[%d] is_min_heap_tree[%d]\n", root->key, num_tree_node(root), is_min_heap_tree(root));
        if((! is_pow_of_2(num_tree_node(root))) ||
           (! is_min_heap_tree(root)))
        {
            return FALSE;
        }
    }

    return TRUE;
}
