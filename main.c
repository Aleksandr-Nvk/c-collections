#include "declarations.h"
#include "stdio.h"

/* Examples of usage of all collections */
int main(void) {
    printf("\n\n*** LIST EXAMPLE ***\n");
    list_execute_example();

    printf("\n\n*** LINKED LIST EXAMPLE ***\n");
    linked_list_execute_example();

    printf("\n\n*** QUEUE EXAMPLE ***\n");
    queue_execute_example();

    printf("\n\n*** STACK EXAMPLE ***\n");
    stack_execute_example();

    printf("\n\n*** DICTIONARY EXAMPLE ***\n");
    dictionary_execute_example();

    return 0;
}