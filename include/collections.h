#include <stdlib.h>

typedef struct List {
    void** array;

    size_t count;
    size_t capacity;
} List;

List list_new(void);
void* list_of_index(List* list, size_t index);
void list_add(List* list, void* item);
void list_remove(List* list, void* item);
void list_clear(List* list);
void list_dealloc(List* list);

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

Node* lin_list_new_head(void* data);
Node* lin_list_get_tail(Node* head);
void lin_list_append(Node* head, void* data);
Node* lin_list_prepend(Node* head, void* data);
Node* lin_list_remove_head(Node* head);
void lin_list_remove_tail(Node* head);
Node* lin_list_remove(Node* head, void* data);
void lin_list_dealloc(Node* head);

typedef struct Stack {
    void** array;

    size_t count;
    size_t capacity;
} Stack;

Stack stack_new(void);
void stack_push(Stack* stack, void* item);
void* stack_pop(Stack* stack);
void* stack_peek(Stack* stack);
void stack_clear(Stack* stack);
void stack_dealloc(Stack* stack);

typedef struct Queue {
    void** array;

    size_t count;
    size_t capacity;
} Queue;

Queue queue_new(void);
void queue_enqueue(Queue* queue, void* item);
void* queue_dequeue(Queue* queue);
void* queue_peek(Queue* queue);
void queue_clear(Queue* queue);
void queue_dealloc(Queue* queue);

typedef struct KeyValuePair {
    void* key;
    void* value;
} KeyValuePair;

typedef struct Dictionary {
    KeyValuePair** array;

    size_t* counts;
    size_t* capacities;

    size_t count;
} Dictionary;

Dictionary dict_new(void);
void dict_add(Dictionary* dictionary, void* key, void* value);
void* dict_resolve(Dictionary* dictionary, void* key);
void dict_remove(Dictionary* dictionary, void* key);
void dict_clear(Dictionary* dictionary);
void dict_dealloc(Dictionary* dictionary);