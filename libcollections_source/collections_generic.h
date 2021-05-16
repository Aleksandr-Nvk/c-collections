#include <stdlib.h>
#include <stdio.h>

#define MIN_LIST_CAPACITY 4  /* default capacity of an empty list when you add the first item to it */
#define MIN_STACK_CAPACITY 4  /* default capacity of an empty stack when you add the first item to it */
#define MIN_QUEUE_CAPACITY 4  /* default capacity of an empty queue when you add the first item to it */
#define MIN_DICTIONARY_CAPACITY 4  /* default capacity of internal dictionary arrays when you add the first items to them */

#define GENERATE_LIST_OF_TYPE(type) \
/* basic list structure, a wrapping around an array */ \
typedef struct type##List { \
    type* array; \
\
    size_t count;            /* amount of items currently stored in list */ \
    size_t capacity;            /* possible amount of items stored in list (can be expanded) */ \
} type##List; \
\
/* returns a new blank list */ \
type##List type##_list_new(void) { \
    type##List new_list = {NULL, 0, 0}; \
    return new_list; \
} \
\
/* returns an item from a list by an index (or NULL if the index is out of range) */ \
type list_of_index(type##List* list, size_t index) { \
    if (index < list->count || index >= 0) { \
        return list->array[index]; \
    } \
\
    /* Throw the following error if the index is out of range */ \
    perror("\nINDEX WAS OUT OF RANGE"); \
    return 0; \
} \
\
/* adds an item to a list */ \
void list_add(type##List* list, type item) { \
    if (list->capacity == 0) { \
        list->capacity = MIN_LIST_CAPACITY; \
        list->array = malloc(list->capacity * sizeof(type)); \
    } else if (list->count == list->capacity) { \
        list->capacity *= 2;            /* double capacity of list if more space is needed */ \
        list->array = realloc(list->array, list->capacity * sizeof(type)); \
    } \
\
    list->array[list->count++] = item; \
} \
\
/* removes the first occurrence of given item from a list */ \
void list_remove(type##List* list, type item) { \
    for (int i = 0; i < list->count; ++i) { \
        if (list->array[i] == item) { \
            /* Defragmentation of the list */ \
            for (int k = i; k < list->count - 1; ++k) { \
                list->array[k] = list->array[k + 1]; \
            } \
            --list->count; \
            break; \
        } \
    } \
} \
\
/* removes all items from a list (capacity is unchanged) */ \
void list_clear(type##List* list) { \
    list->count = 0; \
} \
\
/* completely deallocates a list */ \
void list_dealloc(type##List* list) { \
    list->count = 0; \
    list->capacity = 0; \
\
    free(list->array); \
} \

#define GENERATE_LINKED_LIST_OF_TYPE(type) \
/* basic node structure */ \
typedef struct type##Node { \
    type data; \
    struct type##Node* next; \
} type##Node; \
\
/* returns a new head node */ \
type##Node* type##_lin_list_new_head(type data) { \
    type##Node* new_node = malloc(sizeof(type##Node));  /* heads are allocated in heap to be cleaned easily */ \
    new_node->data = data; \
    new_node->next = NULL; \
\
    return new_node; \
} \
\
/* returns the last node in a linked list */ \
type##Node* type##_lin_list_get_tail(type##Node* head) { \
    if (head->next != NULL) { \
        return type##_lin_list_get_tail(head->next); \
    } \
\
    return head; \
} \
\
/* appends a new node with given data to a linked list */ \
void type##_lin_list_append(type##Node* head, type data) { \
    type##Node *tail, *new_node; \
    tail = type##_lin_list_get_tail(head); \
    new_node = malloc(sizeof(type##Node));        /*
                                             * memory needs to be allocated, otherwise 'new_node' will be freed from
                                             * stack as soon as the function ends, which will cause infinite recursion
                                             * in 'lin_list_get_tail()'. Same applies to 'lin_list_prepend()'
                                             */ \
    new_node->data = data; \
    new_node->next = NULL; \
\
    tail->next = new_node; \
} \
\
/* prepends a new head with given data to a linked list and returns it */ \
type##Node* type##_lin_list_prepend(type##Node* head, type data) { \
    type##Node* new_head = malloc(sizeof(type##Node)); \
\
    new_head->data = data; \
    new_head->next = head; \
\
    return new_head; \
} \
\
/* removes head node from a linked list and returns a new head (or NULL if head was the only node) */ \
type##Node* type##_lin_list_remove_head(type##Node* head) { \
    type##Node* new_head = head->next; \
    free(head); \
\
    return new_head; \
} \
\
/* removes the last node from a linked list */ \
void type##_lin_list_remove_tail(type##Node* head) { \
    type##Node *current, *previous; \
    current = previous = head; \
\
    while (current->next != NULL) { \
        previous = current; \
        current = current->next; \
    } \
\
    previous->next = NULL; \
    free(current); \
} \
\
/* removes the first node with data identical to given from a linked list and returns the head node */ \
type##Node* type##_lin_list_remove(type##Node* head, type data) { \
    type##Node *current, *previous; \
    current = previous = head; \
\
    while (current != NULL) { \
        if (current->data == data) { \
            if (current == head) { \
                return type##_lin_list_remove_head(head); \
            } else if (current->next == NULL) { \
                previous->next = NULL; \
                free(current); \
            } else { \
                previous->next = current->next; \
                free(current); \
            } \
\
            return head; \
        } \
\
        previous = current; \
        current = current->next; \
    } \
\
    return head; \
} \
\
/* completely deallocates a linked list */ \
void type##_lin_list_dealloc(type##Node* head) { \
    if (head->next != NULL) { \
        type##_lin_list_dealloc(head->next); \
    } \
\
    free(head); \
} \

#define GENERATE_STACK_OF_TYPE(type) \
/* basic stack structure, a wrapping around an array */ \
typedef struct type##Stack { \
    type* array; \
\
    size_t count;            /* amount of items currently stored in stack */ \
    size_t capacity;            /* possible amount of items stored in stack (can be expanded) */ \
} type##Stack; \
\
/* returns a new blank stack */ \
type##Stack type##_stack_new(void) { \
    type##Stack new_stack = {NULL, 0, 0}; \
    return new_stack; \
} \
\
/* adds item to the top of stack */ \
void type##_stack_push(type##Stack* stack, type item) { \
    if (stack->capacity == 0) {          /* set default capacity if list is empty */ \
        stack->capacity = MIN_STACK_CAPACITY; \
        stack->array = malloc(stack->capacity * sizeof(type)); \
    } else if (stack->count == stack->capacity) {         /* double capacity of list if more space is needed */ \
        stack->capacity *= 2; \
        stack->array = realloc(stack->array, stack->capacity * sizeof(type)); \
    } \
\
    stack->array[stack->count++] = item; \
} \
\
/* returns the last item from stack, removes it from stack */ \
type type##_stack_pop(type##Stack* stack) { \
    if (stack->count != 0) { \
        return stack->array[--stack->count]; \
    } \
\
    perror("\nSTACK IS EMPTY"); \
    return 0; \
} \
\
/* returns the last item from stack, keeps it in stack */ \
type type##_stack_peek(type##Stack* stack) { \
    if (stack->count != 0) { \
        return stack->array[stack->count - 1]; \
    } \
\
    perror("\nSTACK IS EMPTY"); \
    return 0; \
} \
\
/* removes all items from a list (capacity is unchanged) */ \
void type##_stack_clear(type##Stack* stack) { \
    stack->count = 0; \
} \
\
/* completely deallocates stack */ \
void type##_stack_dealloc(type##Stack* stack) { \
    stack->count = 0; \
    stack->capacity = 0; \
\
    free(stack->array); \
} \

#define GENERATE_QUEUE_OF_TYPE(type) \
/* basic queue structure, a wrapping around an array */ \
typedef struct type##Queue { \
    type* array; \
\
    size_t count;            /* amount of items currently stored in queue */ \
    size_t capacity;            /* possible amount of items stored in queue (can be expanded) */ \
} type##Queue; \
\
/* returns a new blank queue */ \
type##Queue type##_queue_new(void) { \
    type##Queue new_queue = {NULL, 0, 0}; \
    return new_queue; \
} \
\
/* adds an item to the end of queue for pending */ \
void type##_queue_enqueue(type##Queue* queue, type item) { \
    if (queue->capacity == 0) {          /* set default capacity if list is empty */ \
        queue->capacity = MIN_QUEUE_CAPACITY; \
        queue->array = malloc(queue->capacity * sizeof(type)); \
    } else if (queue->count == queue->capacity) {         /* double capacity of list if more space is needed */ \
        queue->capacity *= 2; \
        queue->array = realloc(queue->array, queue->capacity * sizeof(type)); \
    } \
\
    queue->array[queue->count++] = item; \
} \
\
/* returns the next waiting item from queue, removes it from queue */ \
type type##_queue_dequeue(type##Queue* queue) { \
    if (queue->count != 0) { \
        type next = queue->array[0]; \
        for (int i = 1; i < queue->count; ++i) { \
            queue->array[i - 1] = queue->array[i]; \
        } \
        queue->count--; \
        return next; \
    } \
\
    perror("\nQUEUE IS EMPTY"); \
    return 0; \
} \
\
/* returns the next waiting item from queue, keeps it in queue */ \
type type##_queue_peek(type##Queue* queue) { \
    if (queue->count != 0) { \
        return queue->array[0]; \
    } \
\
    perror("\nQUEUE IS EMPTY"); \
    return 0; \
} \
\
/* removes all items from a list (capacity is unchanged) */ \
void type##_queue_clear(type##Queue* queue) { \
    queue->count = 0; \
} \
\
/* completely deallocates queue */ \
void type##_queue_dealloc(type##Queue* queue) { \
    queue->count = 0; \
    queue->capacity = 0; \
\
    free(queue->array); \
} \

#define GENERATE_DICTIONARY_OF_TYPE(key_type, value_type) \
typedef struct key_type##value_type##KeyValuePair { \
    key_type key; \
    value_type value; \
} key_type##value_type##KeyValuePair; \
\
typedef struct key_type##value_type##Dictionary { \
    key_type##value_type##KeyValuePair** array;           /* array of 10 arrays, basic structure of hash table */ \
\
    size_t* counts;         /* stores 10 counts of each nested array */ \
    size_t* capacities;         /* stores 10 capacities of each nested array */ \
\
    size_t count;            /* amount of key-value pairs currently stored in dictionary */ \
} key_type##value_type##Dictionary; \
\
key_type##value_type##Dictionary key_type##_value_type##_dict_new(void) { \
    key_type##value_type##Dictionary new_dictionary = {malloc(10 * sizeof(key_type##value_type##KeyValuePair*)), \
                                 calloc(10, sizeof(size_t)), \
                                 calloc(10, sizeof(size_t)),0}; \
\
    return new_dictionary; \
} \
\
/* adds a key-value pair to a dictionary */ \
void key_type##_value_type##_dict_add(key_type##value_type##Dictionary* dictionary, key_type key, value_type value) { \
    size_t index = (long)key % 10;          /* reduce the amount of indices */ \
\
    if (dictionary->capacities[index] == 0) { \
        dictionary->capacities[index] = MIN_DICTIONARY_CAPACITY; \
        dictionary->array[index] = malloc(dictionary->capacities[index] * sizeof(key_type##value_type##KeyValuePair)); \
    } else if (dictionary->capacities[index] == dictionary->counts[index]) { \
        dictionary->capacities[index] *= 2; \
        dictionary->array[index] = realloc(dictionary->array[index], dictionary->capacities[index] * sizeof(key_type##value_type##KeyValuePair)); \
    } \
\
    for (int i = 0; i < dictionary->counts[index]; ++i) { \
        if (dictionary->array[index][i].key == key) { \
            perror("\nITEM WITH SUCH KEY ALREADY EXISTS"); \
            return; \
        } \
    } \
\
    key_type##value_type##KeyValuePair new_pair = {key, value}; \
    dictionary->array[index][dictionary->counts[index]++] = new_pair; \
    ++dictionary->count; \
} \
\
/* returns a value by its key */ \
value_type key_type##_value_type##_dict_resolve(key_type##value_type##Dictionary* dictionary, key_type key) { \
    size_t index = (long)key % 10; \
    key_type##value_type##KeyValuePair* array = dictionary->array[index]; \
\
    for (int i = 0; i < dictionary->counts[index]; ++i) { \
        if (array[i].key == key) { \
            return array[i].value; \
        } \
    } \
\
    perror("\nNO ITEM WITH SUCH KEY FOUND"); \
    return 0; \
} \
\
/* removes a value bond to a key from a dictionary */ \
void key_type##_value_type##_dict_remove(key_type##value_type##Dictionary* dictionary, key_type key) { \
    size_t index = (long)key % 10; \
    key_type##value_type##KeyValuePair* array = dictionary->array[index]; \
\
    for (int i = 0; i < dictionary->counts[index]; ++i) { \
        if (array[i].key == key) { \
            for (int k = i; k < dictionary->counts[index] - 1; ++k) { \
                array[i] = array[i + 1]; \
            } \
\
            --dictionary->counts[index]; \
            --dictionary->count; \
            return; \
        } \
    } \
} \
\
/* removes all items from a dictionary (capacity is unchanged) */ \
void key_type##_value_type##_dict_clear(key_type##value_type##Dictionary* dictionary) { \
    for (int i = 0; i < 10; ++i) { \
        dictionary->counts[i] = 0; \
    } \
    dictionary->count = 0; \
} \
\
/* completely deallocates dictionary */ \
void key_type##_value_type##_dict_dealloc(key_type##value_type##Dictionary* dictionary) { \
    key_type##_value_type##_dict_clear(dictionary); \
\
    for (int i = 0; i < 10; ++i) { \
        dictionary->capacities[i] = 0; \
    } \
\
    free(dictionary->array); \
}