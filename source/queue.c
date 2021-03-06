#include <stdio.h>
#include <stdlib.h>
#include "collections.h"

/* returns a new blank queue */
Queue queue_new(void) {
    Queue new_queue = {NULL, 0, 0};
    return new_queue;
}

/* adds an item to the end of queue for pending */
void queue_enqueue(Queue* queue, void* item) {
    if (queue == NULL) {
        perror("\nQUEUE REFERENCE WAS NULL");
        return;
    }

    if (queue->capacity == 0) {          /* set default capacity if list is empty */
        queue->capacity = MIN_QUEUE_CAPACITY;
        queue->array = malloc(queue->capacity * sizeof(void*));
    } else if (queue->count == queue->capacity) {         /* double capacity of list if more space is needed */
        queue->capacity *= 2;
        queue->array = realloc(queue->array, queue->capacity * sizeof(void*));
    }

    queue->array[queue->count++] = item;
}

/* returns the next waiting item from queue, removes it from queue */
void* queue_dequeue(Queue* queue) {
    if (queue == NULL) {
        perror("\nQUEUE REFERENCE WAS NULL");
        return NULL;
    }

    if (queue->count != 0) {
        void* next = queue->array[0];
        for (int i = 1; i < queue->count; ++i) {
            queue->array[i - 1] = queue->array[i];
        }
        queue->count--;
        return next;
    }

    perror("\nQUEUE IS EMPTY");
    return NULL;
}

/* returns the next waiting item from queue, keeps it in queue */
void* queue_peek(Queue* queue) {
    if (queue == NULL) {
        perror("\nQUEUE REFERENCE WAS NULL");
        return NULL;
    }

    if (queue->count != 0) {
        return queue->array[0];
    }

    perror("\nQUEUE IS EMPTY");
    return NULL;
}

/* removes all items from a list (capacity is unchanged) */
void queue_clear(Queue* queue) {
    if (queue == NULL) {
        perror("\nQUEUE REFERENCE WAS NULL");
        return;
    }

    queue->count = 0;
}

/* completely deallocates queue */
void queue_dealloc(Queue* queue) {
    if (queue == NULL) {
        perror("\nQUEUE REFERENCE WAS NULL");
        return;
    }

    queue->count = 0;
    queue->capacity = 0;

    free(queue->array);
}