//map <F4> :wa<CR>:!clear;rm test;g++ -g test.cpp bheap.c -o test -lgtest;./test<CR>

#include <gtest/gtest.h>
#include "bheap.h"

TEST(link_tree, test){
    Node parent = {  1, 0, NULL, NULL, NULL };
    Node child  = { 10, 0, NULL, NULL, NULL };

    link_tree(&child, &parent);
    print_node(&parent); puts("");
    print_node(&child); puts("");

    ASSERT_TRUE(parent.child);
    ASSERT_TRUE(child.parent);
    ASSERT_EQ(parent.child, &child);
}

//-------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
