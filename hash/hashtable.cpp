//  ***********************************************************************************************************
//  Name:       hashtable.cpp
//  Author:     Florian Liehr
//  Datum:      09.04.2019
//  Uhrzeit:    14:08
//  ***********************************************************************************************************

#include <iostream>
#include <iomanip>
#include "hashtable.h"


hasht::hasht(int spalten) {
    hashTable = new node_t*[spalten];
    m = spalten;
    n = 0;

    for (int i = 0; i < m; ++i) {
        hashTable[i] = new node_t;
        hashTable[i]->data = 0;
        hashTable[i]->prev = nullptr;
        hashTable[i]->next = nullptr;
    }
}

hasht::~hasht(){
    delete[] hashTable;
    m = 0;
}

int hasht::hash(int key){
    int hashed_key = 0;

    hashed_key = key % m;
    return hashed_key;
}

node_t* hasht::newNode(int value) {
    node_t *node = (node_t*) malloc(sizeof(node_t));

    node->data = value;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

void hasht::addKey(int key) {
    int hashed_key = hash(key);

    node_t *curr = hashTable[hashed_key];
    while(curr->next != nullptr){
        curr = curr->next;
    }

    node_t* element = newNode(key);
    curr->next = element;
}

bool hasht::search(int key) {
    int hashed_key = hash(key);

    node_t* curr = hashTable[hashed_key];

    if(curr == nullptr){
        printf("Die Liste ist leer!");
    }

    while(curr->data != key){
        curr = curr->next;

        if(curr == nullptr){
            return false;
        }
    }

    return true;
}

