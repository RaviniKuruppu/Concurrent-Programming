#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "linked_list.h"
#include "serial.h"

unsigned long serialExecution(int total_operations, int member_frac, int insert_frac, int delete_frac){
    //total_opreations--> m=10,000

    list_node_s *head = NULL;

    int member_operations_count = 0;   // temporary store the number of member operations
    int insert_operations_count = 0;  
    int delete_operations_count = 0;
    int total_operations_count = 0;

    int n = 1000; // Number of elements in the linked list
    int element_count = 0;

    //srand(time(0));

    // Randomly insert n number of elements
    while (element_count < n){
        Insert(rand()%MAX, &head);   // insert random numbers in to the linked list
        element_count++;
    }

    struct timeval start;
    struct timeval end;

    // Start time
    gettimeofday(&start, NULL);

    while (total_operations_count < total_operations){

        int rand_value = rand() % MAX;
        int operation_number = rand() % 3; // generate a random number between 0 and 2  ex:{0,1,2}

        if (operation_number == 0 && insert_operations_count < insert_frac){
            Insert(rand_value, &head);
            insert_operations_count++;
            total_operations_count++;
        }
        else if(operation_number == 1 && member_operations_count < member_frac){
            Member(rand_value, head);
            member_operations_count++;
            total_operations_count++;
        }
        else if(delete_operations_count < delete_frac){
            Delete(rand_value, &head);
            delete_operations_count++;
            total_operations_count++;
        }
    }

    // End time
    gettimeofday(&end, NULL);
    unsigned long time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec; 
    //printf("Time taken: %lu μs\n", time);

    Destructor(head);
    //printf("Serial run complete\n");
    return time;
}