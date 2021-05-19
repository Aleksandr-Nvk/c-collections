#include <stdio.h>
#include "collections_generic.h"

GENERATE_STACK_OF_TYPE(char)            /* 1. generate API for stack */

/* stack usage: reversing input */
void stack_execute_example(void) {
    charStack stack = char_stack_new();             /* 2. create a new stack */

    printf("Enter any text and press Enter: ");

    char c;
    while ((c = (char)getchar()) != '\n') {
        char_stack_push(&stack, c);             /* 3. add a new item to the top */
    }

    /* 3. view an item at the top, keep it in the stack */
    printf("Entered %zu letters. The last one: %c", stack.count, char_stack_peek(&stack));
    printf("\nReversed: ");

    while (stack.count > 0) {
        putchar(char_stack_pop(&stack));            /* 3. view an item at the top, remove it from the stack */
    }

    char_stack_clear(&stack);           /* 3. remove all items (redundant in this example) */

    char_stack_dealloc(&stack);             /* 4. deallocate the stack (to avoid memory leak) */
}