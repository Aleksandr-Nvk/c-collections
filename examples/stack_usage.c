#include "collections_generic.h"
#include <stdio.h>

typedef struct Type {
    int data;
} Type;

GENERATE_STACK_OF_TYPE(Type)
GENERATE_STACK_OF_TYPE(char)

/* stack usage: reversing input */
void stack_execute_example(void) {
    size_t input_length;
    int input_character;
    charStack stack = char_stack_new();

    printf("\nEnter any text: ");

    while ((input_character = getchar()) != '\n' && input_character != EOF) {
        char_stack_push(&stack, (char)input_character);
    }

    printf("\nReversed input: ");

    input_length = stack.count;
    for (int i = 0; i < input_length; ++i) {
        putchar(char_stack_pop(&stack));
    }

    char_stack_dealloc(&stack);             /* mandatory deallocation of the stack */
}