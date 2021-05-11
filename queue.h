#include <stdio.h>
#include <stdlib.h>

#define MIN_CAPACITY 4  /* min capacity an array is expanded to when You add an item to a zero-capacity queue */

/* basic queue structure, a wrapping around an array */
typedef struct Queue {
    void** array;

    size_t count;            /* amount of items currently stored in array */
    size_t capacity;            /* possible amount of items stored in the array (can be expanded) */
} Queue;

/* creates a new queue with zero capacity and returns it */
Queue queue_new(void) {
    Queue new_stack = {NULL, 0, 0};
    return new_stack;
}

/* adds item to the end of queue for pending */
void queue_enqueue(Queue* queue, void* item) {
    if (queue->capacity == 0) {          /* allocate initial 4 bytes if empty */
        queue->capacity = MIN_CAPACITY;
        queue->array = calloc(queue->capacity, sizeof(void*));            /* used calloc to remove garbage values */
    } else if (queue->count == queue->capacity) {         /* double the size if needed */
        queue->capacity *= 2;
        queue->array = realloc(queue->array, queue->capacity * sizeof(void*));
    }

    queue->array[queue->count++] = item;
}

/* removes the next waiting item from queue and returns it */
void* queue_dequeue(Queue* queue) {
    if (queue->count != 0) {
        void* next = queue->array[0];
        for (int i = 1; i < queue->count; ++i) {
            queue->array[i - 1] = queue->array[i];
        }
        queue->count--;
        return next;
    }

    perror("QUEUE IS EMPTY");
    return NULL;
}

/* returns the next waiting item from queue, keeps it in queue */
void* queue_peek(Queue* queue) {
    if (queue->count != 0) {
        return queue->array[0];
    }

    perror("QUEUE IS EMPTY");
    return NULL;
}

/* removes all items from queue, keeps capacity unchanged */
void queue_clear(Queue* queue) {
    for (int i = 0; i < queue->count; ++i) {
        queue->array[i] = NULL;
    }
    queue->count = 0;
}

/* completely deallocates queue */
void queue_dealloc(Queue* stack) {
    stack->count = 0;
    stack->capacity = 0;

    free(stack->array);
}