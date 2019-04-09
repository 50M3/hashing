//  ***********************************************************************************************************
//  Name:       hashtable.cpp
//  Author:     Florian Liehr
//  Datum:      09.04.2019
//  Uhrzeit:    14:08
//  Beschreib.  Diese Datei implementiert Funtionen zum Verwalten einer Hashtabelle.
//  ***********************************************************************************************************

#include <iostream>
#include <iomanip>
#include "hashtable.h"

/*
 * hash_t::hash_t(int spalten)
 *  Erstellt eine Hashtabelle der Größe <spalten>
 *
 * Parameterliste:
 *  int spalten: Die Größe der erstellenden Hashtabelle
 */
hash_t::hash_t(int spalten) {
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

/*
 * hash_t::~hash_t
 *  Dekonstruiert die Hashtabelle
 */
hash_t::~hash_t(){
    delete[] hashTable;
    m = 0;
}

/*
 * int hash_t::hash(int key)
 *  Errechnet einen Key durch die Divisionsmethode
 *
 * Parameterliste:
 *  int key: Der Key der gehashed werden soll
 *
 * Rückgabeparameter:
 *  hashed_key: Der neue Key
 */
int hash_t::hash(int key){
    int hashed_key = 0;

    hashed_key = key % m;
    return hashed_key;
}

/*
 * node_t* hash_t::newNode(int value)
 *  Erstellt eine neue Liste
 *
 * Parameterliste:
 *  int value: Der eingefügte Wert von value.
 *
 * Rückgabeparamter:
 *  node: Die neu erstellte Liste
 */
node_t* hash_t::newNode(int value) {
    node_t *node = (node_t*) malloc(sizeof(node_t));

    node->data = value;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

/*
 * void hash_t::add(int key)
 *  Fügt ein neues Element in die Hashtabelle ein
 *
 * Parameterliste:
 *  int key: key mit dem in die Liste eingefügt wird
 */
void hash_t::add(int key) {
    int hashed_key = hash(key);

    node_t *curr = hashTable[hashed_key];
    while(curr->next != nullptr){
        curr = curr->next;
    }

    node_t* element = newNode(key);
    curr->next = element;
}

/*
 * bool hash_t::remove(int key)
 *  Löscht ein Element welches mit dem key gefunden wurde.
 *
 * Parameterliste:
 *  int key: Key mit dem in der Liste gesucht wird.
 *
 * Rückgabeparameter:
 *  bool: false: Liste ist leer
 *  bool: true: Element wurde erfolgreich gelöscht
 */
bool hash_t::remove(int key){
    int hashed_key = hash(key);

    node_t* curr = hashTable[hashed_key];
    node_t* prev = nullptr;
    node_t* next = nullptr;

    while(curr->data != key){
        curr = curr->next;

        if(curr == nullptr)
            return false;
    }
    prev->next = next;
    next->prev = prev;

    delete(curr);
    return true;
}

/*
 * bool hash_t::search(int key)
 *  Sucht ein Element welches zum Key passt
 *
 * Parameterliste:
 *  int key: Key mit dem in der Liste gesucht wird
 *
 * Rückgabeparameter:
 *  bool: false: Liste ist leer
 *  bool: true: Element wurde in der Liste gefunden
 */
bool hash_t::search(int key) {
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