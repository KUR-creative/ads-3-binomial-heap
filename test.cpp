//map <F4> :wa<CR>:!clear;rm test;g++ -g test.cpp bheap.c -o test -lgtest;./test<CR>

#include <gtest/gtest.h>
#include "bheap.h"


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

TEST(print_tree, test){
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

//-------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
