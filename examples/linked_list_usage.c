#include "collections.h"
#include <stdio.h>

/* prints strings from linked list starting from 'current' */
void print_lin_list(Node* current) {
    printf("\n%s", (char*)current->data);
    if (current->next != NULL) {
        print_lin_list(current->next);              /* printing items one after another */
    }
}

/* linked list usage: playlist queue */
void linked_list_execute_example(void) {
    char* music[] = {"Without Me", "Killing Strangers", "Deutschland", "Ride"};
    Node* head = lin_list_new_head(music[0]);

    for (int i = 1; i < sizeof(music) / sizeof(music[0]); ++i) {
        lin_list_append(head, music[i]);            /* adding new tracks to queue */
    }

    lin_list_remove(head, music[2]);             /* remove "Deutschland" */

    printf("\nCurrent playlist queue:");
    print_lin_list(head);

    lin_list_dealloc(head);             /* mandatory deallocation of the list */
}