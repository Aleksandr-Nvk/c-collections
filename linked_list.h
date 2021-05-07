#include <stdlib.h>

/* basic node structure */
typedef struct node {
    void* data;
    struct node* next;
} node;

/* basic list structure, a wrapping around an array */
typedef struct linked_list {
    node** array;           /* inner array */

    size_t count;            /* amount of items currently stored in array */
    size_t capacity;            /* possible amount of items stored in the array (can be expanded) */
} linked_list;

/* creates a new list with zero capacity and returns it */
linked_list new_lin_list(void) {
    linked_list new_list = {NULL, 0, 0};
    return new_list;
}

/* creates a new linked list node with data in it and returns it */
node new_lin_list_node(void* data) {
    struct node new_node = {data, NULL};
    return new_node;
}