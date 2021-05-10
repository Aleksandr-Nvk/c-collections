#include <stdlib.h>

/* basic node structure */
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

/* creates a new linked list head node with data and returns it */
Node* lin_list_new_head(void* data) {
    Node* new_node = malloc(sizeof(Node));  /* heads are allocated in heap to be cleaned easily */

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

/* gets the last node in linked list and returns it */
Node* lin_list_get_tail(Node* head) {
    if (head->next != NULL) {
        return lin_list_get_tail(head->next);
    }

    return head;
}

/* appends a new node with 'new_data' data to linked list */
void lin_list_append(Node* head, void* new_data) {
    Node *end, *new_node;
    end = lin_list_get_tail(head);
    new_node = malloc(sizeof(Node));  /*
                                             * memory needs to be allocated, otherwise 'new_node' will be freed from
                                             * stack as soon as the function ends, which will cause infinite recursion
                                             * in 'lin_list_get_tail()'. Same applies to 'lin_list_prepend()'
                                             */
    new_node->data = new_data;
    new_node->next = NULL;

    end->next = new_node;
}

/* prepends a new head with new data to linked list and returns it */
Node* lin_list_prepend(Node* head, void* new_data) {
    Node* new_head = malloc(sizeof(Node));

    new_head->data = new_data;
    new_head->next = head;

    return new_head;
}

/* removes head node from linked list and returns a new head */
Node* lin_list_remove_head(Node* head) {
    Node* new_head = head->next;
    free(head);

    return new_head;
}

/* removes the last node from linked list */
void lin_list_remove_tail(Node* head) {
    Node *current, *previous;
    current = previous = head;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    previous->next = NULL;
    free(current);
}

/* removes the first node with data identical to given from linked list and returns a head */
Node* lin_list_remove(Node* head, void* data) {
    Node *current, *previous;
    current = previous = head;

    while (current != NULL) {
        if (current->data == data) {
            if (current == head) {
                return lin_list_remove_head(head);
            } else if (current->next == NULL) {
                previous->next = NULL;
                free(current);
            } else {
                previous->next = current->next;
                free(current);
            }

            return head;
        }

        previous = current;
        current = current->next;
    }

    return head;
}

/* completely deallocates linked list */
void lin_list_dealloc(Node* head) {
    if (head->next != NULL) {
        lin_list_dealloc(head->next);
    }
    free(head);
}