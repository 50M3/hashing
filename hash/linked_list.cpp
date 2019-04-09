//  ***********************************************************************************************************
//  Name:       linked_list.cpp
//  Author:     Florian Liehr
//  Datum:      09.04.2019
//  Uhrzeit:    13:58
//  ***********************************************************************************************************

#include <iostream>
#include "linked_list.h"

node_t *newNode(int val, node_t *prev, node_t *next){
    node_t *node = (node_t*) malloc(sizeof(node_t));

    node->data = val;
    node->next = next;
    node->prev = prev;
    return node;
}

void listAddElement(node_t *head, int val){
    if (head == nullptr){
        std::cout << "ERROR: Head is Empty!";
        exit(-1);
    }

    node_t *curr = head;
    while (curr->next){
        curr = curr->next;
    }

    node_t *element = newNode(val, curr, nullptr);
    curr->next = element;
}

void listDelete(node_t *head){
    if (head == nullptr)
        return;

    node_t *curr = head;
    node_t *next = nullptr;
    while(curr){
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void listDeleteElement(node_t *head, int val){
    if (head == nullptr)
        return;

    node_t *curr = head;

    while (curr->next && curr->data != val)
        curr = curr->next;

    // CHECK VAL AGAIN
    if (curr->data == val){
        // HEAD IS TARGET?
        if (curr == head){
            // HEAD IS ONLY->DELETE LIST
            if (curr->next == nullptr){
                listDelete(head);
                return;
            }
            else{
                curr->data = curr->next->data;
                curr->next = curr->next->next;
                free(curr->next);
            }
        }
        else{
            curr->prev->next = curr->next;
            if (curr->next)
                curr->next->prev = curr->prev;
            free(curr);
        }
    };
}

void listPrint(node_t *head){
    if (head == nullptr)
        return;

    node_t *curr = head;
    int i = 1;
    while(1){
        std::cout << "->%1d", curr->data;
        i++;
        if (curr->next)
            curr = curr->next;
        else
            return;
    };
}