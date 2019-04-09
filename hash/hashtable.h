//  ***********************************************************************************************************
//  Name:       hashtable.h
//  Author:     Florian Liehr
//  Datum:      09.04.2019
//  Uhrzeit:    14:08
//  ***********************************************************************************************************

#ifndef GDI_HASHTABLE_H
#define GDI_HASHTABLE_H

#endif //GDI_HASHTABLE_H

#include <iostream>
#include "linked_list.h"

class hasht{
public:
    hasht(int slots = 1000);
    ~hasht();
    int hash(int key);
    node_t *newNode(int first_value);
    void addKey(int key);
    //bool deleteKey(int key);
    //void printTable();
    bool search(int key);

private:
    int m;
    int n;

    node_t **hashTable;
};
