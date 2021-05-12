#include <stdio.h>
#include <stdlib.h>

#define MIN_CAPACITY 4  /* min capacity an array is expanded to when You add an item to a zero-capacity stack */

/* basic stack structure, a wrapping around an array */
typedef struct Stack {
    void** array;

    size_t count;            /* amount of items currently stored in array */
    size_t capacity;            /* possible amount of items stored in the array (can be expanded) */
} Stack;

/* creates a new stack with zero capacity and returns it */
Stack stack_new(void) {
    Stack new_stack = {NULL, 0, 0};
    return new_stack;
}

/* adds item to the top of stack */
void push(Stack* stack, void* item) {
    if (stack->capacity == 0) {          /* allocate initial 4 bytes if empty */
        stack->capacity = MIN_CAPACITY;
        stack->array = malloc(stack->capacity * sizeof(void*));
    } else if (stack->count == stack->capacity) {         /* double the size if needed */
        stack->capacity *= 2;
        stack->array = realloc(stack->array, stack->capacity * sizeof(void*));
    }

    stack->array[stack->count++] = item;
}

/* removes the last item from stack and returns it */
void* stack_pop(Stack* stack) {
    if (stack->count != 0) {
        return stack->array[--stack->count];
    }

    perror("\nSTACK IS EMPTY");
    return NULL;
}

/* returns the last item from stack, keeps it in stack */
void* stack_peek(Stack* stack) {
    if (stack->count != 0) {
        return stack->array[stack->count - 1];
    }

    perror("\nSTACK IS EMPTY");
    return NULL;
}

/* removes all items from stack, keeps capacity unchanged */
void stack_clear(Stack* stack) {
    stack->count = 0;
}

/* completely deallocates stack */
void stack_dealloc(Stack* stack) {
    stack->count = 0;
    stack->capacity = 0;

    free(stack->array);
}