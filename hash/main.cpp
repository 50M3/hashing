//  ***********************************************************************************************************
//  Name:       main.cpp
//  Author:     Florian Liehr
//  Datum:      09.04.2019
//  Uhrzeit:    14:08
//  ***********************************************************************************************************
#include <iostream>
#include "hashtable.h"

int main() {
    int min = RAND_MAX, max = 0, rand_w = 0;

    int n = 100000000;
    int m = 0;

    for(int alpha = 0; alpha < 301; alpha++){
        m = n / alpha;
        hash_t test(m);

        for(int i = 0; i < 1000000; i++){
            rand_w = rand();

            if(rand_w > max){
                max = rand_w;
            }
            if(rand_w < min){
                min = rand_w;
            }
            test.add(rand_w);
        }

    }
    return 0;
}