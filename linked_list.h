#include <stdlib.h>

/* basic node structure */
typedef struct node {
    void* data;
    struct node* next;
} node;

/* creates a new linked list node with data in it and returns it */
node* new_lin_list_head(void* data) {
    node* new_node = malloc(sizeof(node));  /* heads are also allocated in heap to be cleaned easily */

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

/* gets the last node in chain starting from 'current' and returns it */
node* get_end_lin_list(node* current) {
    if (current->next != NULL) {
        return get_end_lin_list(current->next);
    }

    return current;
}

/* Inserts a new_data node with 'new_data' data at the end of the list */
void ap_to_lin_list(node* head, void* new_data) {
    node* end = get_end_lin_list(head);
    node* new_node = malloc(sizeof(node));  /*
                                             * memory needs to be allocated, otherwise 'new_node' will be freed from
                                             * stack as soon as the function ends, which will cause infinite recursion
                                             * in 'get_end_lin_list()'. Same applies to 'prep_to_lin_list()'
                                             */
    new_node->data = new_data;
    new_node->next = NULL;

    end->next = new_node;
}

/* Inserts a new head with 'new' data and returns it */
node* prep_to_lin_list(node* old_head, void* new_data) {
    node* new_head = malloc(sizeof(node));

    new_head->data = new_data;
    new_head->next = old_head;

    return new_head;
}

/* removes the last node from linked list with head */
void rem_fr_end_of_lin_list(node* head) {
    node* current = head;
    node* penultimate;

    while(current->next != NULL) {
        penultimate = current;
        current = current->next;
    }

    penultimate->next = NULL;
    free(current);
}

/* removes the last node from linked list with head and returns a new head */
node* rem_at_head_of_lin_list(node* head) {
    node* new_head = head->next;
    free(head);

    return new_head;    /* user has no access to non-head nodes, so we need to return a new head after deletion */
}

/* deallocates memory used by linked list starting from head */
void clear_lin_list(node* head) {
    if (head->next != NULL) {
        clear_lin_list(head->next);
    }
    free(head);
}