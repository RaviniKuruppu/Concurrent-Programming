#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct list_node_s {
    int data;
    struct list_node_s* next;
};

typedef struct list_node_s list_node_s;

int Member(int value, list_node_s* head_p);
int Insert(int value, list_node_s** head_pp);
int Delete(int value, list_node_s** head_pp);

void Destructor(list_node_s* head_p);
void Print(list_node_s* head_p);

#endif