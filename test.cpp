//map <F4> :wa<CR>:!clear;rm test;g++ -g test.cpp bheap.c -o test -lgtest;./test<CR>

#include <gtest/gtest.h>
#include "bheap.h"
#include <stdlib.h>
#include <time.h>


TEST(link_tree, test){
    Node parent = {  1, 0, NULL, NULL, NULL };
    Node child  = { 10, 0, NULL, NULL, NULL };

    link_tree(&parent, &child);
    print_node(&parent); puts("");
    print_node(&child); puts("");

    ASSERT_TRUE(parent.child);
    ASSERT_TRUE(child.parent);
    ASSERT_EQ(parent.child, &child);
}

//TEST(print_tree, test){
TEST(DISABLED_print_tree, test){
    { puts("n = 1 ----------------");
    Node root = { 1, 0, NULL, NULL, NULL };
    print_tree(&root); 
    puts("\n"); }

    { puts("n = 2 ----------------");
    Node root = { 1, 0, NULL, NULL, NULL };
    Node child= { 2, 0, NULL, NULL, NULL };
    link_tree(&root, &child);
    print_tree(&root); puts("");
     puts("\n"); }

    { puts("n = 4 ----------------");
    Node n[4];
    for(int i = 0; i < 4; i++){
        n[i] = { i, 0, NULL, NULL, NULL };
    }
    link_tree(&n[0], &n[1]); // 0--1
    link_tree(&n[2], &n[3]); // 2--3
    link_tree(&n[0], &n[2]); // 0--1
                             // |
                             // *--2--3
    print_node(&n[0]); puts("");
    print_tree(&n[0]); puts("");
     puts("\n"); }

    { puts("n = 8 ----------------");
    Node n[8];
    for(int i = 0; i < 8; i++){
        n[i] = { i, 0, NULL, NULL, NULL };
    }

    link_tree(&n[0], &n[1]); // 0--1
    link_tree(&n[2], &n[3]); // 2--3
    link_tree(&n[0], &n[2]); // 0--1
                             // |
                             // *--2--3
    link_tree(&n[4], &n[5]); // 4--5
    link_tree(&n[6], &n[7]); // 6--7
    link_tree(&n[4], &n[6]); // 4--5
                             // |
                             // *--6--7
    link_tree(&n[0], &n[4]); // 0--1
                             // |
                             // *--2--3
                             // |
                             // *--4--5
                             //    |
                             //    *--6--7
    //print_node(&n[0]); puts("");
    print_tree(&n[0]); puts("");
     puts("\n"); }

    { puts("n = 16 ----------------");
    Node n[16];
    for(int i = 0; i < 16; i++){
        n[i] = { i, 0, NULL, NULL, NULL };
    }

    link_tree(&n[0], &n[1]); // 0--1
    link_tree(&n[2], &n[3]); // 2--3
    link_tree(&n[0], &n[2]); // 0--1
                             // |
                             // *--2--3
    link_tree(&n[4], &n[5]); // 4--5
    link_tree(&n[6], &n[7]); // 6--7
    link_tree(&n[4], &n[6]); // 4--5
                             // |
                             // *--6--7
    link_tree(&n[0], &n[4]); // 0--1
                             // |
                             // *--2--3
                             // |
                             // *--4--5
                             //    |
                             //    *--6--7
    link_tree(&n[8], &n[9]); // 8--9
    link_tree(&n[10],&n[11]);// 10--11
    link_tree(&n[8], &n[10]);// 8--9
                             // |
                             // *--10--11
    link_tree(&n[12],&n[13]);// 12--13
    link_tree(&n[14],&n[15]);// 14--15
    link_tree(&n[12],&n[14]);// 12--13
                             // |
                             // *--14--15
    link_tree(&n[8],&n[12]); // 8--9
                             // |
                             // *--10--11
                             // |
                             // *--12--13
                             //    |
                             //    *--14--15
                             
    link_tree(&n[0], &n[8]); // 0--1
                             // |
                             // *--2--3
                             // |
                             // *--4--5
                             // |  |
                             // |  *--6--7
                             // |  
                             // *--8--9
                             //    |
                             //    *--10--11
                             //    |
                             //    *--12--13
                             //       |
                             //       *--14--15
    print_tree(&n[0]); puts("");
     puts("\n"); }
}


int len_roots(Node* roots){
    int len = 0;
    Node* cursor = roots;
    while(cursor){
        len++;
        cursor = cursor->sibling;
    }
    return len;
}

int degree(Node* head, int step){
    Node* now = head;
    for(int i = 0; i < step; i++){
        if(now){
            now = now->sibling;
        }else{
            return -1;
        }
    }
    return (now ? now->degree : -1);
}
TEST(merge_roots, 1){
    Node roots1[1] = { {0,3,0,0,0} };
    Node roots2[1] = { {0,1,0,0,0} };
    printf("r1s: "); print_roots(roots1, NULL);
    printf("r2s: "); print_roots(roots2, NULL);

    Node* merged = merge_roots(roots1, roots2);
    printf("\nmerged: "); print_roots(merged, NULL);

    ASSERT_EQ(degree(merged,0), 1);
    ASSERT_EQ(degree(merged,1), 3);
    ASSERT_EQ(merged, roots2);
    ASSERT_EQ(merged->sibling, roots1);
}

TEST(merge_roots, 2){
    size_t size = sizeof(Node);
    Node roots1[2] = { 
        {0,1,0,0,&roots1[1]},
        {0,7,0,0,0},
    };
    Node roots2[3] = { 
        {0,2,0,0,&roots2[1]},
        {0,3,0,0,&roots2[2]},
        {0,4,0,0,0},
    };
    printf("r1s: "); print_roots(roots1, NULL);
    printf("r2s: "); print_roots(roots2, NULL);

    Node* merged = merge_roots(roots1, roots2);
    printf("\nmerged: "); print_roots(merged, NULL);

    ASSERT_EQ(degree(merged,0), 1);
    ASSERT_EQ(degree(merged,1), 2);
    ASSERT_EQ(degree(merged,2), 3);
    ASSERT_EQ(degree(merged,3), 4);
    ASSERT_EQ(degree(merged,4), 7);
}

TEST(merge_roots, nil_h1){
    size_t size = sizeof(Node);
    Node* roots1 = NULL;
    Node roots2[3] = { 
        {0,2,0,0,&roots2[1]},
        {0,3,0,0,&roots2[2]},
        {0,4,0,0,0},
    };
    printf("r1s: "); print_roots(roots1, NULL);
    printf("r2s: "); print_roots(roots2, NULL);

    Node* merged = merge_roots(roots1, roots2);
    printf("\nmerged: "); print_roots(merged, NULL);

    ASSERT_EQ(degree(merged,0), 2);
    ASSERT_EQ(degree(merged,1), 3);
    ASSERT_EQ(degree(merged,2), 4);
}

TEST(merge_roots, property_test){
    int seed = time(NULL);
    //int seed = 1589194680;
    srand(seed);
    printf("\nseed: %d \n", seed);
    for(int no = 1; no < 101; no++)
    {
    // Generate random root list
    Node roots1[1000] = { 0, };
    Node roots2[1000] = { 0, };

    int len1 = rand() % (no * 10) + 1;
    roots1[0].degree = (rand() % 10 + 1);
    for(int i = 1; i < len1; i++){
        roots1[i].degree = 
            roots1[i - 1].degree + (rand() % 10 + 1);
        roots1[i - 1].sibling = &roots1[i]; 
    }

    int len2 = rand() % (no * 10) + 1;
    roots2[0].degree = (rand() % 10 + 1);
    for(int i = 1; i < len2; i++){
        roots2[i].degree = 
            roots2[i - 1].degree + (rand() % 10 + 1);
        roots2[i - 1].sibling = &roots2[i]; 
    }

    //printf("r1s: "); print_roots(roots1, NULL);
    //printf("r2s: "); print_roots(roots2, NULL);
    Node* new_roots = merge_roots(roots1, roots2);

    // length of new_roots = len1 + len2
    int len = len_roots(new_roots);
    ASSERT_EQ(len, len1 + len2);

    // TODO: 현재 한 쪽 길이 0인 경우 꺼놓은 상태
    // TODO: sorted 체크하는 코드 짜고, 길이 0 체크도 켜기.
    //printf("no = %d \n", no);
    Node* prev = NULL;
    Node* now = new_roots;
    while(now){
        len++;
        prev = now;
        now = now->sibling;
        if(now != NULL){
            ASSERT_LE(prev->degree, now->degree);
            //if(prev->degree > now->degree){ puts("prev->degree > now->degree"); }
        }
    }

    // new_roots must be sorted in ascending order of degree

    /*
    */
    }
}

TEST(merge_heap, merge_2_empty_heap_return_empty_heap){
    Node* h1 = NULL; Node* h2 = NULL; Node* merged;
    merge_heap(h1, h2, &merged);
    ASSERT_EQ(merged, (Node*)NULL);
}

TEST(merge_heap, merge_empty_and_1node_return_1node){
    Node node = {2, 0, NULL, NULL, NULL};
    Node* h1 = NULL; Node* h2 = &node; Node* merged;
    merge_heap(h1, h2, &merged);
    ASSERT_EQ(merged, &node);
}

TEST(merge_heap, case4_link_two_deg2_heap_to_deg4_heap){
    const int num_node = 4;
    Node node[num_node] = {
        {1, 1,   NULL, node+1,   NULL},
        {2, 0, node+0,   NULL,   NULL},
        {3, 1,   NULL, node+3,   NULL},
        {4, 0, node+2,   NULL,   NULL},
    };
    Node expected[num_node] = {
        {1, 2,   NULL, node+2,   NULL},
        {2, 0, node+0,   NULL,   NULL},
        {3, 1, node+0, node+3, node+1},
        {4, 0, node+2,   NULL,   NULL},
    };

    Node* h1 = node+2; Node* h2 = node+0; Node* merged; 
    merge_heap(h1, h2, &merged);

    ASSERT_EQ(merged, h2);
    /*
    puts("\n----ptrs----");
    printf("[%p]",node);
    printf("[%p]",node+1);
    printf("[%p]",node+2);
    printf("[%p]",node+3);
    puts("\n----root----");
    print_node(merged);
    puts("\n----result----");
    print_tree(merged);
    */
    for(int i = 0; i < num_node; i++){
        //printf("i[%d]", i);
        ASSERT_EQ(node[i].key,     expected[i].key);
        ASSERT_EQ(node[i].degree,  expected[i].degree);
        ASSERT_EQ(node[i].parent,  expected[i].parent);
        ASSERT_EQ(node[i].child,   expected[i].child);
        ASSERT_EQ(node[i].sibling, expected[i].sibling);
    }
}

//-------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
