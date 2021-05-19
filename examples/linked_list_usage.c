#include <stdio.h>
#include <string.h>
#include "collections_generic.h"

typedef char* string;

int lin_list_equals(string first, string second);

GENERATE_LINKED_LIST_OF_TYPE(string, &lin_list_equals)    /* 1. generate API for linked list */

void print_lin_list(stringNode* current);

/* linked list usage: playlist queue */
void linked_list_execute_example(void) {
    char* tracks[] = {"Without Me", "Killing Strangers", "Blinding Lights", "Ride", "Rap God"};

    stringNode* head = string_lin_list_new_head(tracks[0]);    /* 2. create a new head */

    printf("\n*** INITIAL ***\n\n");
    print_lin_list(head);

    for (int i = 1; i < sizeof(tracks) / sizeof(tracks[0]); ++i) {
        string_lin_list_append(head, tracks[i]);            /* 3. add items to the end */
    }

    printf("\n\n*** APPENDED ***\n\n");
    print_lin_list(head);

    head = string_lin_list_prepend(head, "Lucid Dreams");   /* 3. add another item to the beginning */

    printf("\n\n*** PREPENDED ***\n\n");
    print_lin_list(head);

    head = string_lin_list_remove_head(head);           /* 3. remove the first item */

    printf("\n\n*** REMOVED (FIRST) ***\n\n");
    print_lin_list(head);

    string_lin_list_remove(head, "Ride");               /* 3. remove the node which contains "Ride" */

    printf("\n\n*** REMOVED ***\n\n");
    print_lin_list(head);

    /* removing all nodes except head */
    while (string_lin_list_get_tail(head) != head) {    /* 3. get the last item */
        string_lin_list_remove_tail(head);              /* 3. remove the last item */
    }

    printf("\n\n*** REMOVED (LAST) ***\n");
    print_lin_list(head);

    string_lin_list_dealloc(head);              /* 4. deallocate the list (to avoid memory leak) */
}

/* function used to compare objects in list */
int lin_list_equals(string first, string second) {
    return !strcmp(first, second);
}

/* prints strings from linked list starting from 'current' */
void print_lin_list(stringNode* current) {
    printf("\"%s\" ", (char*)current->data);
    if (current->next != NULL) {
        printf("-> ");
        print_lin_list(current->next);              /* printing items one after another, recursively */
    }
}