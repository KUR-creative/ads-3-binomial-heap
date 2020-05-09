//map <F4> :wa<CR>:!clear;rm test;g++ -g test.cpp bheap.c -o test -lgtest;./test<CR>

#include <gtest/gtest.h>
#include "bheap.h"

//-------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
