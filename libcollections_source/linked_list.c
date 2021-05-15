#include <stdlib.h>

/* basic node structure */
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

/* returns a new head node */
Node* lin_list_new_head(void* data) {
    Node* new_node = malloc(sizeof(Node));  /* heads are allocated in heap to be cleaned easily */
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

/* returns the last node in a linked list */
Node* lin_list_get_tail(Node* head) {
    if (head->next != NULL) {
        return lin_list_get_tail(head->next);
    }

    return head;
}

/* appends a new node with given data to a linked list */
void lin_list_append(Node* head, void* data) {
    Node *tail, *new_node;
    tail = lin_list_get_tail(head);
    new_node = malloc(sizeof(Node));        /*
                                             * memory needs to be allocated, otherwise 'new_node' will be freed from
                                             * stack as soon as the function ends, which will cause infinite recursion
                                             * in 'lin_list_get_tail()'. Same applies to 'lin_list_prepend()'
                                             */
    new_node->data = data;
    new_node->next = NULL;

    tail->next = new_node;
}

/* prepends a new head with given data to a linked list and returns it */
Node* lin_list_prepend(Node* head, void* data) {
    Node* new_head = malloc(sizeof(Node));

    new_head->data = data;
    new_head->next = head;

    return new_head;
}

/* removes head node from a linked list and returns a new head (or NULL if head was the only node) */
Node* lin_list_remove_head(Node* head) {
    Node* new_head = head->next;
    free(head);

    return new_head;
}

/* removes the last node from a linked list */
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

/* removes the first node with data identical to given from a linked list and returns the head node */
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

/* completely deallocates a linked list */
void lin_list_dealloc(Node* head) {
    if (head->next != NULL) {
        lin_list_dealloc(head->next);
    }

    free(head);
}