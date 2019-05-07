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

    int n = 10000;
    int m = 0;

    for(double alpha = 0.5; alpha < 1.0; alpha + 0.05){
        m = n / alpha;
        hash_t test(m);

    }
    return 0;
}