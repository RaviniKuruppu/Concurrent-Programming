#include <stdlib.h>
#include "linked_list.h"


/*Add struct - in the lec note*/

int Member(int value, list_node_s* head_p) {
    list_node_s* curr_p = head_p;

    while (curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if (curr_p == NULL || curr_p->data > value) {
        return 0;
    } else {
        return 1;
    }
}  /* Member */



int Insert(int value, list_node_s** head_pp) {
    list_node_s* curr_p = *head_pp;
    list_node_s* pred_p = NULL;
    list_node_s* temp_p;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        temp_p = malloc(sizeof(list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL){ /* New first node */
            *head_pp = temp_p;
        }
        else {
            pred_p->next = temp_p;
        }
        return 1;
    } else { /* Value already in list */
        return 0;
    }
}   /* Insert */


int Delete(int value, list_node_s** head_pp) {
    list_node_s* curr_p = *head_pp;
    list_node_s* pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value) {
        if (pred_p == NULL) { /*Deleting first node in list */
            *head_pp = curr_p->next;
            free(curr_p);
        } else {
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;
    } else { /*Value is not in list */
        return 0;
    }
}  /* Delete */




void Destructor(list_node_s* head_p){
    list_node_s* curr_p = head_p;
    list_node_s* temp_p = NULL;

    while (curr_p != NULL)
    {
        temp_p = curr_p;
        curr_p = curr_p->next;
        free(temp_p);
    }
} /* Destroy linked list */


void Print(list_node_s *head_p){
    list_node_s *curr_p = head_p;

    while (NULL != curr_p){
        printf("node: %d \n",curr_p->data);
        curr_p = curr_p->next;
    }
} /* Print linked list*/
