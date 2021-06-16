#include <stdlib.h>

#define MIN_LIST_CAPACITY    4      /* min default size of inner array in list structure */
#define MIN_STACK_CAPACITY    4     /* min default size of inner array in stack structure */
#define MIN_QUEUE_CAPACITY    4     /* min default size of inner array in queue structure */
#define MIN_DICTIONARY_CAPACITY    4    /* min default size of inner arrays in dictionary structure */

/* basic list structure, a wrap around a standard array */
typedef struct List {
    void** array;

    size_t count;
    size_t capacity;
} List;

/* returns a new blank list */
List list_new(void);

/* returns an item from a list by an index (or NULL if the index is out of range) */
void* list_of_index(List* list, size_t index);

/* adds an item to a list */
void list_add(List* list, void* item);

/* removes the first occurrence of given item from a list */
void list_remove(List* list, void* item);

/* removes all items from a list (capacity is unchanged) */
void list_clear(List* list);

/* completely deallocates a list */
void list_dealloc(List* list);

/* basic linked list unit (node) */
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

/* returns a new head node with data in it */
Node* lin_list_head_new(void* data);

/* returns the last node in a linked list */
Node* lin_list_get_tail(Node* head);

/* appends a new node with given data to a linked list */
void lin_list_append(Node* head, void* data);

/* prepends a new head with given data to a linked list and returns it */
Node* lin_list_prepend(Node* head, void* data);

/* removes head node from a linked list and returns a new head (or NULL if head was the only node) */
Node* lin_list_remove_head(Node* head);

/* removes the last node from a linked list */
void lin_list_remove_tail(Node* head);

/* removes the first node with data identical to given from a linked list and returns the head node */
Node* lin_list_remove(Node* head, void* data);

/* completely deallocates a linked list */
void lin_list_dealloc(Node* head);

/* basic stack structure, a wrap around a standard array */
typedef struct Stack {
    void** array;

    size_t count;
    size_t capacity;
} Stack;

/* returns a new blank stack */
Stack stack_new(void);

/* adds item to the top of stack */
void stack_push(Stack* stack, void* item);

/* returns the last item from stack, removes it from stack */
void* stack_pop(Stack* stack);

/* returns the last item from stack, keeps it in stack */
void* stack_peek(Stack* stack);

/* removes all items from a list (capacity is unchanged) */
void stack_clear(Stack* stack);

/* completely deallocates stack */
void stack_dealloc(Stack* stack);

/* basic queue structure, a wrap around a standard array */
typedef struct Queue {
    void** array;

    size_t count;
    size_t capacity;
} Queue;

/* returns a new blank queue */
Queue queue_new(void);

/* adds an item to the end of queue for pending */
void queue_enqueue(Queue* queue, void* item);

/* returns the next waiting item from queue, removes it from queue */
void* queue_dequeue(Queue* queue);

/* returns the next waiting item from queue, keeps it in queue */
void* queue_peek(Queue* queue);

/* removes all items from a list (capacity is unchanged) */
void queue_clear(Queue* queue);

/* completely deallocates queue */
void queue_dealloc(Queue* queue);

/* basic key-value pair structure, used to bind a value to its access key */
typedef struct KeyValuePair {
    void* key;
    void* value;
} KeyValuePair;

/* basic dictionary structure, a wrap around a standard array */
typedef struct Dictionary {
    KeyValuePair** array;

    size_t* counts;
    size_t* capacities;

    size_t count;
} Dictionary;

/* returns a new blank dictionary */
Dictionary dict_new(void);

/* adds a key-value pair to a dictionary */
void dict_add(Dictionary* dictionary, void* key, void* value);

/* returns a value by its key */
void* dict_resolve(Dictionary* dictionary, void* key);

/* removes a value bond to a key from a dictionary */
void dict_remove(Dictionary* dictionary, void* key);

/* removes all items from a dictionary (capacity is unchanged) */
void dict_clear(Dictionary* dictionary);

/* completely deallocates dictionary */
void dict_dealloc(Dictionary* dictionary);