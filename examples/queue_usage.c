#include <stdio.h>
#include <time.h>
#include "collections_generic.h"

typedef char* string;

void suspend(double seconds);

GENERATE_QUEUE_OF_TYPE(string)              /* 1. generate API for queue */

/* queue usage: queueing objects */
void queue_execute_example(void) {
    stringQueue queue = string_queue_new();             /* 2. create a new queue */
    string customers[] = {"Helen", "Max", "Alex", "Ihor"};

    for (int i = 0; i < sizeof(customers) / sizeof(customers[0]); ++i) {
        string_queue_enqueue(&queue, customers[i]);             /* 3. add new items to the queue */
    }

    int portions = 0;
    while (queue.count > 0) {
        string current = string_queue_dequeue(&queue);      /* 3. get the next item, remove it from the queue */
        string next = string_queue_peek(&queue);            /* 3. get the next item, keep it in the queue */
        printf("\n%s got an ice-cream. %s is next!", current, next);
        string_queue_enqueue(&queue, next);             /* 3. enqueue an item */

        suspend(1.5);

        ++portions;

        if (portions == 6) {    /* isn't converted into for loop for the sake of usage of string_queue_clear() */
            string_queue_clear(&queue);             /* 3. remove all items */
        }
    }

    string_queue_dealloc(&queue);           /* 4. deallocate the queue (to avoid memory leak) */
}

void suspend(double seconds) {
    if (seconds <= 0) {
        return;
    }

    clock_t start = clock();
    while ((double)(clock() - start) / (double)CLOCKS_PER_SEC < seconds) { }
}