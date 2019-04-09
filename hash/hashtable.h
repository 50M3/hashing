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

// hash_t - Klasse
class hash_t{
public:
    hash_t(int slots = 1000);                   //Konstruktor
    ~hash_t();                                  //Dekonstruktor
    int hash(int key);                          //Hashfunktion
    node_t *newNode(int first_value);           //Neue Liste
    void add(int key);                          //Einfügfunktion
    bool remove(int key);                       //Löschfunktion
    //void printTable();
    bool search(int key);                       //Suchfunktion

private:
    int m;                                      //Anzahl der Schlüssel
    int n;                                      //Anzahl der Spalten

    node_t **hashTable;
};
