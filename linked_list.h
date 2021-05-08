#include <stdlib.h>

/* basic node structure */
typedef struct node {
    void* data;
    struct node* next;
} node;

/* creates a new linked list node with data in it and returns it */
node new_lin_list_head(void* data) {
    node new_node = {data, NULL};
    return new_node;
}

/* returns size of linked list starting from 'head' */
size_t count_lin_list(node head) {
    size_t count = 1;
    node current = head;

    while (current.next != NULL) {
        current = *current.next;
        count++;
    }

    return count;
}

/* gets the last node in chain starting from 'current' and returns it */
node* get_end_lin_list(node* current) {
    if (current->next != NULL) {
        return get_end_lin_list(current->next);
    }

    return current;
}

/* Inserts a new_data node with 'new_data' data at the end of the list */
void ap_lin_list(node* head, void* new_data) {
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

/* gets all nodes starting from head and returns them */
node** get_all(node* head) {
    node* current = head;
    node** all = malloc(count_lin_list(*head));

    for (int i = 0; i < count_lin_list(*head); ++i) {
        all[i] = current;
        current = current->next;
    }

    return all;
}

/* deallocates memory used by linked list starting from head */
void clear_lin_list(node* head) {
    node** all = get_all(head);
    for (int i = 0; i < count_lin_list(*head) ; ++i) {
        free(all[i]);
    }
}