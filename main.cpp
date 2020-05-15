// map <F4> :wa<CR>:!rm main;g++ main.cpp bheap.c -g -o main;./main<CR>
#include <iostream>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include "bheap.h"

namespace crn = std::chrono;

#define EXPR(key, description, code) do{            \
    auto beg_clk = crn::steady_clock::now();        \
    code                                            \
    auto end_clk = crn::steady_clock::now();        \
    auto run_time = end_clk - beg_clk;              \
    std::cout <<                                    \
        key": " <<                                  \
        crn::duration<double,std::milli>(run_time)  \
        .count() << std::endl;                      \
}while(0)

#define EXPR1(description, n1, n2, code) do{        \
    auto beg_clk = crn::steady_clock::now();        \
    code                                            \
    auto end_clk = crn::steady_clock::now();        \
    auto run_time = end_clk - beg_clk;              \
    printf("- {n1: %d, n2: %d, time: %f}\n",        \
        n1, n2,                                     \
        crn::duration<double,std::milli>(run_time));\
}while(0)


int main(int argc, char* argv[]){
    // 1. serial insert: asc, dec, rand.
    // 2. min, pop_min: asc, dec, rand
    // 3. merge two random heaps
    //int num_data = 10000000;
    //int num_data = 100;
    //int num_data = 10000;
    int num_data = 1000;
    //int num_data = 10;
    
    int num_data_m = 10000;

    if(argc > 1){
        int argv1ret = sscanf(argv[1], "%d", &num_data);
        int argv2ret = sscanf(argv[2], "%d", &num_data_m);
        if(argv1ret == EOF || argv2ret == EOF){
            std::cout << "argv error: " << '\n';
            std::cout << argv[0] << ',' 
                      << argv[1] << ',' 
                      << argv[2] << '\n';
        }
    }

    {
    int* h = (int*)malloc(num_data * sizeof(int));
    EXPR("h.push.asc", "std::heap push",
        for(int i = 0; i < num_data; i++){
            h[i] = i;
            //printf("[%d]=%d", i, num_data - i);
            std::push_heap(h, h+i, std::greater<>{});
            /*
            for(int j = 0; j < num_data; j++){
                std::cout << h[j] << ' '; } puts("");
            */
        }
    );
    //std::cout << "h: "; for (auto i : h) std::cout << i << ' ';
    EXPR("h.pop.asc", "std::heap pop",
        for(int i = 0; i < num_data; i++){
            //printf("[%d]=%d ", i, h[i]);
            std::pop_heap(
                h, h + num_data - i, std::greater<>{});
            /*
            for(int j = 0; j < num_data; j++){
                std::cout << h[j] << ' '; } 
            printf("[%d]", h[num_data - i - 1]);
            puts("");
            */
                
            int min = h[num_data - i - 1];
            if(min != i){ 
                std::cout << min << " vs " << i << '\n'; }
        }
    );
    free(h);
    }

    {
    Node* node = (Node*)malloc(num_data * sizeof(Node));
    //Node node[num_data] = { 0, };
    Node* h = NULL;
    EXPR("bh.push.asc", "binomial heap push",
        for(int i = 0; i < num_data; i++){
            node[i].key = i;
            insert(&h, node+i);
        }
    );
    EXPR("bh.pop.asc", "binomial heap pop",
        for(int e = 0; e < num_data; e++){
            int a = pop_min(&h);
            if(a != e){ std::cout << "error"; }
        }
    );
    // std::cout << "bh: "; for(int i = 0; i < num_data; i++){ std::cout << i << ' '; }
    free(node);
    }

    {
    int* h = (int*)malloc(num_data * sizeof(int));
    EXPR("h.push.dec", "std::heap push",
        for(int i = 0; i < num_data; i++){
            h[i] = num_data - i;
            //printf("[%d]=%d", i, num_data - i);
            std::push_heap(h, h+i, std::greater<>{});
        }
    );
    //std::cout << "h: "; for (auto i : h) std::cout << i << ' ';
    EXPR("h.pop.dec", "std::heap pop",
        for(int i = num_data - 1; i >= 0; i--){
            //printf("[%d]=%d ", i, h[i]);
            std::pop_heap(h, h+i, std::greater<>{});
            int min = h[i];
            if(min != num_data - i){ 
                std::cout << min << " vs " << 
                    num_data - i << '\n'; }
        }
    );
    free(h);
    }

    {
    Node* node = (Node*)malloc(num_data * sizeof(Node));
    //Node node[num_data] = { 0, };
    Node* h = NULL;
    EXPR("bh.push.dec", "binomial heap push",
        for(int i = num_data - 1; i >= 0; i--){
            node[i].key = i;
            insert(&h, node+i);
        }
    );
    EXPR("bh.pop.dec", "binomial heap pop",
        for(int e = 0; e < num_data; e++){
            int a = pop_min(&h);
            if(a != e){ std::cout << "error"; }
        }
    );
    // std::cout << "bh: "; for(int i = 0; i < num_data; i++){ std::cout << i << ' '; }
    free(node);
    }

    {
    srand(time(NULL));
    int* h = (int*)malloc(num_data * sizeof(int));
    EXPR("h.push.rand", "std::heap push",
        for(int i = 0; i < num_data; i++){
            h[i] = rand() % num_data;
            //printf("[%d]=%d", i, num_data - i);
            std::push_heap(h, h+i, std::greater<>{});
            /*
            for(int j = 0; j < num_data; j++){
                std::cout << h[j] << ' '; } puts("");
            */
        }
    );
    //std::cout << "h: "; for (auto i : h) std::cout << i << ' ';
    EXPR("h.pop.rand", "std::heap pop",
        for(int i = 0; i < num_data; i++){
            //printf("[%d]=%d ", i, h[i]);
            std::pop_heap(
                h, h + num_data - i, std::greater<>{});
            /*
            for(int j = 0; j < num_data - i; j++){
                std::cout << h[j] << ' '; } 
            int min = h[num_data - i - 1];
            printf("[%d]", min);
            puts("");
            */
        }
    );
    free(h);
    }

    {
    Node* node = (Node*)malloc(num_data * sizeof(Node));
    Node* h = NULL;
    EXPR("bh.push.rand", "binomial heap push",
        for(int i = num_data - 1; i >= 0; i--){
            node[i].key = rand() % num_data;
            insert(&h, node+i);
        }
    );
    EXPR("bh.pop.rand", "binomial heap pop",
        for(int e = 0; e < num_data; e++){
            int a = pop_min(&h);
        }
    );
    // std::cout << "bh: "; for(int i = 0; i < num_data; i++){ std::cout << i << ' '; }
    free(node);
    }

    {
    puts("h.merge.2rand: ");
    //int n_iter = 100;
    int n_iter = 3;
    for(int _ = 0; _ < n_iter; _++){
        int n1 = rand() % num_data_m + 1;
        int n2 = rand() % num_data_m + 1;

        int h1[n1] = {0,};
        int h2[n2] = {0,};
        //int* h1 = (int*)malloc(n1 * sizeof(int));
        //int* h2 = (int*)malloc(n2 * sizeof(int));

        // make heap1, 2
        for(int i = 0; i < n1; i++){ 
            h1[i] = rand() % num_data_m;
            std::make_heap(h1, h1+n1, std::greater<>{});
        }
        for(int i = 0; i < n2; i++){
            h2[i] = rand() % num_data_m;
            std::make_heap(h2, h2+n2, std::greater<>{});
        }

        //printf("h1: "); for(int i = 0; i < n1; i++){ std::cout << h1[i] << ' '; } puts("");
        //printf("h2: "); for(int i = 0; i < n2; i++){ std::cout << h2[i] << ' ';  } puts("");
        
        // merge: copy and make_heap
        EXPR1("1 elem", n1, n2,
            int* m = (int*)malloc((n1 + n2) * sizeof(int));
            memcpy(m, h1, n1 * sizeof(int));
            memcpy(m + n1, h2, n2 * sizeof(int));
        //printf("m: "); for(int i = 0; i < n1 + n2; i++){ std::cout << m[i] << ' '; } puts("");
            std::make_heap(m, m + n1 + n2, std::greater<>{});
        //printf("hm: "); for(int i = 0; i < n1 + n2; i++){ std::cout << m[i] << ' '; } puts("");
            free(m); 
        );
        //free(h2);
        //free(h1);
    }
    }

    {
    puts("bh.merge.2rand: ");
    int n_iter = 100;
    for(int _ = 0; _ < n_iter; _++){
        int n1 = rand() % num_data_m + 1;
        int n2 = rand() % num_data_m + 1;

        //Node* node1 = (Node*)malloc(n1 * sizeof(Node));
        //Node* node2 = (Node*)malloc(n2 * sizeof(Node));
        Node node1[n1] = {0,};
        Node node2[n2] = {0,};
        Node* h1 = NULL; Node* h2 = NULL;

        // make heap1, 2
        for(int i = 0; i < n1; i++){ 
            node1[i].key = rand() % num_data_m;
            insert(&h1, node1+i);
        }
        for(int i = 0; i < n2; i++){
            node2[i].key = rand() % num_data_m;
            insert(&h2, node2+i);
        }

        //printf("node1: "); for(int i = 0; i < n1; i++){ std::cout << node1[i] << ' '; } puts("");
        //printf("node2: "); for(int i = 0; i < n2; i++){ std::cout << node2[i] << ' ';  } puts("");
        
        // merge
        EXPR1("1 elem", n1, n2,
            Node* merged = NULL;
            merge_heap(h1, h2, &merged);
        );
        //free(h2);
        //free(h1);
    }
    }
}
