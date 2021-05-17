#include "collections.h"
#include <stdio.h>

/* queue usage: queueing objects */
void queue_execute_example(void) {
    char* people[] = {"Monica", "Chandler", "Rachel", "Phoebe", "Joey", "Ross"};
    Queue queue = queue_new();

    printf("\nCurrent queue: ");
    for (int i = 0; i < sizeof(people) / sizeof(people[0]); ++i) {
        printf("%s ", people[i]);
        queue_enqueue(&queue, people[i]);
    }

    queue_enqueue(&queue, queue_dequeue(&queue));           /* re-enqueue first two people */
    queue_enqueue(&queue, queue_dequeue(&queue));

    printf("\nCurrent queue: ");
    for (int i = 0; i < queue.count; ++i) {
        printf("%s ", (char*)queue_dequeue(&queue));
    }

    queue_dealloc(&queue);              /* mandatory deallocation of the queue */
}